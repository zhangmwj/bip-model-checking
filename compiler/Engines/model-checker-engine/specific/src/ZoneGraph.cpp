#include <ZoneGraph.hpp>

ZoneGraph::ZoneGraph(ModelCheckerEngine &engine):
  ModelCheckerScheduler(engine) {
}

ZoneGraph::~ZoneGraph() {
}

BipError &ZoneGraph::run() {
  cout << "[BIP ENGINE]: Compute zone graph" << endl;
  return computeZoneGraph();
}

BipError &ZoneGraph::computeZoneGraph() {
  vector<const State *> passed;
  list<const State *> wait;
  wait.push_back(&engine().initialState());
  while (!wait.empty()) {
    const State &current = *wait.front();
    wait.pop_front();
    // check for visited passed
    if (find(passed.begin(), passed.end(), &current) == passed.end()) {
      cout << "State #" << current.id() << endl;
      engine().setState(current);
      print();
      cout << endl;
      // add the current state to reachable passed
      passed.push_back(&current);
      BipError &error = engine().computeSuccessors(current);

      if (error.type() != NO_ERROR) {
        return error;
      }
      cout << "Successors: ";
      for (const State *s: engine().successors(current)) {
        cout << "#" << s->id() << " ";
        wait.push_back(s);
      }
      cout << endl << endl << endl;
    }
  }
  return BipError::NoError;
}
