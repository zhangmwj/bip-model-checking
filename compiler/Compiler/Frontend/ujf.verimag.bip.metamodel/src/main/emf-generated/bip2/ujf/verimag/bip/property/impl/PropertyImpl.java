/**
 */
package bip2.ujf.verimag.bip.property.impl;

import bip2.ujf.verimag.bip.actionlang.ValuedExpression;

import bip2.ujf.verimag.bip.property.Property;
import bip2.ujf.verimag.bip.property.PropertyPackage;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Property</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.property.impl.PropertyImpl#isReachability <em>Reachability</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.property.impl.PropertyImpl#getExpression <em>Expression</em>}</li>
 * </ul>
 *
 * @generated
 */
public class PropertyImpl extends AnnotatedEObjectImpl implements Property {
    /**
     * The default value of the '{@link #isReachability() <em>Reachability</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #isReachability()
     * @generated
     * @ordered
     */
    protected static final boolean REACHABILITY_EDEFAULT = true;

    /**
     * The cached value of the '{@link #isReachability() <em>Reachability</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #isReachability()
     * @generated
     * @ordered
     */
    protected boolean reachability = REACHABILITY_EDEFAULT;

    /**
     * The cached value of the '{@link #getExpression() <em>Expression</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getExpression()
     * @generated
     * @ordered
     */
    protected ValuedExpression expression;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected PropertyImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return PropertyPackage.Literals.PROPERTY;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public boolean isReachability() {
        return reachability;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void setReachability(boolean newReachability) {
        boolean oldReachability = reachability;
        reachability = newReachability;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PropertyPackage.PROPERTY__REACHABILITY, oldReachability,
                    reachability));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public ValuedExpression getExpression() {
        return expression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetExpression(ValuedExpression newExpression,
            NotificationChain msgs) {
        ValuedExpression oldExpression = expression;
        expression = newExpression;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET, PropertyPackage.PROPERTY__EXPRESSION,
                    oldExpression, newExpression);
            if (msgs == null)
                msgs = notification;
            else
                msgs.add(notification);
        }
        return msgs;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void setExpression(ValuedExpression newExpression) {
        if (newExpression != expression) {
            NotificationChain msgs = null;
            if (expression != null)
                msgs = ((InternalEObject) expression).eInverseRemove(this,
                        EOPPOSITE_FEATURE_BASE
                                - PropertyPackage.PROPERTY__EXPRESSION,
                        null, msgs);
            if (newExpression != null)
                msgs = ((InternalEObject) newExpression).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - PropertyPackage.PROPERTY__EXPRESSION,
                        null, msgs);
            msgs = basicSetExpression(newExpression, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PropertyPackage.PROPERTY__EXPRESSION, newExpression,
                    newExpression));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public NotificationChain eInverseRemove(InternalEObject otherEnd,
            int featureID, NotificationChain msgs) {
        switch (featureID) {
        case PropertyPackage.PROPERTY__EXPRESSION:
            return basicSetExpression(null, msgs);
        }
        return super.eInverseRemove(otherEnd, featureID, msgs);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case PropertyPackage.PROPERTY__REACHABILITY:
            return isReachability();
        case PropertyPackage.PROPERTY__EXPRESSION:
            return getExpression();
        }
        return super.eGet(featureID, resolve, coreType);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void eSet(int featureID, Object newValue) {
        switch (featureID) {
        case PropertyPackage.PROPERTY__REACHABILITY:
            setReachability((Boolean) newValue);
            return;
        case PropertyPackage.PROPERTY__EXPRESSION:
            setExpression((ValuedExpression) newValue);
            return;
        }
        super.eSet(featureID, newValue);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void eUnset(int featureID) {
        switch (featureID) {
        case PropertyPackage.PROPERTY__REACHABILITY:
            setReachability(REACHABILITY_EDEFAULT);
            return;
        case PropertyPackage.PROPERTY__EXPRESSION:
            setExpression((ValuedExpression) null);
            return;
        }
        super.eUnset(featureID);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public boolean eIsSet(int featureID) {
        switch (featureID) {
        case PropertyPackage.PROPERTY__REACHABILITY:
            return reachability != REACHABILITY_EDEFAULT;
        case PropertyPackage.PROPERTY__EXPRESSION:
            return expression != null;
        }
        return super.eIsSet(featureID);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public String toString() {
        if (eIsProxy())
            return super.toString();

        StringBuilder result = new StringBuilder(super.toString());
        result.append(" (reachability: ");
        result.append(reachability);
        result.append(')');
        return result.toString();
    }

} //PropertyImpl
