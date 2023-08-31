
#include <ClockWithNegativeValueErrorItf.hpp>

// constructors
ClockWithNegativeValueErrorItf::ClockWithNegativeValueErrorItf(const Clock &clock) :
        BipErrorItf(CLOCK_WITH_NEGATIVE_VALUE),
        mClock(&clock) {
}

// destructor
ClockWithNegativeValueErrorItf::~ClockWithNegativeValueErrorItf() {
}
