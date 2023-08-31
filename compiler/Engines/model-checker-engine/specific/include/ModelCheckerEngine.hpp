
#ifndef _BIP_Engine_ModelCheckerEngine_HPP_
#define _BIP_Engine_ModelCheckerEngine_HPP_

#include <Compound.hpp>
#include <State.hpp>
#include <BipError.hpp>
#include <bip-engineiface-config.hpp>
#include <dbm/fed.h>
using namespace dbm;

class InteractionValue;

class AtomInternalPort;

class ModelCheckerEngine {
public:
  ModelCheckerEngine(Compound &top);
  virtual ~ModelCheckerEngine();

  const Compound &top() const { return mTop; }
  const dbm_t &dbm() const { return mDbm; }
  const State &initialState() const { return *mInitialState; }

  BipError &initialize();
  void setState(const State &state);
  void print() const;
  BipError &computeSuccessors(const State &state);
  const vector<const State *> &successors(const State &state);
  void printTrace(const State &state);

protected:
  void initDbm();
  void initKMax();

  void computePriorityGraph();
  vector<const Connector *> reachableConnectors(const Connector &c);
  void computePriorityReduction();
  void initConnectorPriorities();

  BipError &computeInternalSuccessors(const State &state, bool &findEager);
  BipError &computeInteractionSuccessors(const State &state, bool &findEager);
  BipError &isDelayable(bool &findEager);
  BipError &getState(const State **state);
  void printDbm() const;
  void printConstraints() const;

  Compound &top() { return mTop; }
  dbm_t &dbm() { return mDbm; }
  vector<const Clock *> &clocks() { return mClocks; }
  bool hasClocks() const { return !mClocks.empty(); }
  vector<int32_t> &kMax() { return mKMax; }
  vector<const Connector *> &highestConnector() { return mHighestConnector; }
  map<const Connector *, vector<const Connector *>> &priorities() { return mPriorities; }

  unordered_map<const State, pair<const State *, vector<const State*>>, State::hash_all> &successors() { return mSuccessors; }

  Compound &mTop;

  dbm_t mDbm;
  vector<const Clock *> mClocks;
  vector<int32_t> mKMax;

  vector<const Connector *> mHighestConnector;
  map<const Connector *, vector<const Connector *>> mPriorities;

  const State *mInitialState;
  // si vector size == 0 => pas de successors
  // si vector[0] == nullptr => pas encore calculer
  unordered_map<const State, pair<const State *,vector<const State*>>, State::hash_all> mSuccessors;
};

#endif // _BIP_Engine_ModelCheckerEngine_HPP_
