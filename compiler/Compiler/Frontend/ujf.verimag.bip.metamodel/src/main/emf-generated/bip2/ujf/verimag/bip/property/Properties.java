/**
 */
package bip2.ujf.verimag.bip.property;

import org.eclipse.emf.common.util.EMap;

import ujf.verimag.bip.metamodel.AnnotatedEObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Properties</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.property.Properties#getProperties <em>Properties</em>}</li>
 * </ul>
 *
 * @see bip2.ujf.verimag.bip.property.PropertyPackage#getProperties()
 * @model
 * @extends AnnotatedEObject
 * @generated
 */
public interface Properties extends AnnotatedEObject {
    /**
     * Returns the value of the '<em><b>Properties</b></em>' map.
     * The key is of type {@link java.lang.String},
     * and the value is of type {@link bip2.ujf.verimag.bip.property.Property},
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the value of the '<em>Properties</em>' map.
     * @see bip2.ujf.verimag.bip.property.PropertyPackage#getProperties_Properties()
     * @model mapType="bip2.ujf.verimag.bip.property.StringToPropertyMapEntry&lt;org.eclipse.emf.ecore.EString, bip2.ujf.verimag.bip.property.Property&gt;"
     * @generated
     */
    EMap<String, Property> getProperties();

} // Properties
