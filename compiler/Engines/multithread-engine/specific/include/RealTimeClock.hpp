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

#ifndef _BIP_Engine_RealTimeClock_HPP_
#define _BIP_Engine_RealTimeClock_HPP_

#include <NotifiableClock.hpp>
#include <TimeValue.hpp>

#include <mutex>

/** \brief Provides the basic interface for implementing the clock used by
 * the scheduler.
 *
 * 
 */
class RealTimeClock : public NotifiableClock {
 public:
  RealTimeClock();
  virtual ~RealTimeClock();

  static void start() { mGetTimeOfDayAtStart = getTimeOfDay(); }

  virtual TimeValue time() const { return getTimeOfDay() - mGetTimeOfDayAtStart; }
  virtual bool wait(const TimeValue &time);

 protected:
  static TimeValue getTimeOfDay();
  static TimeValue mGetTimeOfDayAtStart;

  mutex mMutex;
  condition_variable mConditionVariable;
  bool mNotified;
};

#endif // _BIP_Engine_RealTimeClock_HPP_
