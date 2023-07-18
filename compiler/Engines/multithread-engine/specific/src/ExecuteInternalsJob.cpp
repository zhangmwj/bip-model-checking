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

#include <ExecuteInternalsJob.hpp>
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

ExecuteInternalsJob::ExecuteInternalsJob(Atom &atom) :
  Job(Executer::jobs),
  mAtom(atom),
  mLogger(NULL),
  mReserver(*this),
  mChosenInternal(NULL),
  mChosenTime(TimeValue::MIN) {
  mResetChoice.dependsOn(atom.internals());
}

ExecuteInternalsJob::~ExecuteInternalsJob() {
}

void ExecuteInternalsJob::initialize() {  
  mResetChoice.addUser(*this);
  
  ExecuteAtomJob &atomJob = atom().executeJob();

  for (vector<Resource *>::const_iterator resourceIt = atomJob.writer().resources().begin() ;
         resourceIt != atomJob.writer().resources().end() ;
         ++resourceIt) {
    Resource &resource = **resourceIt;

    mReserver.addResource(resource);
  }

  if (!isRealTime()) {
    mReserver.addResource(simulationClockResource());
    
    mUpdateClockJob.initialize();
  }
}

void ExecuteInternalsJob::realJob() {
  // compute time-safe interval
  mTimeSafe = atom().timeSafetyValidator().timeSafe();

  if (hasChosen()              &&
      hasWokenUpAtWakeUpTime() &&
      !mResetChoice.isReset()  &&
      mTimeSafe.in(chosenTime())) {
    // in simulation mode interaction are executed directly without sleeping periods
    assert(isRealTime());

    // try to execute the chosen interaction
    tryToExecuteChosenInternal();
  }
  else {
    // update model time
    if (isRealTime() && hasResumeEager()) {
      mModelClock.wait(atom().time());
    }
    else {
      mModelClock.update();
    }
    
    // check time-safety
    if (!mTimeSafe.in(mModelClock.time())) {
      TimeSafetyViolationError &error = *new TimeSafetyViolationError(mModelClock.time(), atom().holder().root());

      // log time-safety violation error
      logger().log(error);
    }
    
    // chose an interaction...
    recomputeChoice();
    
    // ... and try to execute it
    if (hasChosen()) {
      if (isRealTime()) {
        restart(chosenTime());
      }
      else {
        tryToExecuteChosenInternal();
      }
    }
  }
}

bool ExecuteInternalsJob::tryToExecuteChosenInternal() {
  bool success = mReserver.tryToReserve(chosenTime());

  if (success) {
    modelClock().wait(chosenTime());
    
    if (isRealTime()) {
      modelClock().wait(chosenTime());
    }
    else {
      mUpdateClockJob.setTime(chosenTime());
      mUpdateClockJob.restart();
    }
  }

  // self-retart
  restart();

  return success;
}

void ExecuteInternalsJob::executeChosenInternal() {
  assert(hasChosen());
  
  // log the choices
  logger().log(chosenInternal(), chosenTime(), atom().internals());
    
  atom().executeJob().setChosenInternal(chosenInternal());
  atom().executeJob().setChosenTime(chosenTime());
  atom().setHasResume(chosenInternal().portValue().hasResume());
  
  atom().executeJob().restart();
}

void ExecuteInternalsJob::recomputeChoice() {
  // reset chosen external and time
  mChosenInternal = NULL;
  mChosenTime = TimeValue::MIN;
  
  // reinitialize real-time scheduler
  Scheduler scheduler(modelClock().time(), asap(), firstEnabled());
  Interval schedulable = mTimeSafe && Interval(mModelClock.time(), mReserver.deadline());

  const vector<AtomInternalPort *> &enabledInternals = atom().internals();

  for (vector<AtomInternalPort *>::const_iterator portIt = enabledInternals.begin() ;
       portIt != enabledInternals.end() ;
       ++portIt) {
    AtomInternalPort &port = **portIt;
    const TimingConstraint &timingConstraint = port.timingConstraint();

    Interval interv = timingConstraint.interval() &&
      schedulable;

    if (scheduler.choose(interv, false)) {
      mChosenInternal = &port;
    }
  }

  if (mChosenInternal != NULL) {
    mChosenTime = scheduler.plannedTime();
  }
  
  // mark choice as non-reset
  mResetChoice.setIsReset(false);
}

bool ExecuteInternalsJob::hasResumeEager() const {
  bool ret = false;
  
  if (atom().hadResume()) {
    const vector<AtomInternalPort *> &enabledInternals = atom().internals();
    
    for (vector<AtomInternalPort *>::const_iterator portIt = enabledInternals.begin() ;
         portIt != enabledInternals.end() ;
         ++portIt) {
      const AtomInternalPort &port = **portIt;
      const TimingConstraint &timingConstraint = port.timingConstraint();
      
      if (timingConstraint.in(atom().time()) && timingConstraint.urgency() == EAGER) {
        ret = true;
        break;
      }
    }

    for (vector<AtomExternalPort *>::const_iterator portIt = atom().externals().begin() ;
         portIt != atom().externals().end() ;
         ++portIt) {
      const AtomExternalPort &port = **portIt;
      const TimingConstraint &timingConstraint = port.timingConstraint();
      
      if (timingConstraint.in(atom().time()) && timingConstraint.urgency() == EAGER) {
        ret = true;
        break;
      }
    }
  }

  return ret;
}
