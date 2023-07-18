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

#include <Atom.hpp>
#include <Compound.hpp>
#include <BipError.hpp>
#include "ExecuteAtomJob.hpp"
#include <Connector.hpp>
#include <CycleInPriorities.hpp>
#include <CycleInPrioritiesError.hpp>
#include <BipError.hpp>
#include <UnexpectedEventError.hpp>

// constructors
Atom::Atom(const string &name) :
  ComponentItf(name, ATOM),
  Component(name, ATOM),
  AtomItf(name),
  mInternals(this, &Atom::recomputeInternals),
  mExecuteJob(*this),
  mExecuteInternalsJob(*this),
  mExecuteExternalsJob(*this),
  mTimeSafetyValidator(*this),
  mHasResume(false),
  mHadResume(false) {
  mInvariantAndTimeReset.addResource(mResource);
}

Atom::Atom(const string &name, const bool &initialHasResume) :
  ComponentItf(name, ATOM),
  Component(name, ATOM),
  AtomItf(name, initialHasResume),
  mInternals(this, &Atom::recomputeInternals),
  mExecuteJob(*this),
  mExecuteInternalsJob(*this),
  mExecuteExternalsJob(*this),
  mTimeSafetyValidator(*this),
  mHasResume(false),
  mHadResume(false) {
  mInvariantAndTimeReset.addResource(mResource);
}

// destructor
Atom::~Atom() {
  /* implement your destructor here */
}

/* \brief Execute an internal port.
 *
 * \param internalPort is the target internal port, it should be an internal
 * port of atom 'this'.
 *
 * \return An error if found during the execution of the corresponding
 * transition, BipError::NoError otherwise.
 */
BipError &Atom::execute(AtomInternalPort &internalPort, const TimeValue &time) {
  // execute
  BipError &error = execute(internalPort.portValue(), time);

  if (error.type() != NO_ERROR) {
    return error;
  }

  // reset the interface ports
  // reset();

  return BipError::NoError;
}

void Atom::allNotReady() {
  // mark all exported ports as ready
  for (map<string, AtomExportPort *>::const_iterator portIt = ports().begin() ;
       portIt != ports().end() ;
       ++portIt) {
    AtomExportPort &port = *portIt->second;

    port.unsetReady();
  }

  // mark all exported data as ready
  for (map<string, AtomExportData *>::const_iterator dataIt = data().begin() ;
       dataIt != data().end() ;
       ++dataIt) {
    AtomExportData &data = *dataIt->second;
    
    data.unsetReady();
  }
}

void Atom::allReady() {
  // mark all exported ports as ready
  for (map<string, AtomExportPort *>::const_iterator portIt = ports().begin() ;
       portIt != ports().end() ;
       ++portIt) {
    AtomExportPort &port = *portIt->second;

    port.setReady();
  }

  // mark all exported data as ready
  for (map<string, AtomExportData *>::const_iterator dataIt = data().begin() ;
       dataIt != data().end() ;
       ++dataIt) {
    AtomExportData &data = *dataIt->second;

    data.setReady();
  }

  // reset internal ports
  for (map<string, AtomInternalPort *>::const_iterator portIt = internalPorts().begin() ;
       portIt != internalPorts().end() ;
       ++portIt) {
    AtomInternalPort &port = *portIt->second;

    // force recomputation of timing constraints
    // and mInternals that depends on internal ports
    // TO BE OPTIMIZED LATER
    port.reset();
  }

  // reset invariant and time dependent values  
  mInvariantAndTimeReset.resetDependent();

  // reset enabled internal ports
  mInternals.reset();
}

  
BipError &Atom::checkExternals() {
  vector<AtomExternalPort *>::iterator portIt = mWaiting.begin();

  // check incoming events on waiting ports
  while (portIt != mWaiting.end()) {
    AtomExternalPort &port = **portIt;

    assert(port.waiting());

    bool checkRemainingEvents = false;
    bool alreadyNextPort = false;

    do {
      // /!\ hasEvent() may change at any time
      // to keep consistency we take a snapshot of
      // its current value here.
      bool snapshotHasEvent = port.hasEvent();

      checkRemainingEvents = false;
      alreadyNextPort = false;

      if (snapshotHasEvent) {
        // force recomputation of port timing constaint
        port.reset();

        if (port.hasExpectedEvent()) {
          assert(!port.timingConstraint().empty());

          // add port to the executable external ports
          mExternals.push_back(&port);
          mExternalsReset.resetDependent();

          // remove port of the waiting external ports & update ready queue
          portIt = mWaiting.erase(portIt);
          mExecuteExternalsJob.readyQueue().removeSporadicPush(1);

          // inform that there is no need for incrementing portIt
          alreadyNextPort = true;
        }
        else if (true) { // TO BE DONE: EARLY EVENT! (port.eventTime() <= planningInterval.right()) { // !hasEarlyEvent
          if (port.policy() == REMEMBER) {
            // nothing to do in this case!
          }
          else if (port.policy() == IGNORE) {
            port.popEvent();
            checkRemainingEvents = true;
          }
          else if (port.policy() == ERROR) {
            BipError &error = *new UnexpectedEventError(port.holder(), port);
            return error;
          }
          else {
            assert(false);
          }
        }
      }

      assert(!(checkRemainingEvents && alreadyNextPort));
    } while (checkRemainingEvents);

    // next port
    if (!alreadyNextPort) {
      ++portIt;
    }
  }

  // check incoming events on unexpected ports
  for (vector<AtomExternalPort*>::const_iterator unexpectedIt = mUnexpected.begin() ;
       unexpectedIt != mUnexpected.end() ;
       ++unexpectedIt) {
    AtomExternalPort &unexpectedPort = **unexpectedIt;

    if (unexpectedPort.hasEvent()) {
      if (true) { // TO BE DONE: EARLY EVENT! (port.eventTime() <= planningInterval.right()) { // !hasEarlyEvent if (unexpectedPort.eventTime() <= planningInterval.right()) { // !hasEarlyEvent
        if (unexpectedPort.policy() == REMEMBER) {
          // nothing to do in this case!
        }
        else if (unexpectedPort.policy() == IGNORE) {
          unexpectedPort.purgeEvents();
        }
        else if (unexpectedPort.policy() == ERROR) {
          BipError &error = *new UnexpectedEventError(unexpectedPort.holder(), unexpectedPort);
          return error;
        }
        else {
          assert(false);
        }
      }
    }
  }

  return BipError::NoError;
}

BipError &Atom::recomputeExternals() {
  // inform the ready queue on the number of waiting ports
  mExecuteExternalsJob.readyQueue().removeSporadicPush(mWaiting.size());

  // recompute from scratch
  mExternals.clear();
  mWaiting.clear();
  mUnexpected.clear();

  // loop on external ports
  for (map<string, AtomExternalPort *>::const_iterator portIt = externalPorts().begin() ;
       portIt != externalPorts().end() ;
       ++portIt) {
    AtomExternalPort &port = *portIt->second;
    
    if (port.waiting()) {
      if (port.hasInterval()) {
        if (port.interval().next(modelClock().time()) != TimeValue::MAX) {
          mWaiting.push_back(&port);
        }
        else {
          mUnexpected.push_back(&port);
        }
      }
      else {
        mWaiting.push_back(&port);
      }
    }
    else {
      mUnexpected.push_back(&port);
    }
  }

  // inform the ready queue on the number of waiting ports
  mExecuteExternalsJob.readyQueue().addSporadicPush(mWaiting.size());

  return checkExternals();
}

void Atom::recomputeInternals(vector<AtomInternalPort *> &internals) const {
  // recompute from scratch
  internals.clear();

  // loop on intenal ports
  for (map<string, AtomInternalPort *>::const_iterator portIt = internalPorts().begin() ;
       portIt != internalPorts().end() ;
       ++portIt) {
    AtomInternalPort &port = *portIt->second;

    if (!port.isExported()) { // TO BE OPTIMIZED LATER
      if (port.hasPortValue()) {
        const TimingConstraint &timingConstraint = port.timingConstraint();

        if (!timingConstraint.empty()) {
          internals.push_back(&port);
        }
      }
    }
  }
}
  
ostream& operator<<(ostream &o, const Atom &atom) {
  return o << atom.toString();
}

ostream& operator<<(ostream &o, const Atom *atom) {
  return o << atom->toString();
}
