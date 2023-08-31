
#ifndef _BIP_Engine_ClockWithNegativeValueError_HPP_
#define _BIP_Engine_ClockWithNegativeValueError_HPP_

// inherited classes
#include <ClockWithNegativeValueErrorItf.hpp>
#include "BipError.hpp"


class ClockWithNegativeValueError : public virtual BipErrorItf, public BipError, public ClockWithNegativeValueErrorItf {
public:
    // constructors
    ClockWithNegativeValueError(const Clock &clock);

    // destructor
    virtual ~ClockWithNegativeValueError();
};


#endif // _BIP_Engine_ClockWithNegativeValueError_HPP_
