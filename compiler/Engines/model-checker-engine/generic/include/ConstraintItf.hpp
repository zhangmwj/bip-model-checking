
#ifndef _BIP_Engine_ConstraintItf_HPP_
#define _BIP_Engine_ConstraintItf_HPP_

#include <bip-engineiface-config.hpp>
#include <dbm/constraints.h>

using namespace bipbasetypes;

// used classes
#include "Clock.hpp"
#include "TimeValue.hpp"

// referenced classes
class Constraint;

class ConstraintItf {
public:
    // destructor
    virtual ~ConstraintItf();

    // operations
    virtual Constraint &operator=(const Constraint &constraint) = 0;
    virtual Constraint &operator=(bool b) = 0;

    // getters for attributes
    bool hasTimingConstraints() const { return !mTimingConstraints.empty(); }
    bool valueConstraints() const { return mValueConstraints; }
    const vector<constraint_t> &timingConstraints() const { return mTimingConstraints; }

    // setters for attributes
    void setValueConstraints(bool b) { mValueConstraints = b; }
    void setTimingConstraints(const vector<constraint_t> &timingConstraint) { mTimingConstraints = timingConstraint; }
    void clearTimingConstraints() { mTimingConstraints.clear(); }

protected:
    // protected constructor
    ConstraintItf(bool b = true);
    ConstraintItf(const Clock &clock, int32_t bound, bool isLT, bool isStrict);

    vector<constraint_t> &timingConstraints() { return mTimingConstraints; }

    // attributes
    bool mValueConstraints;
    vector<constraint_t> mTimingConstraints;
};

#endif // _BIP_Engine_ConstraintItf_HPP_
