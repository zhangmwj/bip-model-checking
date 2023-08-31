
#ifndef _BIP_Engine_ZoneGraph_HPP_
#define _BIP_Engine_ZoneGraph_HPP_

#include <ModelCheckerScheduler.hpp>

class ZoneGraph : public ModelCheckerScheduler {
public:
  ZoneGraph(ModelCheckerEngine &engine);
  virtual ~ZoneGraph();

  virtual BipError &run();

protected:
  BipError &computeZoneGraph();
};

#endif // _BIP_Engine_ZoneGraph_HPP_
