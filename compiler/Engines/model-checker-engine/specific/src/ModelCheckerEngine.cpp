#include <ModelCheckerEngine.hpp>
#include <Atom.hpp>
#include <Constraint.hpp>
#include <Compound.hpp>
#include <dbm/fed.h>
#include <dbm/constraints.h>

using namespace dbm;

void serialize(char **, size_t *);

void deserialize(const char *, size_t);

ModelCheckerEngine::ModelCheckerEngine(Compound &top):
  mTop(top),
  mInitialState(nullptr) {
}

ModelCheckerEngine::~ModelCheckerEngine() {
}

BipError &ModelCheckerEngine::initialize() {
  clocks().clear();
  Clock::configureDbm(dbm(), clocks());
  BipError &error = top().initialize();
  if (error.type() == NO_ERROR) {
    if (hasClocks()) {
      initDbm();
      initKMax();
    }
    initConnectorPriorities();
    BipError &error2 = getState(&mInitialState);
    if (error2.type() != NO_ERROR)
      return error2;
  }
  return error;
}

void ModelCheckerEngine::initDbm() {
  dbm().setDimension((int) clocks().size() + 2);
  dbm().setZero();
}

void ModelCheckerEngine::initKMax() {
  cindex_t dimension = dbm().getDimension();
  kMax().clear();
  kMax().reserve(dimension);
  for (cindex_t i = 0; i < dimension; i++) {
    kMax().push_back(0);
  }

  for (const Constraint &c : top().allTimingConstraints()) {
    for (const constraint_t &tc: c.timingConstraints()) {
      assert ((tc.i == 0 || tc.j == 0) && tc.i != tc.j);
      cindex_t clock = tc.i == 0 ? tc.j : tc.i;
      int32_t value = dbm_raw2bound(tc.value);
      if (value < 0)
        value = -value;
      if (kMax()[clock] < value)
        kMax()[clock] = value;
    }
  }
}

void ModelCheckerEngine::computePriorityGraph() {
  priorities().clear();
  highestConnector().clear();

  list<const Connector *> highest;
  for (const pair<string, Connector *> it : top().getConnectors()) {
    highest.push_back(it.second);
  }

  for (Priority *priority : top().getPriorities()) {
    if (priority->hasHigh() && priority->hasLow()) { // C1:* < C2:*
      priorities()[&priority->high().connector()].push_back(&priority->low().connector());
      highest.remove(&priority->low().connector());
    } else if (priority->hasHigh()) { // *:* < C:*
      for (const pair<string, Connector *> it: top().getConnectors()) {
        if (it.second != &priority->high().connector())
          priorities()[&priority->high().connector()].push_back(it.second);
      }
      highest.clear();
      highest.push_back(&priority->high().connector());
    } else if (priority->hasLow()) { // C:* < *:*
      for (const pair<string, Connector *> it : top().getConnectors()) {
        if (it.second != &priority->low().connector())
          priorities()[it.second].push_back(&priority->low().connector());
      }
      highest.remove(&priority->low().connector());
    } else {
      assert(false); // *:* < *:*
    }
  }
  assert(!highest.empty());
  highestConnector().insert(highestConnector().begin(), highest.begin(), highest.end());
}

vector<const Connector *> ModelCheckerEngine::reachableConnectors(const Connector &c) {
  vector<const Connector *> passed;
  vector<const Connector *> wait = priorities()[&c];
  while (!wait.empty()) {
    const Connector *current = wait.back();
    wait.pop_back();
    if (find(passed.begin(), passed.end(), current) == passed.end()) {
      passed.push_back(current);
      wait.insert(wait.end(), priorities()[current].begin(), priorities()[current].end());
    }
  }
  return passed;
}

void ModelCheckerEngine::computePriorityReduction() {
  for (const auto &prioIt : priorities()) {
    const Connector *u = prioIt.first;
    vector<const Connector *> &successors = priorities()[u];
    const vector<const Connector *> successorsCopy = prioIt.second;
    for (const Connector *c : successorsCopy) {
      vector<const Connector *> reachable = reachableConnectors(*c);
      successors.erase(remove_if(successors.begin(), successors.end(),
                                   [&reachable] (const Connector *c)
                                   { return find(reachable.begin(), reachable.end(), c) != reachable.end(); }),
                       successors.end());
    }
  }
}

void ModelCheckerEngine::initConnectorPriorities() {
  computePriorityGraph();
  computePriorityReduction();
}

BipError &ModelCheckerEngine::computeInternalSuccessors(const State &state, bool &findEager){
  setState(state);
  vector<AtomInternalPort *> internals = top().internals();
  unsigned int nbInternals = internals.size();

  for (unsigned int i = 0; i < nbInternals; i++) {
    setState(state);
    AtomInternalPort &currentInternal = *internals[i];
    PortValue p = currentInternal.portValue();
    if (p.urgency() == EAGER) {
      assert(!p.hasGuard() || !p.guard().hasTimingConstraints());
    } else {
      if (findEager)
        continue;
    }

    BipError &error = currentInternal.holder().execute(currentInternal);

    switch (error.type()) {
      case NO_ERROR:
        if (findEager) {
          return error;
        } else {
          const State *s;
          BipError &error2 = getState(&s);
          if (error2.type() != NO_ERROR) {
            return error2;
          }
          successors()[state].push_back(s);
        }
        break;
      case ATOM_INVARIANT_VIOLATION:
        delete &error;
        break;
      default:
        return error;
    }
  }
  findEager = false;
  return BipError::NoError;
}

BipError &ModelCheckerEngine::computeInteractionSuccessors(const State &state, bool &findEager) {
  list<const Connector *> connectorToDo(highestConnector().begin(), highestConnector().end());
  set<const Connector *> connectorDone;

  while (!connectorToDo.empty()) {
    const Connector *currentConnector = connectorToDo.front();
    connectorToDo.pop_front();
    if (connectorDone.find(currentConnector) == connectorDone.end()) {
      bool findInteraction = false;

      setState(state);
      vector<InteractionValue *> interactionToDo = currentConnector->enabledInteractions(true);
      sort(interactionToDo.begin(), interactionToDo.end(), [](InteractionValue *i, InteractionValue *j)
           { return i->portValues().size() <= j->portValues().size(); });
      vector<InteractionValue *> maximalInteractions;

      while (!interactionToDo.empty()) {
        InteractionValue &currentInteraction = *interactionToDo.back();
        interactionToDo.pop_back();

        bool isMaximal = true;
        for (InteractionValue *j: maximalInteractions) {
          if (currentInteraction.interaction() < j->interaction()) {
            isMaximal = false;
            break;
          }
        }

        if (isMaximal) {
          setState(state);
          if (currentInteraction.urgency() == EAGER)
            assert(!currentInteraction.constraint().hasTimingConstraints());

          // execute
          currentInteraction.connector().down(currentInteraction);
          BipError &error = currentInteraction.connector().holder().execute(currentInteraction);

          switch(error.type()) {
            case NO_ERROR:
              findInteraction = true;
              if (findEager) {
                if (currentInteraction.urgency() == EAGER) {
                  for (InteractionValue *i : interactionToDo) {
                    i->connector().releaseInteractionValue(*i);
                  }
                  currentInteraction.connector().releaseInteractionValue(currentInteraction);
                  return error;
                }
              } else {
                const State *s;
                BipError &error2 = getState(&s);
                if (error2.type() != NO_ERROR) {
                  return error2;
                }
                successors()[state].push_back(s);
              }
              break;
            case ATOM_INVARIANT_VIOLATION:
              break;
            default:
              return error;
          }
        }
        currentInteraction.connector().releaseInteractionValue(currentInteraction);
      }
      connectorDone.insert(currentConnector);
      if (!findInteraction) {
        connectorToDo.insert(connectorToDo.end(), priorities()[currentConnector].begin(), priorities()[currentConnector].end());
      } else {
        vector<const Connector *> addToDone = reachableConnectors(*currentConnector);
        connectorDone.insert(addToDone.begin(), addToDone.end());
      }
    }
  }
  findEager = false;
  return BipError::NoError;
}

BipError &ModelCheckerEngine::isDelayable(bool &findEager) {
  if (!hasClocks()) {
    findEager = false;
    return BipError::NoError;
  } else {
    findEager = true;
    char *stateBuffer;
    size_t stateSize;
    serialize(&stateBuffer, &stateSize);
    const State state(stateBuffer, stateSize, dbm());
    BipError &internalError = computeInternalSuccessors(state, findEager);
    switch (internalError.type()) {
      case NO_ERROR:
        if (!findEager) {
          findEager = true;
          BipError &externalError = computeInteractionSuccessors(state, findEager);
          return externalError;
        }
      default:
        return internalError;
    }
  }
}

BipError &ModelCheckerEngine::getState(const State **state) {
  char *stateBuffer;
  size_t stateSize;
  serialize(&stateBuffer, &stateSize);

  if (!hasClocks()) {
    auto ret = successors().emplace(std::piecewise_construct,
                         std::forward_as_tuple(stateBuffer, stateSize),
                         std::forward_as_tuple());
    if (ret.second) {
      mSuccessors[ret.first->first].push_back(nullptr);
    }
    *state = &ret.first->first;
    return BipError::NoError;
  } else {
    dbm_t stateDbm(dbm()(), dbm().getDimension());
    const Constraint invariants = top().invariantConstraint();
    bool findEager;
    BipError &error = isDelayable(findEager);
    if (error.type() != NO_ERROR) {
      return error;
    }
    if (!findEager) {
      stateDbm.up();
      stateDbm &= invariants.timingConstraints();
    }
    stateDbm.extrapolateMaxBounds(kMax().data());
    auto ret = successors().emplace(std::piecewise_construct,
                         std::forward_as_tuple(stateBuffer, stateSize, stateDbm),
                         std::forward_as_tuple());
    if (ret.second) {
      mSuccessors[ret.first->first].push_back(nullptr);
    }
    *state = &ret.first->first;
    return BipError::NoError;
  }
}

void ModelCheckerEngine::setState(const State &state) {
  if (hasClocks()) {
    dbm() = state.dbm()();
  }
  deserialize(state.buffer(), state.size());
}

const vector<const State *> &ModelCheckerEngine::successors(const State &state) {
  return successors()[state];
}

BipError &ModelCheckerEngine::computeSuccessors(const State &state) {
  vector<const State *> &ret = successors()[state];
  if (ret.size() == 1 && ret[0] == nullptr) {
    ret.clear();
    bool findEager = false;
    BipError &internalError = computeInternalSuccessors(state, findEager);
    if (internalError.type() != NO_ERROR) {
      return internalError;
    }
    // size_t nbInternals = ret.size();
    BipError &externalError = computeInteractionSuccessors(state, findEager);
    if (externalError.type() != NO_ERROR) {
      return externalError;
    }
  }
  return BipError::NoError;
}

void ModelCheckerEngine::print() const {
  bool first = true;
  for (const pair<string, Component*> it : top().components()) {
    Component &component = *it.second;
    assert(component.type() == ATOM);
    Atom &atom = dynamic_cast<Atom &>(component);
    if (first) {
      first = false;
    } else {
      cout << ", ";
    }
    cout << atom.toString();
  }
  cout << endl << endl;
  if (hasClocks()) {
    cout << "Zone : " << endl;
    printDbm();
    cout << endl;
    printConstraints();
  }
}

void ModelCheckerEngine::printDbm() const {
  const cindex_t dim = dbm().getDimension();
  cout << '\t' << "0" << '\t' << "global";
  for (const Clock *c : mClocks) {
    cout << '\t' << c->fullname();
  }
  cout << endl;
  for (cindex_t i = 0; i < dim; ++i) {
    cout << (i == 0? "0" : i == 1 ? "global" : mClocks[i-2]->fullname());
    for (cindex_t j = 0; j < dim; ++j) {
      cout << '\t';
      dbm_cppPrintRaw(cout, dbm()(i, j)) ;
    }
    cout << "\\\n";
  }
}

void ModelCheckerEngine::printConstraints() const {
  cindex_t dim = dbm().getDimension();
  uint32_t bitMatrix[bits2intsize(dim*dim)];
  size_t nbConstraints = dbm_analyzeForMinDBM(dbm()(), dim, bitMatrix);
  uint32_t index[dim*(dim-1)];
  dbm_bitMatrix2indices(bitMatrix, nbConstraints, index, dim);

  raw_t r;
  for (size_t i = 0; i < mClocks.size(); i++) {
    cindex_t clockIndex = i + 2;
    r = dbm()(0,clockIndex);
    cout << mClocks[i]->fullname() << (dbm_rawIsStrict(r) ? " > " : " >= ") << -dbm_raw2bound(r) << endl;
    r = dbm()(clockIndex, 0);
    if (dbm_raw2bound(r) != dbm_INFINITY) {
      cout << mClocks[i]->fullname() << (dbm_rawIsStrict(r) ? " < " : " <= ") << dbm_raw2bound(r) << endl;
    }
  }
  r = dbm()(0,1);
  cout << "global" << (dbm_rawIsStrict(r) ? " > " : " >= ") << -dbm_raw2bound(r) << endl;

  for (cindex_t k = 0; k < nbConstraints; k++) {
    cindex_t i = index[k] & 0xffff;
    cindex_t j = index[k] >> 16;
    if (i != 0 && j != 0) {
      string iName = i == 1 ? "global" : mClocks[i - 2]->fullname();
      string jName = j == 1 ? "global" : mClocks[j - 2]->fullname();
      r = dbm()(i, j);
      cout << iName << " - " << jName << (dbm_rawIsStrict(r) ? " < " : " <= ") << dbm_raw2bound(r) << endl;
    }
  }
}