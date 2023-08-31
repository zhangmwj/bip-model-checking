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

#include "RealTimeClock.hpp"
#include <Engine.hpp>

#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

RealTimeClock::RealTimeClock() {
  // initialize signal mask
  sigemptyset(&maskSIGBIP);
  sigaddset(&maskSIGBIP, Engine::SIGBIP);
  sigaddset(&maskSIGBIP, SIGALRM);

  // initialize timer for implementing wait
  timer_create(CLOCK_REALTIME, NULL, &mTimer);
}

RealTimeClock::~RealTimeClock() {
  timer_delete(mTimer);
}

bool RealTimeClock::wait(const TimeValue &newTime) {
  bool hasReceivedNotifications = false;

  TimeValue currentTime = time();

  while (currentTime < newTime && !hasReceivedNotifications) {
    // compute the delay to wait for
    TimeValue delayToWaitFor = newTime - currentTime;

    armTimer(delayToWaitFor);

    // wait for notification and timer expiration
    int sig = sigwaitinfo(&maskSIGBIP, NULL);

    if (sig == Engine::SIGBIP) {
      hasReceivedNotifications = true;
    }
    else {
      currentTime = time();
    }
  }

  return hasReceivedNotifications;
}

TimeValue RealTimeClock::getTimeOfDay() const {
  struct timespec now;
  clock_gettime(CLOCK_REALTIME, &now);
  
  return TimeValue((long long) now.tv_sec, SECOND) + TimeValue((long long) now.tv_nsec, NANOSECOND);
}

void RealTimeClock::armTimer(const TimeValue &delay) {
  assert(delay > TimeValue::ZERO);

  if (delay != TimeValue::MAX) {
    // compute parameters for the timer
    long delay_sec  = (long) (delay / TimeValue(1, SECOND));
    long delay_nsec = (long) ((delay - TimeValue((long long) delay_sec, SECOND)) / TimeValue(1, NANOSECOND));

    // initialize timer parameters
    mTimerSpec.it_interval.tv_sec = 0;
    mTimerSpec.it_interval.tv_sec = 0;
    mTimerSpec.it_value.tv_sec  = delay_sec;
    mTimerSpec.it_value.tv_nsec = delay_nsec;

    // set the timer
    timer_settime(mTimer, 0, &mTimerSpec, NULL);
  }
}

void RealTimeClock::disarmTimer() {
  // initialize timer parameters
  mTimerSpec.it_interval.tv_sec = 0;
  mTimerSpec.it_interval.tv_sec = 0;
  mTimerSpec.it_value.tv_sec  = 0;
  mTimerSpec.it_value.tv_nsec = 0;

  // set the timer
  timer_settime(mTimer, 0, &mTimerSpec, NULL);
}
