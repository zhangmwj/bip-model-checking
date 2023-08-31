#include <Constraint.hpp>

// constructors
Constraint::Constraint(bool b):
    ConstraintItf(b) {
}

Constraint::Constraint(const Clock &clock, int32_t bound, bool isLT, bool isStrict) :
    ConstraintItf(clock, bound, isLT, isStrict) {
}

Constraint::Constraint(int32_t bound, const Clock &clock, bool isLT, bool isStrict) :
    ConstraintItf(clock, bound, !isLT, isStrict) {
}

// destructor
Constraint::~Constraint(){
}

// operations
Constraint &Constraint::operator=(const Constraint &constraint) {
    setValueConstraints(constraint.valueConstraints());
    setTimingConstraints(constraint.timingConstraints());
    return *this;
}

Constraint &Constraint::operator=(bool b) {
    setValueConstraints(b);
    clearTimingConstraints();
    return *this;
}

// specific
Constraint &Constraint::operator&=(const Constraint &constraint) {
    if (!hasTimingConstraints()) { // si this est un boolean
        if (valueConstraints()) { // this vaut true, alors this vaut constraint
            setValueConstraints(constraint.valueConstraints());
            setTimingConstraints(constraint.timingConstraints());
        }
        // sinon, this vaut false et pas besoin de modifier this
    }
    else { // si this est une constrainte sur le temps
        if (constraint.hasTimingConstraints()) { // et constraint aussi, on les ajoutes
            timingConstraints().insert(timingConstraints().end(), constraint.timingConstraints().begin(), constraint.timingConstraints().end());
        } else { // et constraint est un boolean
            if (!constraint.valueConstraints()) { // constraint vaut false, alors this vaut false
                setValueConstraints(constraint.valueConstraints());
                clearTimingConstraints();
            }
            // sinon, constraint vaut true et pas besoin de modifier this
        }
    }
    return *this;
}

Constraint Constraint::operator&&(const Constraint &constraint) const {
    Constraint ret = *this;
    ret &= constraint;
    return ret;
}

Constraint Constraint::operator&&(bool b) const {
    if (b) return Constraint(*this);
    else return Constraint(b);
}

Constraint Constraint::operator||(bool b) const {
    if (b) return Constraint(b);
    else return Constraint(*this);
}

bool Constraint::constrain() const {
    if (hasTimingConstraints()) {
        assert(Clock::hasDbm());
        return Clock::constrainDbm(timingConstraints());
    }
    else return valueConstraints();
}

Constraint operator&&(bool b, const Constraint &constraint) {
    return constraint && b;
}

Constraint operator||(bool b, const Constraint &constraint) {
    return constraint || b;
}

bool Constraint::isSatisfied() const {
    if (hasTimingConstraints()) {
        assert(Clock::hasDbm());
        return !(Clock::dbm() & timingConstraints()).isEmpty();
    }
    return valueConstraints();
}
