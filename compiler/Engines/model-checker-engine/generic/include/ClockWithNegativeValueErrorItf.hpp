#ifndef _BIP_Engine_ClockWithNegativeValueErrorItf_HPP_
#define _BIP_Engine_ClockWithNegativeValueErrorItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// inherited classes
#include "BipErrorItf.hpp"

// used classes
#include "BipError.hpp"

// referenced classes
class Clock;

class ClockWithNegativeValueErrorItf : public virtual BipErrorItf {
public:
    // destructor
    virtual ~ClockWithNegativeValueErrorItf();

    // getters for references
    const Clock &clock() const { return *mClock; }

protected:
    // protected constructors
    ClockWithNegativeValueErrorItf(const Clock &clock);

    // references
    const Clock *mClock;
};

#endif // _BIP_Engine_ClockWithNegativeValueErrorItf_HPP_
