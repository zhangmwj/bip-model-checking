/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 * 
 * This software is a computer program whose purpose is to generate
 * executable code from BIP models.
 * 
 * This software is governed by the CeCILL-B license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-B
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security.
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-B license and that you accept its terms.
 */

#include <ExecuteAtomJob.hpp>
#include "ExecuteConnectorJob.hpp"

#include "AtomInternalPort.hpp"
#include "AtomExternalPort.hpp"

#include "Connector.hpp"
#include "Compound.hpp"
#include "Atom.hpp"
#include "Logger.hpp"

#include "Executer.hpp"
#include "BipError.hpp"
#include "UnexpectedEventError.hpp"

#include <TimeValue.hpp>

ExecuteAtomJob::ExecuteAtomJob(Atom &atom) :
  Job(Executer::jobs, true),
  mInitialized(false),
  mAtom(atom),
  mLogger(NULL),
  mChosenPortValue(NULL),
  mChosenInternal(NULL),
  mChosenExternal(NULL),
  mChosenTime(TimeValue::MIN) {
}

ExecuteAtomJob::~ExecuteAtomJob() {
}

void ExecuteAtomJob::initialize() {
  const Atom &constAtom = atom();

  mWriter.addResource(atom().resource());
  
  // add resources for exported ports
  for (map<string, AtomExportPort *>::const_iterator portIt = constAtom.ports().begin() ;
       portIt != constAtom.ports().end() ;
       ++portIt) {
    AtomExportPort &port = *portIt->second;

    if (port.hasEarlyUpdate()) {
      mWriter.addResource(port.resource());
    }
  }

  // add resources for exported data
  for (map<string, AtomExportData *>::const_iterator dataIt = constAtom.data().begin() ;
       dataIt != constAtom.data().end() ;
       ++dataIt) {
    AtomExportData &data = *dataIt->second;

    if (data.hasEarlyUpdate()) {
      mWriter.addResource(data.resource());
    }
  }

  if (!isRealTime()) {
    atom().timeSafetyValidator().addResource(simulationClockResource());
  }

  // resume management
  mResumeReserver.addResource(atom().resumeResource());
}

void ExecuteAtomJob::realJob() {
  // execute initial transition or choice
  BipError &error = execute();

  if (error.type() != NO_ERROR) {
    logger().log(error);
  }
  
  if (!hasJoiner()) {
    // check events on external ports
    BipError &error = atom().recomputeExternals();

    if (error.type() != NO_ERROR) {
      logger().log(error);
    }
    else {
      // check time-safety and resume component
      BipError &error = checkTimeSafetyAndResume();

      if (error.type() != NO_ERROR) {
        logger().log(error);
      }
      else {
        // unreserve component
        // mReserved.unlock();
      }
    }
  }
  
  atom().allReady();
}

void ExecuteAtomJob::prologue() {  
  mWriter.start();
}

void ExecuteAtomJob::epilogue() {
  atom().resource().free();
  
  if (atom().hadResume()) {
    mResumeReserver.free();
  }
}

BipError &ExecuteAtomJob::execute() {
  BipError *error = NULL;

  if (hasChosen()) {
    modelClock().wait(chosenTime());
  }

  if (hasChosenPortValue()) {
    atom().allNotReady();

    error = &atom().execute(chosenPortValue(), chosenTime());

    // reset choice
    clearChosenPortValue();
  }
  else if (hasChosenInternal()) {
    atom().allNotReady();

    error = &atom().execute(chosenInternal(), chosenTime());

    // reset choice
    clearChosenInternal();
  }
  else if (hasChosenExternal()) {
    atom().allNotReady();

    error = &atom().execute(chosenExternal(), chosenTime());

    // reset choice
    clearChosenExternal();
  }
  else {
    assert(!mInitialized);

    // initialize corresponding atom
    atom().allNotReady();

    error = &atom().initialize();

    // initialize external ports
    initializeAllExternalPorts();

    mInitialized = true;
  }

  if (error->type() != NO_ERROR) {
    return *error;
  }

  // reset dependencies
  // atom().reset();

  return BipError::NoError;
}

BipError &ExecuteAtomJob::checkTimeSafetyAndResume() {
  // keep track of resume status for further urgency management
  atom().setHadResume(atom().hasResume());
  
  if (atom().hasResume()) {  
    TimeValue currentTime = platformClock().time();
  
    while (!mResumeReserver.tryToReserve(currentTime)) {
      currentTime = platformClock().time();
    }

    for (vector<Resource::Validator *>::const_iterator validatorIt = mResumeReserver.mValidators.begin() ;
         validatorIt != mResumeReserver.mValidators.end() ;
         ++validatorIt) {
      Resource::Validator &validator = **validatorIt;

      assert(validator.mReserve.isLocked());
    }
    
    // check time-safety before resuming
    BipError &error = checkTimeSafety(currentTime);

    if (error.type() != NO_ERROR) {
      return error;
    }

    // actual resume
    BipError &errorResume = resume(currentTime);

    if (errorResume.type() != NO_ERROR) {
      return error;
    }
  }

  return BipError::NoError;
}

BipError &ExecuteAtomJob::checkTimeSafety(const TimeValue &time) {
  Interval timeSafeInterval = Interval(modelClock().time(), TimeValue::MAX);

  if (atom().hasInvariant()) {
    timeSafeInterval &= atom().invariant();
  }

  if (atom().hasResume()) {
    timeSafeInterval &= atom().resume();
  }

  if (!timeSafeInterval.in(time)) {
    TimeSafetyViolationError &error = *new TimeSafetyViolationError(time, atom().holder().root());
    
    return error;
  }

  return BipError::NoError;
}

BipError &ExecuteAtomJob::resume(const TimeValue &time) {
  // only resumable atom can be resumed!
  assert(atom().hasResume());
    
  // update model time
  modelClock().wait(time);
    
  BipError &error = atom().resume(time);

  if (error.type() != NO_ERROR) {
    return error;
  }

  // mark atom as resumed
  atom().setHasResume(false);

  // recompute externals
  BipError &errorExternals = atom().recomputeExternals();

  if (errorExternals.type() != NO_ERROR) {
    return errorExternals;
  }

  return BipError::NoError;
}

void ExecuteAtomJob::initializeAllExternalPorts() {
  const Atom &constAtom = atom();

  // initialize external ports
  for (map<string, AtomExternalPort *>::const_iterator portIt = constAtom.externalPorts().begin() ;
         portIt != constAtom.externalPorts().end() ;
         ++portIt) {
    AtomExternalPort &port = *portIt->second;

    port.initialize();
  }
}

void ExecuteAtomJob::ResumeJoiner::epilogue() {
  assert(false);
  
  // real-time
  assert(!jobsToJoin().empty());

  Job &job = **jobsToJoin().begin();
  ExecuteAtomJob &atomJob = dynamic_cast<ExecuteAtomJob &>(job);

  TimeValue time = atomJob.platformClock().time();

  // check events on external ports
  for (vector<Job *>::const_iterator jobIt = jobsToJoin().begin() ;
       jobIt != jobsToJoin().end() ;
       ++jobIt) {
    Job &job = **jobIt;
    ExecuteAtomJob &atomJob = dynamic_cast<ExecuteAtomJob &>(job);

    BipError &error = atomJob.atom().recomputeExternals();

    if (error.type() != NO_ERROR) {
      atomJob.logger().log(error);

      return;
    }
  }

  // perform resume
  for (vector<Job *>::const_iterator jobIt = jobsToJoin().begin() ;
       jobIt != jobsToJoin().end() ;
       ++jobIt) {
    Job &job = **jobIt;
    ExecuteAtomJob &atomJob = dynamic_cast<ExecuteAtomJob &>(job);

    BipError &error = atomJob.resume(time);

    if (error.type() != NO_ERROR) {
      atomJob.logger().log(error);

      return;
    }
  }
  
  // unreserve components
  for (vector<Job *>::const_iterator jobIt = jobsToJoin().begin() ;
       jobIt != jobsToJoin().end() ;
       ++jobIt) {
    Job &job = **jobIt;
    ExecuteAtomJob &atomJob = dynamic_cast<ExecuteAtomJob &>(job);

    atomJob.epilogue();
  }

}
