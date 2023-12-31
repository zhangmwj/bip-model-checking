/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
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

#ifndef _BIP_Engine_Priority_HPP_
#define _BIP_Engine_Priority_HPP_

// inherited classes
#include <PriorityItf.hpp>
#include <Resetable.hpp>
#include <Initializable.hpp>

class BipError;
class CycleInPriorities;
class InteractionValue;
class TimingConstraint;

class Priority : public PriorityItf {
 public:
  // constructors
  Priority(Interaction *low, Interaction *high);

  // destructor
  virtual ~Priority();

  // specific
  bool appliesLow(const Interaction &interaction) const;
  bool appliesHigh(const Interaction &interaction) const;
  Initializable<vector<Priority *>, Priority> &dominatingPriorities() const { return mDominatingPriorities; }
  Initializable<vector<Priority *>, Priority> &dominatedPriorities() const { return mDominatedPriorities; }

  BipError &detectCycles() const;

  bool changed() const { return guard() != mPreviousGuard; }
  void updatePreviousGuard() const { mPreviousGuard = guard(); }

  Resetable<bool, Priority> &active() const { return mActive; }

  void initialize();

  void applyPrioritiesDomination(const InteractionValue &interaction, TimingConstraint &constraint) const;
  void inheritPrioritiesDominatedUrgencies(const InteractionValue &interaction, TimingConstraint &constraint) const;

  ResetableItf &applyDomination() { return mApplyDomination; }
  ResetableItf &inheritUrgency() { return mInheritUrgency; }

  const vector<const CycleInPriorities *> &cycles() const { return mCycles; }
  vector<const CycleInPriorities *> &cycles() { return mCycles; }

 protected:
  void computeDominatingPriorities(vector<Priority *> &priorities);
  void computeDominatedPriorities(vector<Priority *> &priorities);
  void recomputeActive(bool &active) const;

  mutable Initializable<vector<Priority *>, Priority> mDominatingPriorities;
  mutable Initializable<vector<Priority *>, Priority> mDominatedPriorities;

  mutable bool mPreviousGuard;
  mutable Resetable<bool, Priority> mActive;
  ResetableItf mApplyDomination;
  ResetableItf mInheritUrgency;

  vector<const CycleInPriorities *> mCycles;
};

#endif // _BIP_Engine_Priority_HPP_
