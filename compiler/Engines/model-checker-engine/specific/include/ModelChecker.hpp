#ifndef _BIP_Engine_ModelChecker_HPP_
#define _BIP_Engine_ModelChecker_HPP_
#include <ModelCheckerScheduler.hpp>
typedef bool (*prop)();

typedef list<const State *>::const_reference (list<const State *>::* peek)() const;
typedef void (list<const State*>::* pop)();

class ModelChecker : public ModelCheckerScheduler {
public:
  ModelChecker(ModelCheckerEngine &engine, bool bfs);
  virtual ~ModelChecker();

  virtual BipError &run();

  void addProperty(const string &propertyName) { mProperties.push_back(propertyName); }
protected:
  BipError &computeMC(peek, pop);
  BipError &checkProp(string, bool, peek, pop, const State **);

  bool mBfs;
  vector<string> mProperties;
};

#endif // _BIP_Engine_ModelChecker_HPP_