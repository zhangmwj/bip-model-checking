/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 *  Marc Pouhliès
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

#ifndef _BIP_Engine_InteractionValue_HPP_
#define _BIP_Engine_InteractionValue_HPP_

// inherited classes
#include <InteractionValueItf.hpp>
#include "Interaction.hpp"
#include <Interval.hpp>
#include <TimingConstraint.hpp>
#include <Resetable.hpp>

class BipError;
class Connector;

class InteractionValue : public InteractionValueItf {
 public:
  // constructors
  InteractionValue();

  // destructor
  virtual ~InteractionValue();

  // specific
  const Connector &connector() const { return interaction().connector(); }
  const vector<Port *> &ports() const { return interaction().ports(); }
  BipError &execute(const TimeValue &time);

  bool isAllDefined() const;
  bool isEnabled() const;
  bool hasResume() const;

  void applyDomination(TimingConstraint &constraint) const;
  void applyLocalDomination(TimingConstraint &constraint) const;
  void applyPrioritiesDomination(TimingConstraint &constraint) const;
  void applyDominationBy(const InteractionValue &interaction, TimingConstraint &constraint) const;

  void inheritDominatedUrgencies(TimingConstraint &constraint) const;
  void inheritLocalDominatedUrgencies(TimingConstraint &constraint) const;
  void inheritPrioritiesDominatedUrgencies(TimingConstraint &constraint) const;
  void inheritDominatedUrgencyOf(const InteractionValue &interaction, TimingConstraint &constraint) const;

  bool operator<=(const InteractionValue &interaction) const;
  bool operator==(const InteractionValue &interaction) const;
  bool operator!=(const InteractionValue &interaction) const { return ! (*this == interaction); }
  bool operator< (const InteractionValue &interaction) const { bool eq; bool ret = includedIn(interaction, eq); return ret && !eq; }
  bool operator> (const InteractionValue &interaction) const { return interaction < *this; }

  Interval interval() const { return timingConstraint().interval(); }
  const TimingConstraint &timingConstraint() const { return mTimingConstraint; }
  const TimingConstraint &timingConstraintAfterPriorities() const { return mTimingConstraintAfterPriorities; }
  void resetTimingConstraint() const { mTimingConstraint.reset(); }
  void resetTimingConstraintAfterPriorities() const { mTimingConstraintAfterPriorities.reset(); }

  friend ostream& operator<<(ostream &, const InteractionValue&);
  friend ostream& operator<<(ostream &, const InteractionValue*);

 protected:
  bool includedIn(const InteractionValue &interaction, bool &eq) const;

  // update methods resetable objects
  void recomputeTimingConstraint(TimingConstraint &constraint) const;
  void recomputeTimingConstraintAfterPriorities(TimingConstraint &constraint) const;

  mutable Resetable<TimingConstraint, InteractionValue> mTimingConstraint;
  mutable Resetable<TimingConstraint, InteractionValue> mTimingConstraintAfterPriorities;
};


#endif // _BIP_Engine_InteractionValue_HPP_
