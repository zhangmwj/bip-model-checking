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

#include "RandomScheduler.hpp"
#include <Compound.hpp>
#include <Component.hpp>
#include <InteractionValue.hpp>
#include <Atom.hpp>
#include <AtomInternalPort.hpp>
#include <AtomExportPort.hpp>
#include <BipError.hpp>
#include <NonDeterministicPetriNetError.hpp>
#include <NonOneSafePetriNetError.hpp>
#include <CycleInPrioritiesError.hpp>
#include <CycleInAtomPrioritiesError.hpp>
#include <AtomInvariantViolationError.hpp>
#include <UnexpectedEventError.hpp>
#include <TimeSafetyViolationError.hpp>

#include <Engine.hpp>
#include <Logger.hpp>
#include <StringTree.hpp>

#include <TimingConstraint.hpp>
#include <GlobalClock.hpp>

#include <stdlib.h>
#include "engine-version.hpp"

#include <string>
#include <iostream>
#include <sstream>

#include <time.h>
#include <signal.h>
#include <unistd.h>

RandomScheduler::RandomScheduler(Engine &engine, GlobalClock &clock, Logger &logger, bool debug, bool interactive, bool randomSeed, unsigned int seed, bool asap, bool firstEnabled, bool relaxed) :
  Scheduler(engine),
  mPlatformClock(clock),
  mLogger(logger),
  mDebug(debug),
  mInteractive(interactive),
  mRandomSeed(randomSeed),
  mSeed(seed),
  mAsap(asap),
  mFirstEnabled(firstEnabled),
  mRelaxed(relaxed) {
  // initialize signals management
  RandomScheduler::pid = getpid();
  signal(Engine::SIGBIP, handleSignals);
  signal(SIGALRM, handleSignals);

  // initialize static platform clock
  assert(mStaticPlatformClock == NULL);
  mStaticPlatformClock = &clock;
}

RandomScheduler::~RandomScheduler() {
}

/**
 * \brief Initialize the system.
 */
BipError &RandomScheduler::initialize() {
  // log banner
  logger().log("BIP Engine (version " ENGINE_VERSION " )");
  logger().log("");
  logger().log("initialize components...");

  // initialize the seed for random
  ostringstream displayRandomSeed;
  displayRandomSeed << "random scheduling based on seed=";

  if (randomSeed()) {
    int random_seed = time(NULL);
    srand (random_seed);

    displayRandomSeed << random_seed;
  }
  else {
    srand(seed());

    displayRandomSeed << seed();
  }

  // log seed
  logger().log(displayRandomSeed.str());

  BipError &error = engine().initialize();
  
  logger().log(error);

  return error;
}

/**
 * \brief Execute a single execution sequence randomly.
 *
 * Interactions and internal ports are chosen randomly according to
 * a uniform repartition of the probability. It is based on rand() of
 * the standard library for computing random values. Notice that the
 * seed for rand() is currently not fixed.
 */
BipError &RandomScheduler::run() {
  TimeValue timeSafetyViolation = TimeValue::MAX;

  if (debug()) {
    print();
  }

  // check time-safety violation and update model time
  BipError &error = checkTimeSafetyAndResume();
  logger().log(error);

  if (error.type() != NO_ERROR) {
    return error;
  }

  while (!deadlock() && !logger().reachedLimit()) {
    // take a snapshot of the treated notifications
    resetNotifications();

    // /!\ order is critical: must be placed after updateTreatedNotifications()!
    // update current status of external ports w.r.t. incoming events
    BipError &errorInCheckExternals = engine().checkExternals();
    logger().log(errorInCheckExternals);

    if (errorInCheckExternals.type() != NO_ERROR) {
      return errorInCheckExternals;
    }

    // choose an interaction / internal port / external port
    BipError &errorInChoose = choose();
    logger().log(errorInChoose);

    if (errorInChoose.type() != NO_ERROR) {
      return errorInChoose;
    }

    // wait for the next event
    bool hasNotifications = waitForNotificationsUntil(wakeUpTime());

    if (hasNotifications) {
      continue;
    }
    else if (!hasChosen() && !hasNotifications) {
      timeSafetyViolation = wakeUpTime();
      break;
    }
    else if (hasChosen() && !hasNotifications) {
      // execute the selected interaction / internal port / external port
      if (hasChosenInteraction()) {
        if (!interactive()) logger().logEnabled();
        logger().log(chosenInteraction(), wakeUpTime());
        BipError &error = engine().execute(chosenInteraction(), wakeUpTime());
        logger().log(error);

        if (error.type() != NO_ERROR) {
          return error;
        }
      }
      else if (hasChosenInternal()) {
        if (!interactive()) logger().logEnabled();
        logger().log(chosenInternal(), wakeUpTime());
        BipError &error = engine().execute(chosenInternal(), wakeUpTime());
        logger().log(error);

        if (error.type() != NO_ERROR) {
          return error;
        }
      }
      else if (hasChosenExternal()) {
        logger().logEnabledExternals();
        logger().log(chosenExternal(), wakeUpTime());
        BipError &error = engine().execute(chosenExternal(), wakeUpTime());
        logger().log(error);

        if (error.type() != NO_ERROR) {
          return error;
        } 
      }
      else {
        assert(false);
      }

      // check time-safety violation and update model time
      BipError &error = checkTimeSafetyAndResume();
      logger().log(error);

      if (debug()) {
        print();
      }

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
    else {
      assert(false);
    }
  }

  // log deadlock or reached limit
  logger().logEnabled();

  return BipError::NoError;
}

BipError &RandomScheduler::choose() {
  // reninitialize choosing related values
  mChosenInteraction = NULL;
  mChosenInternal = NULL;
  mChosenExternal = NULL;

  mWakeUpTime = engine().waitInterval().right();
  mMinCriterion = TimeValue::MAX;
  mNbMinCriterion = 0;

  // interactive choice
  BipError &error = chooseInteractive();

  // choose if no choice has been made by the interactive mode
  if (error.type() == NO_ERROR && !hasChosenInteraction() && !hasChosenInternal()) {
    for (vector<InteractionValue *>::const_iterator interactionIt = engine().interactions().begin() ;
         interactionIt != engine().interactions().end() ;
         ++interactionIt) {
      InteractionValue &interaction = **interactionIt;    

      choose(interaction);
    }

    for (vector<AtomInternalPort *>::const_iterator portIt = engine().internals().begin() ;
         portIt != engine().internals().end() ;
         ++portIt) {
      AtomInternalPort &port = **portIt;

      choose(port);
    }

    for (vector<AtomExternalPort *>::const_iterator portIt = engine().externals().begin() ;
         portIt != engine().externals().end() ;
         ++portIt) {
      AtomExternalPort &port = **portIt;

      choose(port);
    }
  }

  return error;
}

BipError &RandomScheduler::chooseInteractive() {
  if (interactive()) {
    bool cont = true;

    while ((!engine().interactions().empty() || !engine().internals().empty()) && engine().externals().empty() && cont) {
      logger().logEnabled();
      ostringstream oss;
      oss << engine().interactions().size() + engine().internals().size() - 1;
      string message = " -> enter interaction / internal port number (0.." + oss.str() + "), or 'r' for a random choice: ";

      logger().log(message);

      string str;
      cout.flush();
      cin >> str;

      if (cin.eof()) { // in case of ctrl-D
        cout << endl;
        exit(0);
      }
      else if (str.size() > 0) {
        if (str[0] != 'r') {
          unsigned int chosenIndex;
          istringstream iss( str );
          iss >> chosenIndex;

          if (iss.fail() || chosenIndex >= engine().interactions().size() + engine().internals().size()) {
            logger().log("Invalid choice!");
            cont = true;
          }
          else {
            TimeValue currentTime = platformClock().time();

            cont = true;

            if (chosenIndex < engine().interactions().size()) {
              InteractionValue *chosen = engine().interactions()[chosenIndex];
              Interval interval = engine().interval(*chosen);
              interval &= Interval(currentTime, TimeValue::MAX);

              if (!interval.empty()) {
                mChosenInteraction = chosen;
                mWakeUpTime = plan(interval);
                cont = false;
              }
            }
            else {
              AtomInternalPort *chosen = engine().internals()[chosenIndex - engine().interactions().size()];
              Interval interval = engine().interval(*chosen);
              interval &= Interval(currentTime, TimeValue::MAX);

              if (!interval.empty()) {
                mChosenInternal = chosen;
                mWakeUpTime = plan(interval);
                cont = false;
              }
            }

            if (cont) {
              BipError &error = checkTimeSafety();

              if (error.type() != NO_ERROR) {
                return error;
              }
            }
          }
        }
      }
    }
  }

  return BipError::NoError;
}

bool RandomScheduler::choose(InteractionValue &interaction) {
  bool ret = false;

  Interval interv = engine().interval(interaction);

  if (choose(interv, plan(interv), false)) {
    mChosenInteraction = &interaction;
    mChosenInternal = NULL;
    mChosenExternal = NULL;

    ret = true;
  }

  return ret;
}

bool RandomScheduler::choose(AtomInternalPort &internal) {
  bool ret = false;

  Interval interv = engine().interval(internal);

  if (choose(interv, plan(interv), false)) {
    mChosenInteraction = NULL;
    mChosenInternal = &internal;
    mChosenExternal = NULL;

    ret = true;
  }

  return ret;
}

bool RandomScheduler::choose(AtomExternalPort &external) {
  bool ret = false;

  Interval interv = engine().interval(external);

  if (choose(interv, plan(interv), hasChosenInteraction() || hasChosenInternal())) {
    mChosenInteraction = NULL;
    mChosenInternal = NULL;
    mChosenExternal = &external;

    ret = true;
  }

  return ret;
}

bool RandomScheduler::hasChosen() const {
  return hasChosenInteraction() ||
         hasChosenInternal()    ||
         hasChosenExternal();
}

/**
 * \brief 
 *
 *
 * \param 
 * 
 * \return
 */
 bool RandomScheduler::choose(const Interval &interval, const TimeValue &plannedTime, bool hasPriority) {
  bool ret = false;

  TimeValue criterion = schedulingCriterion(interval, plannedTime);

  if (criterion < mMinCriterion || (criterion == mMinCriterion && hasPriority)) {
    // found a new minimum for the criterion
    mMinCriterion = criterion;
    mNbMinCriterion = 1;

    ret = true;
  }
  else if (criterion == mMinCriterion) {
    ++mNbMinCriterion;

    // random choice between whose which minimize the criterion
    if ((unsigned int) (mNbMinCriterion * (rand() / (RAND_MAX + 1.0))) == mNbMinCriterion - 1) {
      ret = true;
    }
  }

  if (ret) {
    mWakeUpTime = plannedTime;
  }

  return ret;
}

/**
 * \brief Chose an execution time meeting a given timing constraint.
 *
 * The choice is made according to the selected scheduling policy,
 * i.e. ASAP or random.
 *
 * \param interval is the target interval.
 * 
 * \return a time value meeting the timing constraint.
 */
TimeValue RandomScheduler::plan(const Interval &interval) const {
  TimeValue ret;

  if (asap()) {
    ret = interval.next(engine().time());
  }
  else {
    ret = interval.random(TimeValue(1, NANOSECOND));
  }

  return ret;
}

/**
 * \brief Criterion the scheduler should minimize.
 *
 * In the case of firstEnabled scheduling policy,
 * the criterion is the next time value that belong
 * to the target interval from the current time,
 * otherwise it is the planned execution time.
 *
 * \param interval is the validity interval of the target
 * interaction / internal port / external port to schedule.
 * \param planned is the planned time for execution of the
 * target interaction / internal port / external.
 * 
 * \return the time value defining the scheduling
 * criterion to be minimized.
 */
TimeValue RandomScheduler::schedulingCriterion(const Interval &interval, const TimeValue &planned) const {
  TimeValue ret = TimeValue::MAX;

  if (firstEnabled()) {
    ret = interval.next(engine().time());
  }
  else {
    ret = planned;
  }

  return ret;
}

/**
 * \brief Update model time w.r.t. actual time and check that such an
 * update meets timing constraints (urgency, invariants).
 * a useful report to the user (e.g. error message, etc.).
 *
 * \return false if the update of the model time satisfied the timing
 * constraints.
 */
BipError &RandomScheduler::checkTimeSafety() {
  TimeValue ret = TimeValue::MAX;

  // skip it if relaxed and current time = next deadline
  if (!relaxed() || engine().time() < engine().waitInterval().right()) {
    TimeValue currentTime = platformClock().time();

    if (!engine().waitInterval().in(currentTime)) {
      TimeSafetyViolationError &error = *new TimeSafetyViolationError(currentTime);

      return error;
    }
    else {
      engine().wait(currentTime);
    }
  }

  return BipError::NoError;
}

/**
 * \brief Update model time w.r.t. actual time and check that such an
 * update meets timing constraints (urgency, invariants).
 * a useful report to the user (e.g. error message, etc.).
 *
 * \return false if the update of the model time satisfied the timing
 * constraints.
 */
BipError &RandomScheduler::checkTimeSafetyAndResume() {
  TimeValue ret = TimeValue::MAX;

  // skip it if relaxed and current time = next deadline
  if (!relaxed() || engine().time() < engine().waitInterval().right()) {
    TimeValue currentTime = platformClock().time();

    if (!engine().resumeInterval().in(currentTime)) {
      TimeSafetyViolationError &error = *new TimeSafetyViolationError(currentTime);

      return error;
    }
    else {
      BipError &error = engine().resume(currentTime);

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
  }

  return BipError::NoError;
}

bool RandomScheduler::deadlock() const {
  return engine().interactions().empty() && // interaction to execute
         engine().internals().empty()    && // internal port to execute
         engine().externals().empty()    && // external port to execute
    (engine().waiting().empty() || platformClock().time() > engine().waitInterval().right());        // external port waiting
}

bool RandomScheduler::waitForNotificationsUntil(const TimeValue &time) {
  bool ret = false;

  sigset_t maskOld, maskSIGBIP;

  sigemptyset(&maskSIGBIP);
  sigaddset(&maskSIGBIP, Engine::SIGBIP);

  sigprocmask(SIG_BLOCK, &maskSIGBIP, &maskOld);

  if (hasNotifications()) {
    ret = true;
  }
  else {
    ret = platformClock().wait(time);
  }

  sigprocmask(SIG_UNBLOCK, &maskSIGBIP, NULL);

  return ret;
}

void RandomScheduler::notify() {
  kill(RandomScheduler::pid, Engine::SIGBIP);
}

pid_t RandomScheduler::pid(0);

GlobalClock *RandomScheduler::mStaticPlatformClock(NULL);

volatile unsigned int RandomScheduler::mNbReceivedNotifications(0);

void RandomScheduler::handleSignals(int signum) {
  if (signum == Engine::SIGBIP) {
    mNbReceivedNotifications++;
  }
}

/**
 * \brief Displays the current state of the system.
 *
 * Useful for debug purpose. Side effect on cout.
 */
void RandomScheduler::print() {
  const Engine &constEngine = engine();
  const Compound &top = constEngine.top();

  StringTree debugStrTree = print(top);
  string header = "[BIP ENGINE]: ";
  string debugStr = debugStrTree.toString(header);
  cout << debugStr;
}

StringTree RandomScheduler::print(const ConnectorExportPort &port) {
  StringTree ret(port.name());

  for (unsigned int i = 0 ; i < port.portValues().size() ; ++i) {
    string portStr = port.portValues()[i]->toString();

    if (portStr.size() == 0) {
      string noValueStr = "<no_value>";
      ret.addChild(noValueStr);
    }
    else {
      ret.addChild(portStr);
    }
  }

  return ret;
}

StringTree RandomScheduler::print(const CompoundExportPort &port) {
  StringTree ret(port.name());

  for (unsigned int i = 0 ; i < port.portValues().size() ; ++i) {
    string portStr = port.portValues()[i]->toString();

    if (portStr.size() == 0) {
      string noValueStr = "<no_value>";
      ret.addChild(noValueStr);
    }
    else {
      ret.addChild(portStr);
    }
  }

  return ret;
}

StringTree RandomScheduler::print(const AtomInternalPort &port) {
  string ret = port.name();

  if (port.hasPortValue()) {
    string portStr = port.portValue().toString();

    if (portStr.size() > 0) {
      ret = ret + " (" + portStr + ")";
    }
    else {
      ret = ret + " (<no_value>)";
    }
  }

  return StringTree(ret);
}

StringTree RandomScheduler::print(const AtomExportPort &port) {
  StringTree ret(port.name());

  for (unsigned int i = 0 ; i < port.internalPorts().size() ; ++i) {
    const AtomInternalPort &internalPort = *(port.internalPorts()[i]);
    ret.addChild(print(internalPort));
  }

  return ret;
}

StringTree RandomScheduler::print(const InteractionValue &interaction) {
  ostringstream oss;

  oss << interaction;

  oss << " " << interaction.timingConstraint();
  oss << " " << interaction.timingConstraintAfterPriorities() << "*";

  return StringTree(oss.str());
}

StringTree RandomScheduler::print(const Connector &connector) {
  StringTree ret(connector.name());

  if (connector.hasExportedPort()) {
    StringTree portTree = print(connector.exportedPort());
    ret.addChild(portTree);
  }

  const vector<InteractionValue *> &interactions = connector.enabledInteractions();

  for (unsigned int i = 0 ; i < interactions.size() ; ++i) {
    StringTree interactionTree = print(*interactions[i]);
    ret.addChild(interactionTree);
  }
  //connector.release(interactions);

  return ret;
}

StringTree RandomScheduler::print(const Atom &atom) {
  StringTree ret(atom.name());

  for (map<string, AtomExportPort *>::const_iterator portIt = atom.ports().begin() ;
       portIt != atom.ports().end() ;
       ++portIt) {
    const AtomExportPort &port = *(portIt->second);
    StringTree portTree = print(port);
    ret.addChild(portTree);
  }

  string atomStr = atom.toString();
  string::const_iterator beginIt = atomStr.begin();
  string::const_iterator strIt = atomStr.begin() ;

  while (strIt != atomStr.end()) {
    if (*strIt == '\n') {
      string childStr = string(beginIt, strIt);
      ret.addChild(childStr);
      beginIt = strIt + 1;
    }

    ++strIt;
  }

  if (beginIt != atomStr.end()) {
    string childStr = string(beginIt, strIt);
    ret.addChild(childStr);
  }

  return ret;
}

StringTree RandomScheduler::print(const Compound &compound) {
  StringTree ret(compound.name());

  for (map<string, CompoundExportPort *>::const_iterator portIt = compound.ports().begin() ;
       portIt != compound.ports().end() ;
       ++portIt) {
    const CompoundExportPort &port = *(portIt->second);
    StringTree portTree = print(port);
    ret.addChild(portTree);
  }

  for (map<string, Connector *>::const_iterator connIt = compound.connectors().begin() ;
       connIt != compound.connectors().end() ;
       ++connIt) {
    const Connector &connector = *(connIt->second);
    StringTree connectorTree = print(connector);
    ret.addChild(connectorTree);
  }

  for (map<string, Component *>::const_iterator connIt = compound.components().begin() ;
       connIt != compound.components().end() ;
       ++connIt) {
    const Component &component = *(connIt->second);
    StringTree componentTree = print(component);
    ret.addChild(componentTree);
  }

  return ret;
}

StringTree RandomScheduler::print(const Component &component) {
  if (component.type() == COMPOUND) {
    const Compound &compound = (const Compound &) component;
    return print(compound);
  }
  else if (component.type() == ATOM) {
    const Atom &atom = (const Atom &) component;
    return print(atom);
  }
  else {
    assert(false);
  }

  return StringTree();
}
