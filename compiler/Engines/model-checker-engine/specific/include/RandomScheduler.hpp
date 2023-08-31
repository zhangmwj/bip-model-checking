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

#ifndef _BIP_Engine_RandomScheduler_HPP_
#define _BIP_Engine_RandomScheduler_HPP_

#include "Scheduler.hpp"
#include "StringTree.hpp"
#include "Connector.hpp"
#include "Engine.hpp"
#include "AtomInternalPort.hpp"
#include "AtomExternalPort.hpp"
#include <TimeValue.hpp>

class Engine;
class Logger;
class BipError;
class Atom;
class Component;
class Connector;
class Compound;
class InteractionValue;
class ConnectorExportPort;
class CompoundExportPort;
class AtomInternalPort;
class AtomExternalPort;
class AtomExportPort;
class GlobalClock;
class TimingConstraint;

/** \brief Compute execution sequences in which interactions
 * are chosen randomly.
 */
class RandomScheduler : public Scheduler {
 public:
 // New attribute for memorization of previously planned interactions
 //Begin My code



    // Memory interactions
    std::map<const  Connector* , std::pair<TimeValue, Interval> > interactionMemory;
    std::map<const  AtomInternalPort* , std::pair<TimeValue, Interval> > internalMemory;
    std::map<const  AtomExternalPort* , std::pair<TimeValue, Interval> > externalMemory;


    //Inserts in maps
    void insertMemory(const Connector* C, TimeValue t, Interval interv){
        interactionMemory[C] = std::make_pair(t, interv);
    }
    void insertMemory(const AtomInternalPort* P, TimeValue t, Interval interv){
        internalMemory[P] = std::make_pair(t, interv);
    }
    void insertMemory(const AtomExternalPort* P, TimeValue t, Interval interv){
        externalMemory[P] = std::make_pair(t, interv);
    }

    // Getters for
        // TimeValues
    TimeValue getMemoryTime(const Connector * C) {
        std::pair<TimeValue, Interval> val = interactionMemory[C];
        return val.first;
    }
    TimeValue getMemoryTime(const AtomInternalPort * P) {
        std::pair<TimeValue, Interval> val = internalMemory[P];
        return val.first;
    }
    TimeValue getMemoryTime(const AtomExternalPort * P) {
        std::pair<TimeValue, Interval> val = externalMemory[P];
        return val.first;
    }

        //Timing Constraints
    Interval getMemoryInterval(const Connector * C) {
        std::pair<TimeValue, Interval> val = interactionMemory[C];
        return val.second;
    }
    Interval getMemoryInterval(const AtomInternalPort * P) {
        std::pair<TimeValue, Interval> val = internalMemory[P];
        return val.second;
    }
    Interval getMemoryInterval(const AtomExternalPort * P) {
        std::pair<TimeValue, Interval> val = externalMemory[P];
        return val.second;
    }


    // Checkers
    bool isMemorized(const Connector * C){
        for( std::map<const  Connector* , std::pair<TimeValue, Interval> >::iterator it= interactionMemory.begin(); it != interactionMemory.end(); ++it)
        {
            if( (*it).first == C) return true;
        }
        return false  ;
    }
    bool isMemorized(const AtomInternalPort * P){
        for( std::map<const  AtomInternalPort* , std::pair<TimeValue, Interval> >::iterator it= internalMemory.begin(); it != internalMemory.end(); ++it)
        {
            if( (*it).first == P) return true;
        }
        return false  ;
    }
    bool isMemorized(const AtomExternalPort * P){
        for( std::map<const  AtomExternalPort* , std::pair<TimeValue, Interval> >::iterator it= externalMemory.begin(); it != externalMemory.end(); ++it)
        {
            if( (*it).first == P) return true;
        }
        return false  ;
    }

    void logStochastic(string s){
        if(printStochTrace) cout << "[STOCHASTIC RT-BIP ENGINE]: " << s << endl;
    }

    //Clean memory
    void  cleanMemory(std::set<const Connector *> enabledInteractions){
        for( std::map<const  Connector* , std::pair<TimeValue, Interval> >::iterator it= interactionMemory.begin(); it != interactionMemory.end(); /* empty */)
        {
            if( enabledInteractions.find((*it).first) == enabledInteractions.end() ) it = interactionMemory.erase(it);
            else ++it;
        }
    }
    void  cleanMemory(InteractionValue &interaction){
        for( std::map<const  Connector* , std::pair<TimeValue, Interval> > ::iterator it= interactionMemory.begin(); it != interactionMemory.end(); /* empty */)
        {
            if(  (*it).first == &(interaction.connector()) ) it = interactionMemory.erase(it);
            else ++it;
        }
    }
    void  cleanMemory(std::set<const AtomInternalPort*> enabledInternals){
        for( std::map<const  AtomInternalPort* , std::pair<TimeValue, Interval> >::iterator it= internalMemory.begin(); it != internalMemory.end(); /* empty */)
        {
            if( enabledInternals.find((*it).first) == enabledInternals.end() ) it = internalMemory.erase(it);
            else ++it;
        }
    }
    void  cleanMemory(AtomInternalPort &port){
        for( std::map<const  AtomInternalPort* , std::pair<TimeValue, Interval> > ::iterator it= internalMemory.begin(); it != internalMemory.end(); /* empty */)
        {
            if(  (*it).first == &port ) it = internalMemory.erase(it);
            else ++it;
        }
    }
    void  cleanMemory(std::set<const AtomExternalPort*> enabledExternals){
        for( std::map<const  AtomExternalPort* , std::pair<TimeValue, Interval> >::iterator it= externalMemory.begin(); it != externalMemory.end(); /* empty */)
        {
            if( enabledExternals.find((*it).first) == enabledExternals.end() ) it = externalMemory.erase(it);
            else ++it;
        }
    }
    void  cleanMemory(AtomExternalPort &port){
        for( std::map<const  AtomExternalPort* , std::pair<TimeValue, Interval> > ::iterator it= externalMemory.begin(); it != externalMemory.end(); /* empty */)
        {
            if(  (*it).first == &port ) it = externalMemory.erase(it);
            else ++it;
        }
    }

    // Log the memories
    std::string logMemory(){
        std::stringstream ss ;
        ss << "Planning memory: " << endl;
        ss << logInteractionMemory();
        ss << logInternalMemory();
        ss << logExternalMemory();

        std::string s = ss.str();
        return s ;
    }
    std::string logInteractionMemory(){
        std::stringstream ss ;
        for( std::map<const  Connector* , std::pair<TimeValue, Interval> > ::iterator it= interactionMemory.begin(); it != interactionMemory.end(); ++it)
        {
            ss << "       [InteractionMemory]: " << (*it).first->name() << ": " << (*it).second.first << endl;
        }
        std::string s = ss.str();
        return s ;
    }
    std::string logInternalMemory(){
        std::stringstream ss ;
        for( std::map<const  AtomInternalPort* , std::pair<TimeValue, Interval> > ::iterator it= internalMemory.begin(); it != internalMemory.end(); ++it)
        {
	       ss << "      [InternalPortMemory]: " << (*it).first->name() << ": " << (*it).second.first << endl;
        }
        std::string s = ss.str();
        return s ;
    }
    std::string logExternalMemory(){
        std::stringstream ss ;
        for( std::map<const  AtomExternalPort* , std::pair<TimeValue, Interval> > ::iterator it= externalMemory.begin(); it != externalMemory.end(); ++it)
        {
            ss << "      [ExternalPortMemory]: " << (*it).first->name() << ": " << (*it).second.first << endl;
        }
        std::string s = ss.str();
        return s ;
    }
    //   End My code for internals

  RandomScheduler(Engine &engine, GlobalClock &platformClock, Logger &logger, bool debug = false, bool interactive = false, bool randomSeed = true,
                  unsigned int seed = 0, bool asap = false, bool firstEnabled = false, bool relaxed = false);
  virtual ~RandomScheduler();

  void print_vars(){

   engine().getTop().print_data_vars("");
}

  virtual BipError &initialize();

  virtual BipError &run();

  const GlobalClock &platformClock() const { return mPlatformClock; }

  bool debug() const { return mDebug; }
  bool interactive() const { return mInteractive; }
  bool randomSeed() const { return mRandomSeed; }
  unsigned int seed() const { return mSeed; }
  bool asap() const { return mAsap; }
  bool firstEnabled() const { return mFirstEnabled; }
  bool relaxed() const { return mRelaxed; }

  static void notify();
  static GlobalClock &staticPlatformClock() { assert(mStaticPlatformClock != NULL); return *mStaticPlatformClock; }


 protected:
  BipError &choose();
  BipError &chooseInteractive();
  bool choose(InteractionValue &interaction);
  bool choose(AtomInternalPort &internal);
  bool choose(AtomExternalPort &external);
  bool hasChosen() const;
  bool choose(const Interval &interval, const TimeValue &plannedTime, bool hasPriority);
  TimeValue plan(const Interval &interval) const;
  TimeValue schedulingCriterion(const Interval &interval, const TimeValue &planned) const;

  BipError &checkTimeSafety();
  BipError &checkTimeSafetyAndResume();

  bool deadlock() const;
  bool waitForNotificationsUntil(const TimeValue &time);
  static pid_t pid;
  static volatile unsigned int mNbReceivedNotifications;
  static void handleSignals(int signum);
  static GlobalClock *mStaticPlatformClock;

  void print();
  StringTree print(const ConnectorExportPort &port);
  StringTree print(const CompoundExportPort &port);
  StringTree print(const AtomInternalPort &port);
  StringTree print(const AtomExternalPort &port);
  StringTree print(const AtomExportPort &port);
  StringTree print(const InteractionValue &port);
  StringTree print(const Connector &connector);
  StringTree print(const Atom &atom);
  StringTree print(const Compound &compound);
  StringTree print(const Component &component);

  GlobalClock &platformClock() { return mPlatformClock; }

  GlobalClock &mPlatformClock;

  bool hasNotifications() const { return mNbTreatedNotifications != mNbReceivedNotifications; }
  void resetNotifications() { mNbTreatedNotifications = mNbReceivedNotifications; }

  Logger &logger() const { return mLogger; }
  bool hasChosenInteraction() const { return mChosenInteraction != NULL; }
  bool hasChosenInternal() const { return mChosenInternal != NULL; }
  bool hasChosenExternal() const { return mChosenExternal != NULL; }
  InteractionValue &chosenInteraction() const { return *mChosenInteraction; }
  AtomInternalPort &chosenInternal() const { return *mChosenInternal; }
  AtomExternalPort &chosenExternal() const { return *mChosenExternal; }
  const TimeValue &wakeUpTime() const { return mWakeUpTime; }

  Logger &mLogger;
  bool mDebug;
  bool mInteractive;
  bool mRandomSeed;
  unsigned int mSeed;

  unsigned int mNbTreatedNotifications;
  bool mAsap;
  bool mFirstEnabled;
  bool mRelaxed;

  InteractionValue *mChosenInteraction;
  AtomInternalPort *mChosenInternal;
  AtomExternalPort *mChosenExternal;
  TimeValue mWakeUpTime;
  TimeValue mMinCriterion;
  unsigned int mNbMinCriterion;

  // Lotfi
  std::pair < std::pair < string, string > , std::vector<double> > parseDistribution(string distribution);
  TimeValue sample(string dist, Clock *clk, TimeValue engineTime);
  string getDistributionFileName(string distribution);
  double truncated_sampling(double trunk, vector <double> params, string dist, double coverage);
};

#endif // _BIP_Engine_RandomScheduler_HPP_
