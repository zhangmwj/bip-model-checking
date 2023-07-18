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

#include <AtomTimeSafetyValidator.hpp>
#include <Logger.hpp>
#include <TimeSafetyViolationError.hpp>
#include <Atom.hpp>
#include <Port.hpp>
#include <AtomExportPort.hpp>
#include <AtomInternalPort.hpp>
#include <AtomExternalPort.hpp>


// constructors
AtomTimeSafetyValidator::AtomTimeSafetyValidator(Atom &atom) :
  mAtom(atom),
  mMissingResources(0),
  mTimeSafe(Interval(TimeValue::MIN, TimeValue::MAX)) {
}

// destructor
AtomTimeSafetyValidator::~AtomTimeSafetyValidator() {
}

void AtomTimeSafetyValidator::reset(const vector<Resource *> &reservedResources) {
  bool hasResume = false;
  bool resuming = false;
  
  for (vector<Resource *>::const_iterator resourceIt = reservedResources.begin() ;
       resourceIt != reservedResources.end() ;
       ++resourceIt) {
    Resource &resource = **resourceIt;
    
    assert(resource.status() == Resource::RESERVED);
    
    // atom resources: count the number of resume atoms
    if (&resource == &atom().resource()) {
      if (atom().hasResume()) {
        hasResume = true;
      }
    }

    if (&resource == &atom().resumeResource()) {
      resuming = true;
    }
    
    if (find(resources().begin(),
             resources().end(),
             &resource)
        != resources().end()) {
      mMissingResources.fetch_add(1);
    }
  }
  
  if (!resuming) {
    if (!hasResume && mMissingResources.load() == 0) {
      assert(false);
      mReserve.unlock();
    }
    else {
      setIsValid(false);

      if (hasResume) {
        // /!\ should perform a setIsValid(false) before to be effective
        setValid(TimeValue::MAX);
      }
      else {
        assert(mMissingResources.load() > 0);
      }
    }
  }
}

void AtomTimeSafetyValidator::free(Resource &resource) {
  assert(find(resources().begin(),
              resources().end(),
              &resource)
         != resources().end());

  if (&resource == &atom().resource()) {
    if (atom().hadResume()) {
      setIsValid(false);
    }
  }
  
  unsigned int oldMissingResources = mMissingResources.fetch_sub(1);
  
  if (oldMissingResources == 1) {
    validate();
  }
}

void AtomTimeSafetyValidator::validate() {
  assert(!isValid());
      
  TimeValue time = atom().time();
  Interval wait = Interval(time, TimeValue::MAX);

  // take into timing constraints of internal ports
  const vector<AtomInternalPort *> &enabledInternals = atom().internals();

  for (vector<AtomInternalPort *>::const_iterator portIt = enabledInternals.begin() ;
       portIt != enabledInternals.end() ;
       ++portIt) {
    const AtomInternalPort &port = **portIt;
    const TimingConstraint &timingConstraint = port.timingConstraint();

    assert(port.hasPortValue());
    assert(!timingConstraint.empty());

    wait &= timingConstraint.wait(time);
  }

  // take into timing constraints of external ports
  for (vector<AtomExternalPort *>::const_iterator portIt = atom().externals().begin() ;
       portIt != atom().externals().end() ;
       ++portIt) {
    const AtomExternalPort &port = **portIt;

    if (port.waiting()) {
      wait &= port.timingConstraint().wait(time);
    }
  }

  // urgencies ensure this
  assert(!wait.rightOpen());

  if (atom().hasInvariant()) {
    setTimeSafe(wait && atom().invariant());
  }
  else {
    setTimeSafe(wait);
  }
  
  setValid(wait.right());
}

void AtomTimeSafetyValidator::initialize() {
  const ExecuteAtomJob &atomJob = atom().executeJob();
  
  // compute all atoms resource
  for (vector<Resource *>::const_iterator resourceIt = atomJob.writer().resources().begin() ;
         resourceIt != atomJob.writer().resources().end() ;
         ++resourceIt) {
    Resource &resource = **resourceIt;

    addResource(resource);
  }

  // resume resources
  addResource(atom().resumeResource());
}
