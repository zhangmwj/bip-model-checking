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

#ifndef _BIP_Engine_State_HPP_
#define _BIP_Engine_State_HPP_

#include <bip-engineiface-config.hpp>
#include <dbm/fed.h>
#include <string>

using namespace bipbasetypes;
using namespace dbm;

/** \brief Represent a state of a model
 */
class State {
 public:
  struct hash_all {
    size_t operator()(const State &state) const {
      size_t hashDiscret = hash_discret_part()(&state);
      uint32_t hashDbm = dbm_hash(state.dbm()(), state.dbm().getDimension());
      return hashDbm + 0x9e3779b9 + (hashDiscret << 6) + (hashDiscret>>2);
    }
  };

  struct hash_discret_part {
    size_t operator()(const State *state) const {
      size_t res = 17;
      for (size_t i = 0; i < state->size(); i++) {
        res = res * 31 + hash<char>()( state->buffer()[i]);
      }
      return res;
    }
  };

  State(char *buffer, size_t size);
  State(char *buffer, size_t size, const dbm_t &dbm);
  State(const State &state);
  virtual ~State();

  const char *buffer() const { return mBuffer; }
  size_t size() const { return mSize; }

  const dbm_t &dbm() const { return mDbm; }
  bool operator==(const State &state) const;
  bool operator<=(const State &state) const;
  bool operator<(const State &state) const;
  State &operator=(const State &state);
  int id() const { return mId; }

 protected:
  void setSize();
  static int nb;
  char *mBuffer;
  size_t mSize;
  dbm_t mDbm;
  int mId;
  friend ostream &operator<<(ostream &out, const State &state) {
    out << "state mId = " << state.mId;
    return out;
  }
};

#endif // _BIP_Engine_State_HPP_
