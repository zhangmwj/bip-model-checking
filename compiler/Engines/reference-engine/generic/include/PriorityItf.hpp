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

#ifndef _BIP_Engine_PriorityItf_HPP_
#define _BIP_Engine_PriorityItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// used classes
#include "Data.hpp"

// referenced classes
class Compound;
class Interaction;

class Component;

class PriorityItf {
 public:
  // destructor
  virtual ~PriorityItf();

  // operations
  virtual bool guard() const = 0;

  // getters for references
  Interaction &low() const { return *mLow; }
  bool hasLow() const { return mLow != NULL; }
  Interaction &high() const { return *mHigh; }
  bool hasHigh() const { return mHigh != NULL; }
  const vector<Data *> &data() const { return mData; }
  bool hasData() const { return !mData.empty(); }

  // opposites accessors
  Compound &holder() const { return *mHolder; }
  bool hasHolder() const { return mHolder != NULL; }
  void setHolder(Compound &compound) { mHolder = &compound; }

 protected:
  // protected constructors
  PriorityItf(Interaction *low, Interaction *high);

  // protected getters for references
  vector<Data *> &data() { return mData; }

  // protected setters for references
  void addData(Data &data) { mData.push_back(&data); }

  // references
  Interaction *const mLow;
  Interaction *const mHigh;
  vector<Data *> mData;

  // opposites
  Compound *mHolder;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_PriorityItf_HPP_
