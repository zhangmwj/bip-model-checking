#include <ModelCheckerScheduler.hpp>
#include "engine-version.hpp"
#include "bip-engineiface-config.hpp"
using namespace bipbasetypes;
#include "Atom.hpp"

ModelCheckerScheduler::ModelCheckerScheduler(ModelCheckerEngine &engine):
  mEngine(engine) {
}

ModelCheckerScheduler::~ModelCheckerScheduler() {
}

BipError &ModelCheckerScheduler::initialize() {
  cout << "[BIP ENGINE]: BIP Model Checker Engine (version " ENGINE_VERSION  " )" << endl;
  cout << "[BIP ENGINE]:" << endl;
  cout << "[BIP ENGINE]: initialize components..." << endl;
  return engine().initialize();
}

void ModelCheckerScheduler::print() const {
  engine().print();
}