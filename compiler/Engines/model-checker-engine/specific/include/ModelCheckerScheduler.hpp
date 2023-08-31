
#ifndef _BIP_Engine_ModelCheckerScheduler_HPP_
#define _BIP_Engine_ModelCheckerScheduler_HPP_

#include "ModelCheckerEngine.hpp"

class BipError;

class ModelCheckerScheduler {
public :
  ModelCheckerScheduler(ModelCheckerEngine &engine);
  virtual ~ModelCheckerScheduler();

  virtual BipError &initialize();
  virtual BipError &run() = 0;
  const ModelCheckerEngine &engine() const { return mEngine; }

protected:
  void print() const;
  ModelCheckerEngine &engine() { return mEngine; }
  ModelCheckerEngine &mEngine;
};

#endif // _BIP_Engine_ModelCheckerScheduler_HPP_
