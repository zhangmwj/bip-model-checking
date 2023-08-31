/**
 */
package bip2.ujf.verimag.bip.property;

import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EReference;

/**
 * <!-- begin-user-doc -->
 * The <b>Package</b> for the model.
 * It contains accessors for the meta objects to represent
 * <ul>
 *   <li>each class,</li>
 *   <li>each feature of each class,</li>
 *   <li>each enum,</li>
 *   <li>and each data type</li>
 * </ul>
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.property.PropertyFactory
 * @model kind="package"
 * @generated
 */
public interface PropertyPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "property";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/property/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.property";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    PropertyPackage eINSTANCE = bip2.ujf.verimag.bip.property.impl.PropertyPackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.property.impl.PropertyImpl <em>Property</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.property.impl.PropertyImpl
     * @see bip2.ujf.verimag.bip.property.impl.PropertyPackageImpl#getProperty()
     * @generated
     */
    int PROPERTY = 0;

    /**
     * The feature id for the '<em><b>Reachability</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROPERTY__REACHABILITY = 0;

    /**
     * The feature id for the '<em><b>Expression</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROPERTY__EXPRESSION = 1;

    /**
     * The number of structural features of the '<em>Property</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROPERTY_FEATURE_COUNT = 2;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.property.impl.PropertiesImpl <em>Properties</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.property.impl.PropertiesImpl
     * @see bip2.ujf.verimag.bip.property.impl.PropertyPackageImpl#getProperties()
     * @generated
     */
    int PROPERTIES = 1;

    /**
     * The feature id for the '<em><b>Properties</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROPERTIES__PROPERTIES = 0;

    /**
     * The number of structural features of the '<em>Properties</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROPERTIES_FEATURE_COUNT = 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.property.impl.StringToPropertyMapEntryImpl <em>String To Property Map Entry</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.property.impl.StringToPropertyMapEntryImpl
     * @see bip2.ujf.verimag.bip.property.impl.PropertyPackageImpl#getStringToPropertyMapEntry()
     * @generated
     */
    int STRING_TO_PROPERTY_MAP_ENTRY = 2;

    /**
     * The feature id for the '<em><b>Key</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STRING_TO_PROPERTY_MAP_ENTRY__KEY = 0;

    /**
     * The feature id for the '<em><b>Value</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STRING_TO_PROPERTY_MAP_ENTRY__VALUE = 1;

    /**
     * The number of structural features of the '<em>String To Property Map Entry</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STRING_TO_PROPERTY_MAP_ENTRY_FEATURE_COUNT = 2;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.property.Property <em>Property</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Property</em>'.
     * @see bip2.ujf.verimag.bip.property.Property
     * @generated
     */
    EClass getProperty();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.property.Property#isReachability <em>Reachability</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Reachability</em>'.
     * @see bip2.ujf.verimag.bip.property.Property#isReachability()
     * @see #getProperty()
     * @generated
     */
    EAttribute getProperty_Reachability();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.property.Property#getExpression <em>Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Expression</em>'.
     * @see bip2.ujf.verimag.bip.property.Property#getExpression()
     * @see #getProperty()
     * @generated
     */
    EReference getProperty_Expression();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.property.Properties <em>Properties</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Properties</em>'.
     * @see bip2.ujf.verimag.bip.property.Properties
     * @generated
     */
    EClass getProperties();

    /**
     * Returns the meta object for the map '{@link bip2.ujf.verimag.bip.property.Properties#getProperties <em>Properties</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the map '<em>Properties</em>'.
     * @see bip2.ujf.verimag.bip.property.Properties#getProperties()
     * @see #getProperties()
     * @generated
     */
    EReference getProperties_Properties();

    /**
     * Returns the meta object for class '{@link java.util.Map.Entry <em>String To Property Map Entry</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>String To Property Map Entry</em>'.
     * @see java.util.Map.Entry
     * @model keyDataType="org.eclipse.emf.ecore.EString" keyRequired="true"
     *        valueType="bip2.ujf.verimag.bip.property.Property" valueContainment="true" valueRequired="true"
     * @generated
     */
    EClass getStringToPropertyMapEntry();

    /**
     * Returns the meta object for the attribute '{@link java.util.Map.Entry <em>Key</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Key</em>'.
     * @see java.util.Map.Entry
     * @see #getStringToPropertyMapEntry()
     * @generated
     */
    EAttribute getStringToPropertyMapEntry_Key();

    /**
     * Returns the meta object for the containment reference '{@link java.util.Map.Entry <em>Value</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Value</em>'.
     * @see java.util.Map.Entry
     * @see #getStringToPropertyMapEntry()
     * @generated
     */
    EReference getStringToPropertyMapEntry_Value();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    PropertyFactory getPropertyFactory();

    /**
     * <!-- begin-user-doc -->
     * Defines literals for the meta objects that represent
     * <ul>
     *   <li>each class,</li>
     *   <li>each feature of each class,</li>
     *   <li>each enum,</li>
     *   <li>and each data type</li>
     * </ul>
     * <!-- end-user-doc -->
     * @generated
     */
    interface Literals {
        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.property.impl.PropertyImpl <em>Property</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.property.impl.PropertyImpl
         * @see bip2.ujf.verimag.bip.property.impl.PropertyPackageImpl#getProperty()
         * @generated
         */
        EClass PROPERTY = eINSTANCE.getProperty();

        /**
         * The meta object literal for the '<em><b>Reachability</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute PROPERTY__REACHABILITY = eINSTANCE
                .getProperty_Reachability();

        /**
         * The meta object literal for the '<em><b>Expression</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PROPERTY__EXPRESSION = eINSTANCE.getProperty_Expression();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.property.impl.PropertiesImpl <em>Properties</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.property.impl.PropertiesImpl
         * @see bip2.ujf.verimag.bip.property.impl.PropertyPackageImpl#getProperties()
         * @generated
         */
        EClass PROPERTIES = eINSTANCE.getProperties();

        /**
         * The meta object literal for the '<em><b>Properties</b></em>' map feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PROPERTIES__PROPERTIES = eINSTANCE
                .getProperties_Properties();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.property.impl.StringToPropertyMapEntryImpl <em>String To Property Map Entry</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.property.impl.StringToPropertyMapEntryImpl
         * @see bip2.ujf.verimag.bip.property.impl.PropertyPackageImpl#getStringToPropertyMapEntry()
         * @generated
         */
        EClass STRING_TO_PROPERTY_MAP_ENTRY = eINSTANCE
                .getStringToPropertyMapEntry();

        /**
         * The meta object literal for the '<em><b>Key</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute STRING_TO_PROPERTY_MAP_ENTRY__KEY = eINSTANCE
                .getStringToPropertyMapEntry_Key();

        /**
         * The meta object literal for the '<em><b>Value</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference STRING_TO_PROPERTY_MAP_ENTRY__VALUE = eINSTANCE
                .getStringToPropertyMapEntry_Value();

    }

} //PropertyPackage
