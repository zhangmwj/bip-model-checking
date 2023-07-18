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

#ifndef _BIP_Engine_ExecuteExternalsJob_HPP_
#define _BIP_Engine_ExecuteExternalsJob_HPP_

// inherited classes
#include <Job.hpp>
#include <Scheduler.hpp>
#include <Resetable.hpp>
#include <Resource.hpp>
#include <UpdateClockJob.hpp>

class BipError;
class Atom;
class PortValue;
class BipError;
class Logger;
class ExecuteConnectorJob;
class AtomInternalPort;
class AtomExternalPort;
class TimeValue;

class ExecuteExternalsJob : public Job {
 public:
  // constructors
  ExecuteExternalsJob(Atom &atom);

  // destructor
  virtual ~ExecuteExternalsJob();

  // getters for references
  Atom &atom() const { return mAtom; }
  Logger &logger() { return *mLogger; }
  bool hasLogger() const { return mLogger != NULL; }
  bool asap() const { return mAsap; }
  bool firstEnabled() const { return mFirstEnabled; }
  bool relaxed() const { return mRelaxed; }

  // setters
  void setWakeUpTime(const TimeValue &time) { mWakeUpTime = time; }
  void setLogger(Logger &logger) { mLogger = &logger; }
  void clearLogger() { mLogger = NULL; }
  void setAsap(bool b) { mAsap = b; }
  void setFirstEnabled(bool b) { mFirstEnabled = b; }
  void setRelaxed(bool b) { mRelaxed = b; }

  // operations
  void initialize();
  void initializeMutexs() { mReserver.initialize(); }

 protected:
  // operations
  virtual void realJob();
  virtual void prologue() { mReserver.start(); }
  virtual void epilogue() { mReserver.end(); }

  bool tryToExecuteChosenExternal();
  void executeChosenExternal();

  bool hasChosen() const { assert(mChosenExternal == NULL || mChosenTime != TimeValue::MIN); return mChosenExternal != NULL; }
  AtomExternalPort &chosenExternal() const { assert(hasChosen()); return *mChosenExternal; }
  const TimeValue &chosenTime() const { return mChosenTime; }
  void recomputeChoice();

  bool hasResumeEager() const;
  
  Atom &mAtom;
  Logger *mLogger;

  // reservation mechanisms
  class AtomReserver : public Resource::Reserver {
   public:
    AtomReserver(ExecuteExternalsJob &job) : Resource::Reserver(job), mExecuteExternalsJob(job) { }
    virtual ~AtomReserver() { }

    virtual void uponReservation(const TimeValue &time) { mExecuteExternalsJob.executeChosenExternal(); }

   protected:
    ExecuteExternalsJob &mExecuteExternalsJob;
  };
  
  AtomReserver mReserver;

  ResetableItf mResetChoice;
  AtomExternalPort * mChosenExternal;
  TimeValue mChosenTime;
  Interval mTimeSafe;

  bool mAsap;
  bool mFirstEnabled;
  bool mRelaxed;

  UpdateClockJob mUpdateClockJob;
};

#endif // _BIP_Engine_ExecuteExternalsJob_HPP_
