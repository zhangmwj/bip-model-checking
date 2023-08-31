/**
 */
package bip2.ujf.verimag.bip.property.impl;

import bip2.ujf.verimag.bip.property.*;

import java.util.Map;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.impl.EFactoryImpl;

import org.eclipse.emf.ecore.plugin.EcorePlugin;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Factory</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class PropertyFactoryImpl extends EFactoryImpl
        implements PropertyFactory {
    /**
     * Creates the default factory implementation.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static PropertyFactory init() {
        try {
            PropertyFactory thePropertyFactory = (PropertyFactory) EPackage.Registry.INSTANCE
                    .getEFactory(PropertyPackage.eNS_URI);
            if (thePropertyFactory != null) {
                return thePropertyFactory;
            }
        } catch (Exception exception) {
            EcorePlugin.INSTANCE.log(exception);
        }
        return new PropertyFactoryImpl();
    }

    /**
     * Creates an instance of the factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PropertyFactoryImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EObject create(EClass eClass) {
        switch (eClass.getClassifierID()) {
        case PropertyPackage.PROPERTY:
            return (EObject) createProperty();
        case PropertyPackage.PROPERTIES:
            return (EObject) createProperties();
        case PropertyPackage.STRING_TO_PROPERTY_MAP_ENTRY:
            return (EObject) createStringToPropertyMapEntry();
        default:
            throw new IllegalArgumentException("The class '" + eClass.getName()
                    + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Property createProperty() {
        PropertyImpl property = new PropertyImpl();
        return property;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Properties createProperties() {
        PropertiesImpl properties = new PropertiesImpl();
        return properties;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Map.Entry<String, Property> createStringToPropertyMapEntry() {
        StringToPropertyMapEntryImpl stringToPropertyMapEntry = new StringToPropertyMapEntryImpl();
        return stringToPropertyMapEntry;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public PropertyPackage getPropertyPackage() {
        return (PropertyPackage) getEPackage();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @deprecated
     * @generated
     */
    @Deprecated
    public static PropertyPackage getPackage() {
        return PropertyPackage.eINSTANCE;
    }

} //PropertyFactoryImpl
