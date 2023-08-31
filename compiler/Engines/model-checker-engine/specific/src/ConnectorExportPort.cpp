/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 *  Braham-Lotfi Mediouni (braham-lotfi.mediouni@univ-grenoble-alpes.fr)
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

#include <ConnectorExportPort.hpp>
#include <Connector.hpp>
#include <PortValue.hpp>
#include <InteractionValue.hpp>
#include <BipError.hpp>
#include <TimingConstraint.hpp>

// constructors
ConnectorExportPort::ConnectorExportPort(const string &name) :
  PortItf(name, CONNECTOR_EXPORT),
  Port(name, CONNECTOR_EXPORT),
  ConnectorExportPortItf(name) {
  /* implement your constructor here */
}

// destructor
ConnectorExportPort::~ConnectorExportPort() {
  for (map<PortValue *, InteractionValue *>::const_iterator pairIt = mappedPortValues().begin() ;
       pairIt != mappedPortValues().end() ;
       ++pairIt) {
    PortValue &portValue = *pairIt->first;
    InteractionValue *interaction = pairIt->second;

    if (portValue.hasInterval()) {
      delete &portValue.interval();
    }

    // delete interaction value (cannot call release in this case
    // because it is called when deleting the corresponding connector)
    delete interaction;
  }
}

bool ConnectorExportPort::hasResumeFor(PortValue &value) {
  return interaction(value).hasResume();
}


string ConnectorExportPort::getDistribution(PortValue &value){
// should be mapped
  assert(mappedPortValues().find(&value) != mappedPortValues().end());

  // get the interaction
  InteractionValue &interaction = *mappedPortValues()[&value];

  return interaction.getDistribution();
}


  AtomInternalPort *ConnectorExportPort::getStochasticPort(PortValue &value) {
// should be mapped
  assert(mappedPortValues().find(&value) != mappedPortValues().end());

  // get the interaction
  InteractionValue &interaction = *mappedPortValues()[&value];

  return interaction.getStochasticPort();
}

/**
 * \brief Execute the interaction corresponding to a port value.
 *
 * The execution of an interaction is performed by method
 * execute() of the corresponding interaction which executes
 * all the components and connectors involved in the interaction.
 *
 * \param portValue is the target port value; it must be a port value
 * exported by 'this'
 */
BipError &ConnectorExportPort::execute(PortValue &portValue, const TimeValue &time) {
  // should be mapped
  assert(mappedPortValues().find(&portValue) != mappedPortValues().end());

  // get the interaction
  InteractionValue &interaction = *mappedPortValues()[&portValue];

  // same holding connector
  assert(&interaction.connector() == &holder());

  // should be an enabled interaction
  assert(interaction.isEnabled());

  // down
  holder().down(interaction, portValue);

  // execute
  return interaction.execute(time);
}


/**
 * \brief Compute the port values and the maximal port values
 * exported by the port.
 *
 * Require that port values of the ports connected by
 * the connector holding 'this' are up-to-date.
 *
 * Port values exported by 'this' correspond to the application
 * of up() method of the connector holder, for all interaction values
 * enabled by the connector holder, which are the interaction values
 * returned by interaction() in the connector.
 * The computed port values can be accessed using portValues().
 *
 * Maximal port values exported by the port correspond to
 * port values of maximal interaction values.
 * The computed maximal port values can be accessed using
 * maximalPortValues().
 */
void ConnectorExportPort::updatePortValues() {
  // purge mapping between port values and port
  clearMappedPortValues();

  // purge existing references to ports values and maximal port values
  clearPortValues();
  clearMaximalPortValues();

  Connector &connector = holder();
  vector<InteractionValue *> interactions = connector.enabledInteractions();

  // add one port value for each interaction
  for (vector<InteractionValue *>::const_iterator interactionIt = interactions.begin() ;
       interactionIt != interactions.end() ;
       ++interactionIt) {
    InteractionValue &interaction = **interactionIt;

    // do the up of the connector
    PortValue &portValue = connector.up(interaction);

    // set interval
    Interval &interval = *(new Interval(interaction.timingConstraint().interval()));
    portValue.setInterval(interval);

    // set urgency
    Urgency urgency = interaction.timingConstraint().urgency();
    portValue.setUrgency(urgency);

    // add port value
    addPortValue(portValue);
    mapPortValue(portValue, interaction);
  }


  vector<InteractionValue *> interactionsAfterPriorities = connector.enabledInteractions();

  // add one port value for each interaction with corresponding maximal timing constraint
  for (vector<InteractionValue *>::const_iterator interactionIt = interactionsAfterPriorities.begin() ;
       interactionIt != interactionsAfterPriorities.end() ;
       ++interactionIt) {
    InteractionValue &interaction = **interactionIt;

    // manage the port values without applying priorities
    PortValue &portValue = connector.up(interaction);

    // set interval
    Interval &interval = *(new Interval(interaction.timingConstraintAfterPriorities().interval()));
    portValue.setInterval(interval);

    // set urgency
    Urgency urgency = interaction.timingConstraintAfterPriorities().urgency();
    portValue.setUrgency(urgency);

    // add port value to maximal ones
    addMaximalPortValue(portValue);
    mapPortValue(portValue, interaction);
  }
}


/**
 * \brief Get the interaction corresponding to a port value.
 *
 * \param portValue is the target port value for which the interaction is found.
 */
InteractionValue& ConnectorExportPort::interaction(PortValue &portValue) const {
  map<PortValue *, InteractionValue *>::const_iterator pairIt = mappedPortValues().find(&portValue);

  // port value should be mapped
  assert (pairIt != mappedPortValues().end());

  return *(pairIt->second);
}


/**
 * \brief Clear association of interaction values to port values.
 *
 * Also delete port values and release interaction values before clearing the map.
 */
void ConnectorExportPort::clearMappedPortValues() {
  // delete interactions created by previous call to enabledInteractions()
  for (map<PortValue *, InteractionValue *>::const_iterator pairIt = mappedPortValues().begin() ;
       pairIt != mappedPortValues().end() ;
       ++pairIt) {
    PortValue &portValue = *pairIt->first;
    InteractionValue &interaction = *pairIt->second;

    Connector &connector = holder();

    // release the timing constraint
    if (portValue.hasInterval()) {
      delete &portValue.interval();
    }

    // release the interaction
    connector.releaseInteractionValue(interaction);
  }

  // clear the map
  mappedPortValues().clear();
}
