#include <ConstraintItf.hpp>

// constructors
ConstraintItf::ConstraintItf(bool b) :
    mValueConstraints(b),
    mTimingConstraints() {
}

ConstraintItf::ConstraintItf(const Clock &clock, int32_t bound, bool isLT, bool isStrict)
{
    if (isLT)
        mTimingConstraints.push_back(dbm_constraint2(clock.getIndex(), 0, bound, isStrict));
    else
        mTimingConstraints.push_back(dbm_constraint2(0, clock.getIndex(), -bound, isStrict));
}

// destructor
ConstraintItf::~ConstraintItf() {
}
