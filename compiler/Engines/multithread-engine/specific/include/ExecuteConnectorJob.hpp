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

#ifndef _BIP_Engine_ExecuteConnectorJob_HPP_
#define _BIP_Engine_ExecuteConnectorJob_HPP_

// inherited classes
#include <Job.hpp>
#include <BipError.hpp>
#include "ReadyQueue.hpp"
#include <Resetable.hpp>
#include <Scheduler.hpp>
#include <TimeValue.hpp>
#include <ExecuteAtomJob.hpp>
#include <Resource.hpp>
#include <UpdateClockJob.hpp>

class Connector;
class Atom;
class Port;
class Logger;
class InteractionValue;
class Atom;

class ExecuteConnectorJob : public Job {
 public:
  // constructors
  ExecuteConnectorJob(Connector &connector);

  // destructor
  virtual ~ExecuteConnectorJob();

  // getters for references
  Connector &connector() const { return mConnector; }
  Logger &logger() { return *mLogger; }
  bool hasLogger() const { return mLogger != NULL; }
  bool asap() const { return mAsap; }
  bool firstEnabled() const { return mFirstEnabled; }
  bool relaxed() const { return mRelaxed; }
  bool disabledTimeSafety() const { return mDisabledTimeSafety; }
  
  // setters
  void setLogger(Logger &logger) { mLogger = &logger; }
  void clearLogger() { mLogger = NULL; }
  void setAsap(bool b) { mAsap = b; }
  void setFirstEnabled(bool b) { mFirstEnabled = b; }
  void setRelaxed(bool b) { mRelaxed = b; }
  void setDisabledTimeSafety(bool b) { mDisabledTimeSafety = b; }

  // operations
  void initialize();
  void initializeMutexs();

 protected:
  // operations
  virtual void realJob();
  virtual void prologue() { mReserver.start(); }
  virtual void epilogue() { mReserver.end(); }

  void unreserveUnusedResources();

  bool tryToExecuteChosenInteraction();
  void executeChosenInteraction();
  BipError &detectCyclesInPriorities() const;

  bool hasChosen() const { assert(mChosenInteraction == NULL || mChosenTime != TimeValue::MIN); return mChosenInteraction != NULL; }
  InteractionValue &chosenInteraction() const { assert(hasChosen()); return *mChosenInteraction; }
  const TimeValue &chosenTime() const { return mChosenTime; }
  void recomputeChoice();
  
  bool hasResumeEagerInteraction() const;
  bool lastAtomHasResume() const;

  vector<Atom *> allAtoms();
  void allAtoms(vector<Atom *> &atoms, const Connector &connector);
  void allAtoms(vector<Atom *> &atoms, const Port &port);

  Connector &mConnector;
  Logger *mLogger;

  // all atoms involved
  vector<Atom *> mAllAtoms;

  // reservation mechanisms
  class ConnectorReserver : public Resource::Reserver {
   public:
    ConnectorReserver(ExecuteConnectorJob &job) : Resource::Reserver(job), mExecuteConnectorJob(job) { }
    virtual ~ConnectorReserver() { }

    virtual void uponReservation(const TimeValue &time) { mExecuteConnectorJob.executeChosenInteraction(); }

   protected:
    ExecuteConnectorJob &mExecuteConnectorJob;
  };
  
  ConnectorReserver mReserver;
  
  ResetableItf mResetChoice;
  InteractionValue *mChosenInteraction;
  TimeValue mChosenTime;
  Interval mTimeSafe;

  bool mAsap;
  bool mFirstEnabled;
  bool mRelaxed;
  bool mDisabledTimeSafety;

  // resume mechanisms
  ExecuteAtomJob::ResumeJoiner mResumeJoiner;

  UpdateClockJob mUpdateClockJob;
};


#endif // _BIP_Engine_ExecuteConnectorJob_HPP_
