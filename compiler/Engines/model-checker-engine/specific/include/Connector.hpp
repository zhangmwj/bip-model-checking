/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
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

#ifndef _BIP_Engine_Connector_HPP_
#define _BIP_Engine_Connector_HPP_

// inherited classes
#include <ConnectorItf.hpp>
#include "ConnectorExportPort.hpp"
#include "QuotedPortReference.hpp"

class Connector : public ConnectorItf {
 public:
  // constructors
  Connector(const string &name, const bool &asyncResume);

  // destructor
  virtual ~Connector();

  // specific
  bool isTopLevel() const;
  vector<Connector *> subConnectors() const;
  vector<Connector *> allSubConnectors() const;
  void updatePortValues();
  vector<InteractionValue *> enabledInteractions(bool MC = false) const;
  vector<InteractionValue *> maximalInteractions() const;
  void release(const vector<Interaction *> &interactions) const;
  void release(const vector<InteractionValue *> &interactions) const;
  string fullName() const;

 protected:
  // protected setters for references
  void addPort(QuotedPortReference &port) {
    mPorts.push_back(&port);
    port.setHolder(*this);
  }

  void setExportedPort(ConnectorExportPort &exportedPort) {
    mExportedPort = &exportedPort;
    exportedPort.setHolder(*this);
  }

  // specific
  void enumerateInteractionValues(vector<InteractionValue *> &allInteractions, const Interaction &interaction, vector<PortValue *> partialValues, unsigned int nextPortIndex, bool MC = false) const;
};

#endif // _BIP_Engine_Connector_HPP_
