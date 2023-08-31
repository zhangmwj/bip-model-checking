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

#ifndef _BIP_Engine_Atom_HPP_
#define _BIP_Engine_Atom_HPP_

// inherited classes
#include <AtomItf.hpp>
#include "AtomExportPort.hpp"
#include "AtomExportData.hpp"
#include "AtomInternalPort.hpp"
#include "AtomExternalPort.hpp"
#include "Component.hpp"
#include "Compound.hpp"
#include "TimeValue.hpp"
#include "Interval.hpp"
#include "BipError.hpp"


class Atom : public virtual ComponentItf, public Component, public AtomItf {
 public:
  // constructors
  Atom(const string &name);
  Atom(const string &name, bool initialHasResume);

  // destructor
  virtual ~Atom();

  virtual vector<Constraint> allTimingConstraints() const = 0;
  virtual BipError &execute(PortValue &portValue, const TimeValue &time) = 0;
  virtual BipError &execute(PortValue &portValue) = 0;
  virtual BipError &execute(AtomExternalPort &external, const TimeValue &time) = 0;
  virtual string toString() const { return "?"; };

  // specific
  BipError &execute(AtomInternalPort &internalPort, const TimeValue &time);
  BipError &execute(AtomInternalPort &internalPort);
  virtual vector<AtomInternalPort *> internals() const;
  virtual vector<AtomExternalPort *> allExternals() const;
  virtual const TimeValue &time() const { return holder().time(); }
  bool hasResume() const { return mHasResume; }
  void setHasResume(bool b) { mHasResume = b; }

  friend ostream& operator<<(ostream &o, const Atom &atom);
  friend ostream& operator<<(ostream &o, const Atom *atom);

  // references accessors
  void addInternalPort(AtomInternalPort &internalPort) {
    mInternalPorts[internalPort.name()] = &internalPort;
    internalPort.setHolder(*this);
  }

  void addExternalPort(AtomExternalPort &externalPort) {
    mExternalPorts[externalPort.name()] = &externalPort;
    externalPort.setHolder(*this);
  }

  void addPort(AtomExportPort &port) {
    mPorts[port.name()] = &port;
    port.setHolder(*this);
    Component::addPort(port);
  }

  void addData(AtomExportData &data) {
    mData[data.name()] = &data;
    data.setHolder(*this);
    Component::addData(data);
  }

 protected:
  // attributes
  bool mHasResume;
};

#endif // _BIP_Engine_Atom_HPP_
