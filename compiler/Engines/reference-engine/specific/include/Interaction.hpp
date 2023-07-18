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

#ifndef _BIP_Engine_Interaction_HPP_
#define _BIP_Engine_Interaction_HPP_

// inherited classes
#include <InteractionItf.hpp>

class Priority;
class BipError;
class TimingConstraint;

class Interaction : public InteractionItf {
 public:
  // constructors
  Interaction(const Connector &connector);

  // destructor
  virtual ~Interaction();

  // operations
  virtual void recycle() {}

  // specific opertations
  void release();
  virtual bool isEnabled() const;

  void applyPrioritiesDomination(TimingConstraint &constraint) const;
  void applyLocalDomination(TimingConstraint &constraint) const;



  void inheritPrioritiesDominatedUrgencies(TimingConstraint &constraint) const;
  void inheritLocalDominatedUrgencies(TimingConstraint &constraint) const;

  vector<Priority *> dominatingPriorities() const;
  vector<Priority *> dominatedPriorities() const;
  BipError &detectCycleInPriorities() const;

  unsigned int index(const Port &port) const;
  bool contains(const Port &port) const { return index(port) != ports().size(); }

  bool isDominatedLocallyBy(const Interaction &interaction) const;

  friend ostream& operator<<(ostream &, const Interaction&);
  friend ostream& operator<<(ostream &, const Interaction*);

 protected:
  BipError &detectCycleInPriorities(const vector<const Interaction *> &path) const;
};

#endif // _BIP_Engine_Interaction_HPP_
