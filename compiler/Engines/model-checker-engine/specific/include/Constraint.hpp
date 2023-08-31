
#ifndef _BIP_Engine_Constraint_HPP_
#define _BIP_Engine_Constraint_HPP_

// inherited classes
#include <ConstraintItf.hpp>

class Constraint : public ConstraintItf {
public:
    // constructors
    Constraint(bool b = true);
    Constraint(const Clock &clock, int32_t bound, bool isLT, bool isStrict);
    Constraint(int32_t bound, const Clock &clock, bool isLT, bool isStrict);
    // destructor
    virtual ~Constraint();

    // operations
    virtual Constraint &operator=(const Constraint &constraint);
    virtual Constraint &operator=(bool b);

    // specific
    Constraint &operator&=(const Constraint &constraint);
    Constraint operator&&(const Constraint &constraint) const;
    Constraint operator&&(bool b) const;
    Constraint operator||(bool b) const;
    bool constrain() const;
    bool isSatisfied() const;
    friend Constraint operator&&(bool b, const Constraint &constraint);
    friend Constraint operator||(bool b, const Constraint &constraint);
};

#endif // _BIP_Engine_Constraint_HPP_
