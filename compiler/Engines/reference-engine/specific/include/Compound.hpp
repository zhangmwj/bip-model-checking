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

#ifndef _BIP_Engine_Compound_HPP_
#define _BIP_Engine_Compound_HPP_

// inherited classes
#include <CompoundItf.hpp>
#include "Component.hpp"
#include "CompoundExportPort.hpp"
#include "CompoundExportData.hpp"
#include "Connector.hpp"
#include "Priority.hpp"

class InteractionValue;
class AtomInternalPort;
class AtomExternalPort;
class BipError;
class TimeValue;
class Interval;

class Compound : public virtual ComponentItf, public Component, public CompoundItf {
 public:
  // constructors
  Compound(const string &name);


  // destructor
  virtual ~Compound();

  // specific
  virtual BipError &execute(PortValue &portValue, const TimeValue &time);
  BipError &execute(InteractionValue &interactionValue, const TimeValue &time);
  virtual BipError &initialize();
  void initializeAllAtomExternalPorts();
  BipError &update();
  BipError &recursiveUpdate();
  vector<InteractionValue *> interactions() const;
  virtual vector<AtomInternalPort *> internals() const;
  virtual vector<AtomExternalPort *> allExternals() const;
  Interval invariant() const;
  Interval resume() const;
  BipError &resume(const TimeValue &time);
  bool hasResume() const;
  void setTime(const TimeValue &time);
  virtual const TimeValue &time() const { return mTime; }

  bool disableMaximalProgress() const { return mDisableMaximalProgress; }
  void setDisableMaximalProgress(bool disableMaximalProgress) { mDisableMaximalProgress = disableMaximalProgress; }
  void setDisableMaximalProgressForAllSubCompounds(bool disableMaximalProgress);

 protected:
  // protected setters for references
  void addComponent(Component &component) {
    mComponents[component.name()] = &component;
    component.setHolder(*this);
  }

  void addPort(CompoundExportPort &port) {
    mPorts[port.name()] = &port;
    port.setHolder(*this);
    Component::addPort(port);
  }

  void addPriority(Priority &priority) {
    mPriorities.push_back(&priority);
    priority.setHolder(*this);
  }

  void addConnector(Connector &connector) {
    mConnectors[connector.name()] = &connector;
    connector.setHolder(*this);
  }

  void addData(CompoundExportData &data) {
    mData[data.name()] = &data;
    data.setHolder(*this);
    Component::addData(data);
  }

  // specific
  BipError &detectCycleInPriorities() const;
  void updatePortValuesOfConnectors();
  void updatePortValuesOfExportedPorts();

  bool mDisableMaximalProgress;

  TimeValue mTime;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_Compound_HPP_
