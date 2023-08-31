
#include <ModelChecker.hpp>

prop getProp(string);
bool isReachability(string);

ModelChecker::ModelChecker(ModelCheckerEngine &engine, bool bfs):
        ModelCheckerScheduler(engine),
        mBfs(bfs) {
}

ModelChecker::~ModelChecker() {
}

BipError &ModelChecker::run() {
  cout << "[BIP ENGINE]: Compute states visited by model checking " << (mBfs? "BFS:" : "DFS:") << endl;
  peek fpeek;
  if (mBfs)
    fpeek =  &list<const State *>::front;
  else fpeek = &list<const State *>::back;
  pop fpop = mBfs ? &list<const State *>::pop_front : &list<const State *>::pop_back;

  if (mProperties.empty())
    return computeMC(fpeek, fpop);
  for (string &s : mProperties) {
    cout << "Check property " << s << endl;
    const State *state = nullptr;
    bool reachability = isReachability(s);
    BipError &error = checkProp(s, reachability, fpeek, fpop, &state);
    if (error.type() != NO_ERROR) {
      return error;
    }
    if (state == nullptr) {
      cout << s << " is " << (reachability ? "not" : "") << " satisfied" << endl;
    } else {
      cout << s << " is " << (reachability ? "" : "not") << " satisfied" << endl;
      cout << "Trace :" << endl;
      engine().printTrace(*state);
    }
  }
  return BipError::NoError;
}

BipError &ModelChecker::computeMC(peek fpeek, pop fpop) {
  unordered_set<const State *, State::hash_discret_part> pwlist;
  list<const State *> wait;
  wait.push_back(&engine().initialState());
  pwlist.insert(&engine().initialState());
  while (!wait.empty()) {
    const State &current = *(wait.*fpeek)();
    (wait.*fpop)();
    cout << "State #" << current.id() << endl;
    engine().setState(current);
    print();
    cout << endl;
    BipError &error = engine().computeSuccessors(current);
    if (error.type() != NO_ERROR) {
      return error;
    }
    cout << "Successors: ";
    for (const State *s: engine().successors(current)) {
      cout << "#" << s->id() << " ";
    }
    cout << endl << endl << endl;
    for (const State *s:  engine().successors(current)) {
      size_t bucket = pwlist.bucket(s);
      bool toAdd = true;
      for (auto it = pwlist.cbegin(bucket); it != pwlist.cend(bucket); ++it) {
        if (**it < *s) {
          wait.remove(*it);
        }
        if (*s <= **it) {
          toAdd = false;
        }
      }
      if (toAdd) {
        pwlist.insert(s);
        wait.push_back(s);
      }
    }
  }
  return BipError::NoError;
}