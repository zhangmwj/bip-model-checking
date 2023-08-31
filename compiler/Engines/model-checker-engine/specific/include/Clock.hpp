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

#ifndef _BIP_Engine_Clock_HPP_
#define _BIP_Engine_Clock_HPP_

// inherited classes
#include <ClockItf.hpp>
#include <TimeValue.hpp>
#include <GlobalClock.hpp>
#include <dbm/fed.h>
#include <dbm/print.h>
using namespace dbm;

class Clock : public ClockItf {
 public:
  // constructors
  Clock();
  Clock(Atom &atom, const string &name);
  Clock(const Clock &clock);

  // destructor
  virtual ~Clock();

  // operations
  virtual TimeValue time() const;
  virtual double speed() const { return mSpeed; }
  virtual void resetTo(const TimeValue &time);
  virtual void setSpeed(const double &speed);

  static void configureAllClocks(GlobalClock &modelClock);

  static void configureDbm(dbm_t &dbm, vector<const Clock *> &clocks) {
    mDbm = &dbm;
    mClocks = &clocks;
  }

  static bool hasDbm() { return mDbm != NULL; }

  static bool constrainDbm(const vector<constraint_t> &timingConstraints) {
    return mDbm->constrain(timingConstraints.data(), timingConstraints.size());
  }

  void addToDbm() {
    mIndex = mClocks->size() + 2;
    mClocks->push_back(this);
  }

  static const dbm_t &dbm() { return *mDbm; }
  static bool hasModelClock() { return mModelClock != NULL; }

 protected:
  GlobalClock &modelClock() const { return *mModelClock; }
  void setModelClock(GlobalClock &modelClock) { mModelClock = &modelClock; }

  cindex_t getIndex() const {
    return mIndex;
  }
  friend class ConstraintItf;
  TimeValue mResetTime;
  TimeValue mResetTo;
  double mSpeed;

  static GlobalClock *mModelClock;
  static dbm_t *mDbm;
  static vector<const Clock *> *mClocks;

  cindex_t mIndex;
};

inline Clock::Clock(const Clock &clock) :
  ClockItf(clock),
  mResetTime(clock.mResetTime),
  mResetTo(clock.mResetTo),
  mSpeed(clock.mSpeed) {
}

inline
TimeValue Clock::time() const {
  assert(hasModelClock());
  return ((modelClock().time() - mResetTime))*speed() + mResetTo;
}

inline
void Clock::resetTo(const TimeValue &time) {
  if (hasModelClock()) {
    mResetTime = modelClock().time();
    mResetTo = time;
  } else if (hasDbm()) {
    mDbm->updateValue(mIndex, time.getTime());
  }
}

inline
void Clock::setSpeed(const double &speed) {
  assert(hasModelClock());

  resetTo(time());

  mSpeed = speed;
}


#endif // _BIP_Engine_Clock_HPP_
