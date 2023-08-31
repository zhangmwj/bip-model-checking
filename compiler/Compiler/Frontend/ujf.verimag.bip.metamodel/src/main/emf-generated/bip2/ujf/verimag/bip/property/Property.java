/**
 */
package bip2.ujf.verimag.bip.property;

import bip2.ujf.verimag.bip.actionlang.ValuedExpression;

import ujf.verimag.bip.metamodel.AnnotatedEObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Property</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.property.Property#isReachability <em>Reachability</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.property.Property#getExpression <em>Expression</em>}</li>
 * </ul>
 *
 * @see bip2.ujf.verimag.bip.property.PropertyPackage#getProperty()
 * @model
 * @extends AnnotatedEObject
 * @generated
 */
public interface Property extends AnnotatedEObject {
    /**
     * Returns the value of the '<em><b>Reachability</b></em>' attribute.
     * The default value is <code>"true"</code>.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the value of the '<em>Reachability</em>' attribute.
     * @see #setReachability(boolean)
     * @see bip2.ujf.verimag.bip.property.PropertyPackage#getProperty_Reachability()
     * @model default="true" required="true"
     * @generated
     */
    boolean isReachability();

    /**
     * Sets the value of the '{@link bip2.ujf.verimag.bip.property.Property#isReachability <em>Reachability</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Reachability</em>' attribute.
     * @see #isReachability()
     * @generated
     */
    void setReachability(boolean value);

    /**
     * Returns the value of the '<em><b>Expression</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the value of the '<em>Expression</em>' containment reference.
     * @see #setExpression(ValuedExpression)
     * @see bip2.ujf.verimag.bip.property.PropertyPackage#getProperty_Expression()
     * @model containment="true" required="true"
     * @generated
     */
    ValuedExpression getExpression();

    /**
     * Sets the value of the '{@link bip2.ujf.verimag.bip.property.Property#getExpression <em>Expression</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Expression</em>' containment reference.
     * @see #getExpression()
     * @generated
     */
    void setExpression(ValuedExpression value);

} // Property
