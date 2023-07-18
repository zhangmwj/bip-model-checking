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

#include <ExecuteConnectorJob.hpp>
#include "ExecuteAtomJob.hpp"

#include "Connector.hpp"
#include "Compound.hpp"
#include "InteractionValue.hpp"
#include "Port.hpp"
#include "Atom.hpp"
#include "AtomExportPort.hpp"

#include "Executer.hpp"
#include "Logger.hpp"

#include "BipError.hpp"
#include "Resetable.hpp"
#include "CycleInPriorities.hpp"
#include <TimeSafetyViolationError.hpp>
#include "CycleInPrioritiesError.hpp"

#include <TimeValue.hpp>

ExecuteConnectorJob::ExecuteConnectorJob(Connector &connector) :
  Job(Executer::jobs),
  mConnector(connector),
  mLogger(NULL),
  mReserver(*this),
  mChosenInteraction(NULL),
  mChosenTime(TimeValue::MIN) {
}

ExecuteConnectorJob::~ExecuteConnectorJob() {
}

void ExecuteConnectorJob::initialize() {
  if (!connector().hasExportedPort()) {  
    // update job of maximal interactions
    // connector().maximalInteractions().addUser(*this);
    mResetChoice.addUser(*this);
    mResetChoice.dependsOn(connector().maximalInteractions());

    // compute all the atoms involved in the connector
    mAllAtoms = allAtoms();

    // add all resources of the involved atoms
    for (vector<Atom *>::const_iterator atomIt = mAllAtoms.begin() ;
         atomIt != mAllAtoms.end() ;
         ++atomIt) {
      Atom &atom = **atomIt;
      ExecuteAtomJob &atomJob = atom.executeJob();

      for (vector<Resource *>::const_iterator resourceIt = atomJob.writer().resources().begin() ;
           resourceIt != atomJob.writer().resources().end() ;
           ++resourceIt) {
        Resource &resource = **resourceIt;

        mReserver.addResource(resource);
      }
    }

    // compute all resources used by this
    vector<Resource *> allResources = connector().maximalInteractions().allResources();

    // for all resources
    for (vector<Resource *>::const_iterator resourceIt = allResources.begin() ;
         resourceIt != allResources.end() ;
         ++resourceIt) {
      Resource &resource = **resourceIt;

      if (find(mReserver.resources().begin(),
               mReserver.resources().end(),
               &resource)
          == mReserver.resources().end()) {
        mReserver.addObservedResource(resource);
      }
    }

    if (!isRealTime()) {
      mReserver.addResource(simulationClockResource());
      connector().timeSafetyValidator().addResource(simulationClockResource());

      mUpdateClockJob.initialize();
    }
  }
}

void ExecuteConnectorJob::initializeMutexs() {
  if (!connector().hasExportedPort()) {
    mReserver.initialize();
  }
}

void ExecuteConnectorJob::realJob() {  
  // only top-level connectors can schedule interactions
  assert(!connector().hasExportedPort());

  // compute time-safe interval
  mTimeSafe = connector().timeSafetyValidator().timeSafe();

  if (hasChosen()              &&
      hasWokenUpAtWakeUpTime() &&
      !mResetChoice.isReset()  &&
      mTimeSafe.in(chosenTime())) {
    // in simulation mode interaction are executed directly without sleeping periods
    assert(isRealTime());

    // try to execute the chosen interaction
    tryToExecuteChosenInteraction();
  }
  else {      
    // update model time
    if (isRealTime() && hasResumeEagerInteraction()) {
      mModelClock.wait(connector().time());
    }
    else {
      mModelClock.update();
    }
  
    // check time-safety
    if (!mTimeSafe.in(mModelClock.time())) {
      TimeSafetyViolationError &error = *new TimeSafetyViolationError(mModelClock.time(), connector().holder().root());
      
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
        tryToExecuteChosenInteraction();
      }
    }
  }
}

void ExecuteConnectorJob::unreserveUnusedResources() {
  for (vector<Atom *>::const_iterator atomIt = mAllAtoms.begin() ;
       atomIt != mAllAtoms.end() ;
       ++atomIt) {
    Atom &atom = **atomIt;
    ExecuteAtomJob &atomJob = atom.executeJob();

    if (atomJob.isRestarted()) {
      // synchronous resume
      // if (!connector().asyncResume()) {
      //   mResumeJoiner.addJobToJoin(atomJob);
      // }

      // let start job execution
      // atomJob.unpreventEnqueuing();
    }
    else {
      atomJob.writer().free();
    }
  }
}

bool ExecuteConnectorJob::tryToExecuteChosenInteraction() {
  // try to lock dependent atoms
  bool success = mReserver.tryToReserve(chosenTime());
 
  if (success) {
    if (isRealTime()) {
      modelClock().wait(chosenTime());
    }
    else {
      mUpdateClockJob.setTime(chosenTime());
      mUpdateClockJob.restart();
    }
    
    unreserveUnusedResources();
  }
  else {
    // unreserve non involved jobs and allow start of involved ones
    // mReader.unprotect();
  }
  
  // self-restart
  restart();

  return success;
}

void ExecuteConnectorJob::executeChosenInteraction() {
  assert(hasChosen());
  
  // log the executed interaction
  logger().log(chosenInteraction(), chosenTime(), connector().maximalInteractions());

  // down
  connector().down(chosenInteraction());

  // configure execute atom jobs
  chosenInteraction().execute(chosenTime());
}

void ExecuteConnectorJob::recomputeChoice() {
  // reset chosen interaction and time
  mChosenInteraction = NULL;
  mChosenTime = TimeValue::MIN;

  // reinitialize real-time scheduler  
  Scheduler scheduler(modelClock().time(), asap(), firstEnabled());
  Interval schedulable = mTimeSafe && Interval(mModelClock.time(), mReserver.deadline());

  const vector<InteractionValue *> &interactions = connector().maximalInteractions();

  for (vector<InteractionValue *>::const_iterator interactionIt = interactions.begin() ;
       interactionIt != interactions.end() ;
       ++interactionIt) {
    InteractionValue &interaction = **interactionIt;

    Interval interv = interaction.timingConstraintAfterPriorities().interval() &&
      schedulable;
    
    if (scheduler.choose(interv, false)) {
      mChosenInteraction = &interaction;
    }
  }

  if (mChosenInteraction != NULL) {
    mChosenTime = scheduler.plannedTime();

    assert(mChosenTime != TimeValue::MIN);
  }

  // mark choice as non-reset
  mResetChoice.setIsReset(false);
}

bool ExecuteConnectorJob::hasResumeEagerInteraction() const {
  bool ret = false;
  
  if (lastAtomHasResume()) {
    const vector<InteractionValue *> &interactions = connector().maximalInteractions();
    
    for (vector<InteractionValue *>::const_iterator interactionIt = interactions.begin() ;
         interactionIt != interactions.end() ;
         ++interactionIt) {
      const InteractionValue &interaction = **interactionIt;
      const TimingConstraint &timingConstraint = interaction.timingConstraintAfterPriorities();

      // TO BE FIXED!
      // if (timingConstraint.in(connector().time()) && timingConstraint.urgency() == EAGER) {
      if (timingConstraint.wait(connector().time()).right() == connector().time()) {
        ret = true;
        break;
      }
    }
  }

  return ret;
}

bool ExecuteConnectorJob::lastAtomHasResume() const {
  bool ret = false;
  
  for (vector<Atom *>::const_iterator atomIt = mAllAtoms.begin() ;
       atomIt != mAllAtoms.end() ;
       ++atomIt) {
    Atom &atom = **atomIt;

    if (atom.hadResume() &&
        atom.time() == connector().time()) {
      ret = true;
      break;
    }
  }

  return ret;
}

vector<Atom *> ExecuteConnectorJob::allAtoms() {
  vector<Atom *> ret;

  allAtoms(ret, connector());

  return ret;
}

void ExecuteConnectorJob::allAtoms(vector<Atom *> &atoms, const Connector &connector) {
  for (vector<QuotedPortReference *>::const_iterator quotedPortIt = connector.ports().begin() ;
       quotedPortIt != connector.ports().end() ;
       ++quotedPortIt) {
    const QuotedPortReference &quotedPort = **quotedPortIt;
    const Port &port = quotedPort.port();

    allAtoms(atoms, port);
  }
}

void ExecuteConnectorJob::allAtoms(vector<Atom *> &atoms, const Port &port) {
  if (port.type() == ATOM_EXPORT) {
    const AtomExportPort &atomPort = dynamic_cast<const AtomExportPort &>(port);
    Atom &atom = atomPort.holder();

    if (find(atoms.begin(),
             atoms.end(),
             &atom)
        == atoms.end()) {
      atoms.push_back(&atom);
    }
  }
  else if (port.type() == CONNECTOR_EXPORT) {
    const ConnectorExportPort &connectorPort = dynamic_cast<const ConnectorExportPort &>(port);
    const Connector &connector = connectorPort.holder();    

    allAtoms(atoms, connector);
  }
  else if (port.type() == COMPOUND_EXPORT) {
    const CompoundExportPort &compoundPort = dynamic_cast<const CompoundExportPort &>(port);

    for (vector<Port *>::const_iterator forwardPortIt = compoundPort.forwardPorts().begin() ;
         forwardPortIt != compoundPort.forwardPorts().end() ;
         ++forwardPortIt) {
      const Port &forwardPort = **forwardPortIt;

      allAtoms(atoms, forwardPort);
    }
  }
  else {
    assert(false);
  }
}
