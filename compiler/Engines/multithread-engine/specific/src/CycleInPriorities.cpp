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

#include <CycleInPriorities.hpp>
#include <Priority.hpp>
#include <Data.hpp>
#include <AtomExportData.hpp>
#include <CompoundExportData.hpp>
#include <Compound.hpp>
#include <Connector.hpp>
#include <Interaction.hpp>
#include <CycleInPrioritiesError.hpp>
#include <Logger.hpp>

// constructors
CycleInPriorities::CycleInPriorities(const vector<Priority *> &priorities) :
  mError(false) {
  for (vector<Priority *>::const_iterator priorityIt = priorities.begin() ;
       priorityIt != priorities.end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;

    // add priority to the cycle
    mOrderedPriorities.push_back(&priority);
    mPriorities.insert(&priority);
  }
}

CycleInPriorities::CycleInPriorities(const CycleInPriorities &cycle) :
  mError(false) {
  // copy cycle
  mOrderedPriorities = cycle.mOrderedPriorities;
  mPriorities = cycle.mPriorities;
}

// destructor
CycleInPriorities::~CycleInPriorities() {
}

void CycleInPriorities::reset(const vector<Resource *> &resources) {
  setIsValid(false);
}

void CycleInPriorities::free(Resource &resource) {
  if (!isValid()) {
    validate();
  }
}

void CycleInPriorities::validate() {
  bool allResourcesFree = true;
  bool allGuardsTrue = true;
  
  for (vector<Priority *>::const_iterator priorityIt = priorities().begin() ;
       priorityIt != priorities().end() ;
       priorityIt++) {
    Priority &priority = **priorityIt;

    bool priorityResourcesFree = true;

    for (vector<AtomExportData *>::const_iterator atomExportDataIt = priority.atomData().value().begin() ;
         atomExportDataIt != priority.atomData().value().end() ;
         ++atomExportDataIt) {      
      AtomExportData &atomExportData = **atomExportDataIt;

      if (atomExportData.hasEarlyUpdate()) {
        if (atomExportData.resource().status() != Resource::FREE) {
          priorityResourcesFree = false;
          
          break;
        }
      }
      else {
        if (atomExportData.holder().resource().status() != Resource::FREE) {
          priorityResourcesFree = false;
          
          break;
        }
      }
    }

    if (priorityResourcesFree) {
      if (!priority.guard()) {
        allGuardsTrue = false;
        
        break;
      }
    }
    else {
      allResourcesFree = false;
    }
  }

  if (!allGuardsTrue) {
    setIsValid(true);
  }
  
  // a cycle in priorities has been found!
  if (allResourcesFree && allGuardsTrue) {
    bool oldError = mError.exchange(true);

    if (!oldError) {    
      CycleInPrioritiesError &error = *(new CycleInPrioritiesError());

      vector<const Interaction *> interactionsOfCycle = interactions();

      for (vector<const Interaction *>::const_iterator interactionIt = interactionsOfCycle.begin() ;
           interactionIt != interactionsOfCycle.end() ;
           ++interactionIt) {
        const Interaction &interaction = **interactionIt;

        error.addCycle(interaction);
      }

      logger().log(error);
    }
  }
}

void CycleInPriorities::initialize() {
  for (vector<Priority *>::const_iterator priorityIt = priorities().begin() ;
       priorityIt != priorities().end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;

    // add this to the cycles of priority
    priority.cycles().push_back(this);

    for (vector<AtomExportData *>::const_iterator atomExportDataIt = priority.atomData().value().begin() ;
         atomExportDataIt != priority.atomData().value().end() ;
         ++atomExportDataIt) {
      AtomExportData &atomExportData = **atomExportDataIt;

      if (atomExportData.hasEarlyUpdate()) {
        addResource(atomExportData.resource());
      }
      else {
        addResource(atomExportData.holder().resource());
      }
    }
  }
}

bool CycleInPriorities::allGuardsTrue() const {
  bool ret = true;

  for (vector<Priority *>::const_iterator priorityIt = priorities().begin() ;
       priorityIt != priorities().end() ;
       priorityIt++) {
    Priority &priority = **priorityIt;

    if (!priority.guard()) {
      ret = false;
      break;
    }
  }

  return ret;
}

vector<const Interaction *> CycleInPriorities::interactions() const {
  vector<const Interaction *> ret;

  for (size_t i = 0 ; i <= priorities().size() ; ++i) {
    Priority &priority = *priorities()[i % priorities().size()];
    Priority &lowerPriority = *priorities()[(i - 1) % priorities().size()];
    Priority &higherPriority = *priorities()[(i + 1) % priorities().size()];

    Interaction &lowInteraction = getLowInteraction(priority, lowerPriority);
    Interaction &highInteraction = getHighInteraction(priority, higherPriority);

    if (!ret.empty()) {
      // check if low interaction is already in ret
      const Interaction &lastInteraction = *(ret[ret.size() - 1]);

      if (lowInteraction != lastInteraction) {
        ret.push_back(&lowInteraction);
      }
    }
    else {
      ret.push_back(&lowInteraction);
    }

    if (i < priorities().size()) {
      ret.push_back(&highInteraction);
    }
  }

  return ret;
}

Interaction &CycleInPriorities::getLowInteraction(const Priority &priority, const Priority &lowerPriority) const {
  if (priority.hasLow()) {
    return priority.low();
  }
  else {
    if (lowerPriority.hasHigh()) {
      if (lowerPriority.high().hasPorts()) {
        return lowerPriority.high();
      }
      else {
        return getMaximalInteraction(lowerPriority.high().connector());
      }
    }
    else {
      assert(priority.hasHigh());
      assert(lowerPriority.hasLow());

      return getMatchingWildcard(priority.high().connector(),
                                 lowerPriority.low().connector());
    }
  }
}

Interaction &CycleInPriorities::getHighInteraction(const Priority &priority, const Priority &higherPriority) const {
  if (priority.hasHigh()) {
    if (priority.high().hasPorts()) {
      return priority.high();
    }
    else {
      if (higherPriority.hasLow()) {
        return higherPriority.low();
      }
      else {
        return getMaximalInteraction(priority.high().connector());
      }
    }
  }
  else {
    if (higherPriority.hasLow()) {
      return higherPriority.low();
    }
    else {
      assert(priority.hasLow());
      assert(higherPriority.hasHigh());

      return getMatchingWildcard(priority.low().connector(),
                                 higherPriority.high().connector());
    }
  }
}

Interaction &CycleInPriorities::getMatchingWildcard(const Connector &connector1, const Connector &connector2) const {
  assert(&connector1.holder() == &connector2.holder());

  const Compound &compound = connector1.holder();

  Connector *matchingConnector = NULL;

  for (map<string, Connector *>::const_iterator connectorIt = compound.connectors().begin() ;
       connectorIt != compound.connectors().end() ;
       ++connectorIt) {
    Connector &connector = *connectorIt->second;

    if (connector.isTopLevel() &&
        &connector != &connector1 &&
        &connector != &connector2) {
      matchingConnector = &connector;
    }
  }

  assert(matchingConnector != NULL);

  return getMaximalInteraction(*matchingConnector);
}

Interaction &CycleInPriorities::getMaximalInteraction(const Connector &connector) const {
  vector<Port *> allPorts;

  for (vector<QuotedPortReference *>::const_iterator portRefIt = connector.ports().begin() ;
       portRefIt != connector.ports().end() ;
       ++portRefIt) {
    const QuotedPortReference &portRef = **portRefIt;
    Port &port = portRef.port();
           
    allPorts.push_back(&port);
  }

  return connector.createInteraction(allPorts);
}
