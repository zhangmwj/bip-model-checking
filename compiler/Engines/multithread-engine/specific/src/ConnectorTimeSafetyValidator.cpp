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

#include <ConnectorTimeSafetyValidator.hpp>
#include <Logger.hpp>
#include <Connector.hpp>
#include <TimeSafetyViolationError.hpp>
#include <Atom.hpp>
#include <Port.hpp>
#include <AtomExportPort.hpp>
#include <ConnectorExportPort.hpp>
#include <CompoundExportPort.hpp>

// constructors
ConnectorTimeSafetyValidator::ConnectorTimeSafetyValidator(const Connector &connector) :
  mConnector(connector),
  mMissingResources(0),
  mResume(0) {
}

// destructor
ConnectorTimeSafetyValidator::~ConnectorTimeSafetyValidator() {
}

void ConnectorTimeSafetyValidator::reset(const vector<Resource *> &reservedResources) {
  assert(mReserve.isLocked());

  bool resuming = false;
  
  for (vector<Resource *>::const_iterator resourceIt = reservedResources.begin() ;
       resourceIt != reservedResources.end() ;
       ++resourceIt) {
    Resource &resource = **resourceIt;
    
    assert(resource.status() == Resource::RESERVED);

    // atom resources: count the number of resume atoms
    if (isAtomResource(resource)) {
      if (atom(resource).hasResume()) {
        mResume.fetch_add(1);
      }
    }
    
    if (isAtomResumeResource(resource)) {
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
    if (mResume.load() == 0 && mMissingResources.load() == 0) {
      assert(false);
      mReserve.unlock();
    }
    else {
      setIsValid(false);

      if (mResume.load() > 0) {
        // /!\ should perform a setIsValid(false) before to be effective
        setValid(TimeValue::MAX);
      }
      else {
        assert(mMissingResources.load() > 0);
      }
    }
  }
}

void ConnectorTimeSafetyValidator::free(Resource &resource) {
  assert(find(resources().begin(),
              resources().end(),
              &resource)
         != resources().end());
  
  // atom resources: count the number of resume atoms
  if (isAtomResource(resource)) {
    if (atom(resource).hadResume()) {      
      unsigned int oldResume = mResume.fetch_sub(1);

      if (oldResume == 1) {
        setIsValid(false);
      }
    }
  }
    
  unsigned int oldMissingResources = mMissingResources.fetch_sub(1);

  if (oldMissingResources == 1) {
    validate();
  }
}

void ConnectorTimeSafetyValidator::validate() {    
  assert(!isValid());
      
  TimeValue time = connector().time();
  Interval wait = Interval(time, TimeValue::MAX);
    
  const vector<InteractionValue *> &interactions = connector().maximalInteractions();
    
  for (vector<InteractionValue *>::const_iterator interactionIt = interactions.begin() ;
       interactionIt != interactions.end() ;
       ++interactionIt) {
    const InteractionValue &interaction = **interactionIt;
    const TimingConstraint &constraint = interaction.timingConstraintAfterPriorities();
    
    assert(!constraint.empty());
        
    wait &= constraint.wait(time);
  }

  // urgencies ensure this
  assert(!wait.rightOpen());

  setTimeSafe(wait && connector().invariant());
  setValid(wait.right());
}

void ConnectorTimeSafetyValidator::initialize() {
  if (!connector().hasExportedPort()) {    
    // compute all the atoms involved in the connector
    mAllAtoms = allAtoms();

    // compute all atoms resource
    for (vector<Atom *>::const_iterator atomIt = mAllAtoms.begin() ;
         atomIt != mAllAtoms.end() ;
         ++atomIt) {
      Atom &atom = **atomIt;
      
      addResource(atom.resource());
      addResource(atom.resumeResource());
      
      mAllAtomResources.push_back(&atom.resource());
      mAllAtomResumeResources.push_back(&atom.resumeResource());
    }

    // compute all necessary to compute maximal interactions
    vector<Resource *> allResources = connector().maximalInteractions().allResources();

    // add all resources necessary to compute maximal interactions
    for (vector<Resource *>::const_iterator resourceIt = allResources.begin() ;
         resourceIt != allResources.end() ;
         ++resourceIt) {
      Resource &resource = **resourceIt;

      addResource(resource);
      mAllConnectorResources.push_back(&resource);
    }
  }
}

vector<Atom *> ConnectorTimeSafetyValidator::allAtoms() {
  vector<Atom *> ret;

  allAtoms(ret, connector());

  return ret;
}

bool ConnectorTimeSafetyValidator::isAtomResource(const Resource &resource) const {
  return find(mAllAtomResources.begin(),
              mAllAtomResources.end(),
              &resource)
    != mAllAtomResources.end();  
}

bool ConnectorTimeSafetyValidator::isAtomResumeResource(const Resource &resource) const {
  return find(mAllAtomResumeResources.begin(),
              mAllAtomResumeResources.end(),
              &resource)
    != mAllAtomResumeResources.end();  
}

bool ConnectorTimeSafetyValidator::isConnectorResource(const Resource &resource) const {
  return find(mAllConnectorResources.begin(),
              mAllConnectorResources.end(),
              &resource)
    != mAllConnectorResources.end();  
}

Atom &ConnectorTimeSafetyValidator::atom(const Resource &resource) const {
  // should be an atom resource
  assert(isAtomResource(resource));

  vector<Resource *>::const_iterator resourceIt =
    find(mAllAtomResources.begin(),
         mAllAtomResources.end(),
         &resource);

  size_t i = resourceIt - mAllAtomResources.begin();

  Atom &ret = *mAllAtoms[i];

  assert(&(ret.resource()) == &resource);

  return ret;
}

void ConnectorTimeSafetyValidator::allAtoms(vector<Atom *> &atoms, const Connector &connector) {
  for (vector<QuotedPortReference *>::const_iterator quotedPortIt = connector.ports().begin() ;
       quotedPortIt != connector.ports().end() ;
       ++quotedPortIt) {
    const QuotedPortReference &quotedPort = **quotedPortIt;
    const Port &port = quotedPort.port();

    allAtoms(atoms, port);
  }
}

void ConnectorTimeSafetyValidator::allAtoms(vector<Atom *> &atoms, const Port &port) {
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
