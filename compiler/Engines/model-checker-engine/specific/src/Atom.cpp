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

#include <Atom.hpp>
#include <Compound.hpp>
#include <BipError.hpp>

// constructors
Atom::Atom(const string &name) :
  ComponentItf(name, ATOM),
  Component(name, ATOM),
  AtomItf(name),
  mHasResume(false) {
  /* implement your constructor here */
}

Atom::Atom(const string &name, bool initialHasResume) :
  ComponentItf(name, ATOM),
  Component(name, ATOM),
  AtomItf(name, initialHasResume),
  mHasResume(initialHasResume) {
  /* implement your constructor here */
}

// destructor
Atom::~Atom() {
  /* implement your destructor here */
}

/* \brief Execute the transition corresponding to an internal port.
 *
 * \param internalPort is the target internal port, it must be an internal
 * port of atom 'this', and it must have a port value.
 *
 * \return An error if found during the execution of the corresponding
 * transition, BipError::NoError otherwise.
 */
BipError &Atom::execute(AtomInternalPort &internalPort, const TimeValue &time) {
  // must have a port value
  assert(internalPort.hasPortValue());

  // set resume information
  setHasResume(internalPort.portValue().hasResume());

  // execute
  BipError &error = execute(internalPort.portValue(), time);

  if (error.type() != NO_ERROR) {
    return error;
  }

  return BipError::NoError;
}

BipError &Atom::execute(AtomInternalPort &internalPort) {
  // must have a port value
  assert(internalPort.hasPortValue());

  // execute
  BipError &error = execute(internalPort.portValue());

  if (error.type() != NO_ERROR) {
      return error;
  }

  return BipError::NoError;
}

/* \brief Compute enabled internal ports.
 *
 * Compute internal ports enabled by transitions at the current state
 * of atom 'this'.
 *
 * \return The set of enabled internal ports.
 */
vector<AtomInternalPort *> Atom::internals() const {
  vector<AtomInternalPort *> ret;

  for (map<string, AtomInternalPort *>::const_iterator portIt = internalPorts().begin() ;
       portIt != internalPorts().end() ;
       ++portIt) {
    AtomInternalPort &port = *portIt->second;

    // add port value of port if it is not exported
    if (!port.isExported() &&
        port.hasPortValue() &&
        !hasResume()) {
      ret.push_back(&port);
    }
  }

  return ret;
}

/* \brief Compute enabled external ports.
 *
 * Compute external ports waiting for event at the current state
 * of atom 'this' and having corresponding event.
 *
 * \return The set of enabled external ports.
 */
vector<AtomExternalPort *> Atom::allExternals() const {
  vector<AtomExternalPort *> ret;

  for (map<string, AtomExternalPort *>::const_iterator portIt = externalPorts().begin() ;
       portIt != externalPorts().end() ;
       ++portIt) {
    AtomExternalPort &port = *portIt->second;

    if (!hasResume()) {
      ret.push_back(&port);
    }
  }

  return ret;
}

ostream& operator<<(ostream &o, const Atom &atom) {
  return o << atom.toString();
}

ostream& operator<<(ostream &o, const Atom *atom) {
  return o << atom->toString();
}

