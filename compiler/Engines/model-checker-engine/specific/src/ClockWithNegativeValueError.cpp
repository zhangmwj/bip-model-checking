#include <ClockWithNegativeValueError.hpp>

// constructors
ClockWithNegativeValueError::ClockWithNegativeValueError(const Clock &clock) :
        BipErrorItf(CLOCK_WITH_NEGATIVE_VALUE),
        BipError(CLOCK_WITH_NEGATIVE_VALUE),
        ClockWithNegativeValueErrorItf(clock) {
  /* implement your constructor here */
}

// destructor
ClockWithNegativeValueError::~ClockWithNegativeValueError() {
  /* implement your destructor here */
}
