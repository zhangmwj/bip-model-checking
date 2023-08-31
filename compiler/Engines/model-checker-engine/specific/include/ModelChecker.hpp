#ifndef _BIP_Engine_ModelChecker_HPP_
#define _BIP_Engine_ModelChecker_HPP_
#include <ModelCheckerScheduler.hpp>

typedef list<const State *>::const_reference (list<const State *>::* peek)() const;
typedef void (list<const State*>::* pop)();

class ModelChecker : public ModelCheckerScheduler {
public:
  ModelChecker(ModelCheckerEngine &engine, bool bfs);
  virtual ~ModelChecker();

  virtual BipError &run();

protected:
  BipError &computeMC(peek, pop);
  bool mBfs;
};

#endif // _BIP_Engine_ModelChecker_HPP_