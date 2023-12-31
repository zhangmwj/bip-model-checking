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

#ifndef _BIP_Engine_AtomInternalPortItf_HPP_
#define _BIP_Engine_AtomInternalPortItf_HPP_

#include <bip-engineiface-config.hpp>
#include <Clock.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// referenced classes
class Atom;
class PortValue;


class AtomInternalPortItf {
 public:
  // destructor
  virtual ~AtomInternalPortItf();

  // operations
  virtual PortValue &portValue() const = 0;
  virtual bool hasPortValue() const = 0;
  // Lotfi
  virtual void setDistribution(std::string s) = 0;
  virtual std::string getDistribution() const = 0;
  virtual void setClock(Clock *c) = 0;
  virtual Clock *getClock() const = 0;

  // getters for attributes
  const string &name() const { return mName; }

  // opposites accessors
  Atom &holder() const { return *mHolder; }
  bool hasHolder() const { return mHolder != NULL; }
  void setHolder(Atom &atom) { mHolder = &atom; }

 protected:
  // protected constructors
  AtomInternalPortItf(const string &name);

  // attributes
  const string mName;

  // opposites
  Atom *mHolder;
};

#endif // _BIP_Engine_AtomInternalPortItf_HPP_
