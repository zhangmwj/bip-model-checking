/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 *  Anakreontas Mentis
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

#include <Compound.hpp>
#include <Atom.hpp>
#include <Interaction.hpp>
#include <InteractionValue.hpp>
#include <ConnectorExportPort.hpp>
#include <QuotedPortReference.hpp>
#include <Priority.hpp>
#include <BipError.hpp>
#include <Interval.hpp>
#include <Atom.hpp>

// constructors
Compound::Compound(const string &name) :
  ComponentItf(name, COMPOUND),
  Component(name, COMPOUND),
  CompoundItf(name),
  mDisableMaximalProgress(false) {
  /* implement your constructor here */
}

// destructor
Compound::~Compound() {
  /* implement your destructor here */
}

/* \brief Execute the interaction/transition corresponding to a port value.
 *
 * \param portValue is the target port value, it must be a port value
 * associated to one of the exported ports.
 *
 * \return An error if found during the execution of involved atoms or
 * during the update of port values, BipError::NoError otherwise.
 */
BipError &Compound::execute(PortValue &portValue, const TimeValue &time) {
  // find the port from which comes the port value
#ifndef NDEBUG
  bool found = false;
#endif
  for (map<string, CompoundExportPort *>::const_iterator portIt = ports().begin() ;
       portIt != ports().end() ;
       ++portIt) {
    CompoundExportPort &port = *portIt->second;

    // if the port value is associated to port
    if (port.hasPortValue(portValue)) {
      // the port value must be associated to a single port
      assert(!found);

      // execute
      BipError &error = port.execute(portValue, time);

      if (error.type() != NO_ERROR) {
        return error;
      }

#ifndef NDEBUG
      found = true;
#endif
    }
  }

  // port value must belong to one of the ports
  assert(found);

  // update the port values of the component
  return update();
}

/* \brief Execute an interaction value of a connector of a compound.
 *
 * \param interactionValue is the target interaction value, it must be an
 * interaction value of a top-level connector.
 *
 * \return An error if found during the execution of involved atoms or
 * during the update of port values, BipError::NoError otherwise.
 */
BipError &Compound::execute(InteractionValue &interactionValue, const TimeValue &time) {
  // execute the interaction
  BipError &error = interactionValue.execute(time);

  if (error.type() != NO_ERROR) {
    return error;
  }

  // update the port values of the component
  return update();
}

BipError &Compound::execute(InteractionValue &interactionValue) {
  // execute the interaction
  BipError &error = interactionValue.execute();

  if (error.type() != NO_ERROR) {
    return error;
  }

  // update the port values of the component
  return update();
}

/* \brief Initialize the compound component.
 *
 * Recursively calls initialize of all components, and updates
 * port values of the compound 'this'.
 *
 * \return An error if found during the initialization of the involved
 * components or during the update of port values, BipError::NoError otherwise.
 */
BipError &Compound::initialize() {
  // recursive call to sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin();
       componentIt != components().end();
       ++componentIt) {
    Component &component = *componentIt->second;
    BipError &error = component.initialize();

    if (error.type() != NO_ERROR) {
      return error;
    }
  }

  // update the port values of the component
  return update();
}

void Compound::initializeAllAtomExternalPorts() {
  // recursive call to sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;
    
    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      compound.initializeAllAtomExternalPorts();
    }
    else if (component.type() == ATOM) {
      const Atom &atom = dynamic_cast<Atom &>(component);

      for (map<string, AtomExternalPort *>::const_iterator portIt = atom.externalPorts().begin() ;
           portIt != atom.externalPorts().end() ;
           ++portIt) {
        AtomExternalPort &port = *portIt->second;

        port.initialize();
      }
    }
  }
}

vector<Constraint> Compound::allTimingConstraints() const {
  vector<Constraint> ret;
  // recursive call to sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin();
       componentIt != components().end();
       ++componentIt) {
    Component &component = *componentIt->second;
    vector<Constraint> tmp = component.allTimingConstraints();
    ret.insert(ret.end(), tmp.begin(), tmp.end());
  }
  return ret;
}

/**
 * \brief Update port values of connectors and exported ports.
 *
 * Update port values of exported ports of connectors, exported ports of compound
 * 'this'.
 * Require that port values of component exported ports of 'this' are up-to-date.
 *
 * \return An instance of CycleInPrioritiesError if a cycle has been found
 * in priorities, BipError::NoError otherwise.
 */
BipError &Compound::update() {
  // detect cycles in priorities (throw a CycleInPrioritiesException if needed)
  BipError &error = detectCycleInPriorities();

  if (error.type() != NO_ERROR) {
    return error;
  }

  // update port values of all connectors
  updatePortValuesOfConnectors();

  // update port values of all exported ports
  updatePortValuesOfExportedPorts();

  return BipError::NoError;
}

/**
 * \brief Update port values of connectors and exported ports.
 *
 * Update recursively port values of exported ports of connectors, exported
 * ports of compound 'this'.
 *
 * \return An instance of CycleInPrioritiesError if a cycle has been found
 * in priorities, BipError::NoError otherwise.
 */
BipError &Compound::recursiveUpdate() {
  // recursive call to sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      BipError &error = compound.recursiveUpdate();

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
  }

  return update();
}

/**
 * \brief Compute current interactions of non-exported connectors.
 *
 * It also includes interactions of sub-components, that is, the computation
 * is recursive.
 */
vector<InteractionValue *> Compound::interactions(bool MC) const {
  vector<InteractionValue *> ret;

  // get interactions of sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      vector<InteractionValue *> interactionsOfCompound = compound.interactions(MC);

      // add to ret
      ret.insert(ret.end(),
                 interactionsOfCompound.begin(),
                 interactionsOfCompound.end());
    }
  }

  // get interactions of top level non exported connectors
  for (map<string, Connector *>::const_iterator connectorIt = connectors().begin() ;
       connectorIt != connectors().end() ;
       ++connectorIt) {
    Connector &connector = *connectorIt->second;
    
    // keep only interactions of non exported connectors, interactions of exported
    // connector will be handled at higher levels
    if (!connector.hasExportedPort()) {
      const vector<InteractionValue *> interactionsOfConnector = MC? connector.enabledInteractions(MC) : connector.maximalInteractions();

      // add to ret
      ret.insert(ret.end(),
                 interactionsOfConnector.begin(),
                 interactionsOfConnector.end());
    }
  }

  return ret;
}


/**
 * \brief Compute current enabled non-exported internal ports.
 *
 * It also includes internals ports of atom of sub-components, that is,
 * the computation is recursive.
 */
vector<AtomInternalPort *> Compound::internals() const {
  vector<AtomInternalPort *> ret;

  // get interactions of sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;
    vector<AtomInternalPort *> internalsOfComponent = component.internals();

    // add to ret
    ret.insert(ret.end(),
               internalsOfComponent.begin(),
               internalsOfComponent.end());
  }

  return ret;
}


/**
 * \brief Compute the timing constraint corresponding to invariants.
 *
 * 
 *
 * \return The timing constraint corresponding to invariants.
 */
Interval Compound::invariant() const {
  Interval ret = Interval(TimeValue::MIN, TimeValue::MAX);

  // get interactions of sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      // intersect with local timing constraint of component
      ret &= compound.invariant();
    }
    else if (component.type() == ATOM) {
      Atom &atom = dynamic_cast<Atom &>(component);

      // intersect with local timing constraint of component
      if (atom.hasResume()) {
        ret &= atom.resume();
      }
      else if (atom.hasInvariant()) {
        ret &= atom.invariant();
      }
    }
    else {
      assert(false);
    }
  }

  return ret;
}

const Constraint Compound::invariantConstraint() const {
  Constraint ret = true;

  // get interactions of sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin();
       componentIt != components().end();
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      // intersect with local timing constraint of component
      ret &= compound.invariantConstraint();
    } else if (component.type() == ATOM) {
      Atom &atom = dynamic_cast<Atom &>(component);
      ret &= atom.invariantConstraint();
    } else {
      assert(false);
    }
  }

  return ret;
}

/**
 * \brief Compute the timing constraint corresponding to resume transitions.
 *
 * 
 *
 * \return The timing constraint corresponding to resume transitions.
 */
Interval Compound::resume() const {
  Interval ret = Interval(TimeValue::MIN, TimeValue::MAX);

  // get interactions of sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      // intersect with local timing constraint of component
      ret &= compound.resume();
    }
    else if (component.type() == ATOM) {
      Atom &atom = dynamic_cast<Atom &>(component);

      // intersect with local timing constraint of component
      if (atom.hasResume()) {
        ret &= atom.resume();
      }
    }
    else {
      assert(false);
    }
  }

  return ret;
}

/**
 * \brief Resume atomic components of this and lower levels compound components.
 *
 * \return An error if one occurred during the resume, BipError::NoError otherwise.
 */
BipError &Compound::resume(const TimeValue &time) {
  if (hasResume()) {
    for (map<string, Component *>::const_iterator componentIt = components().begin() ;
         componentIt != components().end() ;
         ++componentIt) {
      Component &component = *componentIt->second;

      if (component.type() == COMPOUND) {
        Compound &compound = dynamic_cast<Compound &>(component);
      
        // resume component if needed
        BipError &error = compound.resume(time);

        if (error.type() != NO_ERROR) {
          return error;
        }
      }
      else if (component.type() == ATOM) {
        Atom &atom = dynamic_cast<Atom &>(component);

        // resume component if needed
        if (atom.hasResume()) {
          BipError &error = atom.resume(time);

          if (error.type() != NO_ERROR) {
            return error;
          }

          // reset resume attribute
          atom.setHasResume(false);
        }
      }
      else {
        assert(false);
      }
    }

    // update the port values of the component
    update();
  }

  return BipError::NoError;
}


/**
 * \brief Compute the timing constraint corresponding to resume transitions.
 *
 * 
 *
 * \return The timing constraint corresponding to resume transitions.
 */
bool Compound::hasResume() const {
  bool ret = false;

  // get interactions of sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      ret |= compound.hasResume();
    }
    else if (component.type() == ATOM) {
      Atom &atom = dynamic_cast<Atom &>(component);

      ret |= atom.hasResume();
    }
    else {
      assert(false);
    }
  }

  return ret;
}


/**
 * \brief Compute current enabled external ports.
 *
 * It also includes external ports of atom of sub-components, that is,
 * the computation is recursive.
 */
vector<AtomExternalPort *> Compound::allExternals() const {
  vector<AtomExternalPort *> ret;

  // get interactions of sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;
    vector<AtomExternalPort *> externalsOfComponent = component.allExternals();

    // add to ret
    ret.insert(ret.end(),
               externalsOfComponent.begin(),
               externalsOfComponent.end());
  }

  return ret;
}


void Compound::setTime(const TimeValue &time) {
  // logical time cannot decrease
  assert(mTime <= time);

  // assert(waitInterval()); ...

  // assign new value to the logical time
  mTime = time;

  // update sub-components recursively
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      compound.setTime(time);
    }
  }

  // update
  //update();
}


/**
 * \brief Detects if there a cycle in the priorities.
 *
 * Priorities are defined as the transitive closure of the union of maximal
 * progress (i.e. inclusion of interactions values implemented by operator<)
 * and user-defined priority rules (i.e. instances of Priority given by
 * priorities()).
 *
 * \return An instance of CycleInPrioritiesError if a cycle has been found
 * in priorities, BipError::NoError otherwise.
 */
BipError &Compound::detectCycleInPriorities() const {
  for (vector<Priority *>::const_iterator priorityIt = priorities().begin() ;
       priorityIt != priorities().end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;

    // check for a cycle from priority rule 'priority'
    BipError &error = priority.detectCycle();

    if (error.type() != NO_ERROR) {
      return error;
    }
  }

  return BipError::NoError;
}


/**
 * \brief Update port values of connectors.
 *
 * Update port values of exported ports of connectors.
 * Require that port values of component exported ports are up-to-date.
 */
void Compound::updatePortValuesOfConnectors() {
  // list of connectors already updated
  set<Connector *> updatedConnectors;

  // update port values of all connectors
  for (map<string, Connector *>::const_iterator connectorIt = connectors().begin() ;
       connectorIt != connectors().end() ;
       ++connectorIt) {
    Connector &connector = *connectorIt->second;

    // subconnectors of connector in hierarchical order from bottom to top
    vector<Connector *> subconnectors = connector.allSubConnectors();

    // add connector for updating it in the end
    subconnectors.push_back(&connector);

    for (vector<Connector *>::const_iterator updateConnIt = subconnectors.begin() ;
         updateConnIt != subconnectors.end() ;
         ++updateConnIt) {
      Connector &updateConnector = **updateConnIt;

      // check if updateConnector has been already updated
      if (updatedConnectors.find(&updateConnector) == updatedConnectors.end()) {
        // update port values of updateConnector
        updateConnector.updatePortValues();

        // add updateConnector to the set of updated connectors
        updatedConnectors.insert(&updateConnector);
      }
    }
  }
}


/**
 * \brief Update port values of the exported ports.
 *
 * Update port values of exported ports of compound 'this'.
 * Require that port values of component exported ports and port values of
 * connector exported ports are up-to-date.
 */
void Compound::updatePortValuesOfExportedPorts() {
  for (map<string, CompoundExportPort *>::const_iterator portIt = ports().begin() ;
       portIt != ports().end() ;
       ++portIt) {
    CompoundExportPort &port = *portIt->second;

    port.updatePortValues();
  }
}


/**
 * \brief Set the disable-maximal-progress option for 'this' and all the
 * sub-level compounds.
 *
 * \param disableMaximalProgress corresponds to the new value for the diable
 * disable-maximal-progress option.
 */
void Compound::setDisableMaximalProgressForAllSubCompounds(bool disableMaximalProgress) {
  // set the disable-maximal-progress option for 'this'
  setDisableMaximalProgress(disableMaximalProgress);

  // set the disable-maximal-progress option recursively for all sub-level compounds
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);
      
      compound.setDisableMaximalProgressForAllSubCompounds(disableMaximalProgress);
    }
  }
}
