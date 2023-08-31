/**
 */
package bip2.ujf.verimag.bip.property.impl;

import bip2.Bip2Package;

import bip2.impl.Bip2PackageImpl;

import bip2.ujf.UjfPackage;

import bip2.ujf.impl.UjfPackageImpl;

import bip2.ujf.verimag.VerimagPackage;

import bip2.ujf.verimag.bip.BipPackage;

import bip2.ujf.verimag.bip.actionlang.ActionlangPackage;

import bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl;

import bip2.ujf.verimag.bip.annotation.AnnotationPackage;

import bip2.ujf.verimag.bip.annotation.impl.AnnotationPackageImpl;

import bip2.ujf.verimag.bip.behavior.BehaviorPackage;

import bip2.ujf.verimag.bip.behavior.impl.BehaviorPackageImpl;

import bip2.ujf.verimag.bip.component.ComponentPackage;

import bip2.ujf.verimag.bip.component.atom.AtomPackage;

import bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl;

import bip2.ujf.verimag.bip.component.compound.CompoundPackage;

import bip2.ujf.verimag.bip.component.compound.impl.CompoundPackageImpl;

import bip2.ujf.verimag.bip.component.impl.ComponentPackageImpl;

import bip2.ujf.verimag.bip.connector.ConnectorPackage;

import bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl;

import bip2.ujf.verimag.bip.data.DataPackage;

import bip2.ujf.verimag.bip.data.impl.DataPackageImpl;

import bip2.ujf.verimag.bip.impl.BipPackageImpl;

import bip2.ujf.verimag.bip.instance.InstancePackage;

import bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl;

import bip2.ujf.verimag.bip.invariant.InvariantPackage;

import bip2.ujf.verimag.bip.invariant.impl.InvariantPackageImpl;

import bip2.ujf.verimag.bip.packaging.PackagingPackage;

import bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl;

import bip2.ujf.verimag.bip.port.PortPackage;

import bip2.ujf.verimag.bip.port.impl.PortPackageImpl;

import bip2.ujf.verimag.bip.priority.PriorityPackage;

import bip2.ujf.verimag.bip.priority.impl.PriorityPackageImpl;

import bip2.ujf.verimag.bip.property.Properties;
import bip2.ujf.verimag.bip.property.Property;
import bip2.ujf.verimag.bip.property.PropertyFactory;
import bip2.ujf.verimag.bip.property.PropertyPackage;

import bip2.ujf.verimag.bip.time.TimePackage;

import bip2.ujf.verimag.bip.time.impl.TimePackageImpl;

import bip2.ujf.verimag.bip.types.TypesPackage;

import bip2.ujf.verimag.bip.types.impl.TypesPackageImpl;

import bip2.ujf.verimag.impl.VerimagPackageImpl;

import java.util.Map;

import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EReference;

import org.eclipse.emf.ecore.impl.EPackageImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Package</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class PropertyPackageImpl extends EPackageImpl
        implements PropertyPackage {
    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass propertyEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass propertiesEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass stringToPropertyMapEntryEClass = null;

    /**
     * Creates an instance of the model <b>Package</b>, registered with
     * {@link org.eclipse.emf.ecore.EPackage.Registry EPackage.Registry} by the package
     * package URI value.
     * <p>Note: the correct way to create the package is via the static
     * factory method {@link #init init()}, which also performs
     * initialization of the package, or returns the registered package,
     * if one already exists.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.ecore.EPackage.Registry
     * @see bip2.ujf.verimag.bip.property.PropertyPackage#eNS_URI
     * @see #init()
     * @generated
     */
    private PropertyPackageImpl() {
        super(eNS_URI, PropertyFactory.eINSTANCE);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private static boolean isInited = false;

    /**
     * Creates, registers, and initializes the <b>Package</b> for this model, and for any others upon which it depends.
     *
     * <p>This method is used to initialize {@link PropertyPackage#eINSTANCE} when that field is accessed.
     * Clients should not invoke it directly. Instead, they should simply access that field to obtain the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #eNS_URI
     * @see #createPackageContents()
     * @see #initializePackageContents()
     * @generated
     */
    public static PropertyPackage init() {
        if (isInited)
            return (PropertyPackage) EPackage.Registry.INSTANCE
                    .getEPackage(PropertyPackage.eNS_URI);

        // Obtain or create and register package
        Object registeredPropertyPackage = EPackage.Registry.INSTANCE
                .get(eNS_URI);
        PropertyPackageImpl thePropertyPackage = registeredPropertyPackage instanceof PropertyPackageImpl
                ? (PropertyPackageImpl) registeredPropertyPackage
                : new PropertyPackageImpl();

        isInited = true;

        // Obtain or create and register interdependencies
        Object registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(Bip2Package.eNS_URI);
        Bip2PackageImpl theBip2Package = (Bip2PackageImpl) (registeredPackage instanceof Bip2PackageImpl
                ? registeredPackage
                : Bip2Package.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(UjfPackage.eNS_URI);
        UjfPackageImpl theUjfPackage = (UjfPackageImpl) (registeredPackage instanceof UjfPackageImpl
                ? registeredPackage
                : UjfPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(VerimagPackage.eNS_URI);
        VerimagPackageImpl theVerimagPackage = (VerimagPackageImpl) (registeredPackage instanceof VerimagPackageImpl
                ? registeredPackage
                : VerimagPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(BipPackage.eNS_URI);
        BipPackageImpl theBipPackage = (BipPackageImpl) (registeredPackage instanceof BipPackageImpl
                ? registeredPackage
                : BipPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(TypesPackage.eNS_URI);
        TypesPackageImpl theTypesPackage = (TypesPackageImpl) (registeredPackage instanceof TypesPackageImpl
                ? registeredPackage
                : TypesPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(DataPackage.eNS_URI);
        DataPackageImpl theDataPackage = (DataPackageImpl) (registeredPackage instanceof DataPackageImpl
                ? registeredPackage
                : DataPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(PortPackage.eNS_URI);
        PortPackageImpl thePortPackage = (PortPackageImpl) (registeredPackage instanceof PortPackageImpl
                ? registeredPackage
                : PortPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(BehaviorPackage.eNS_URI);
        BehaviorPackageImpl theBehaviorPackage = (BehaviorPackageImpl) (registeredPackage instanceof BehaviorPackageImpl
                ? registeredPackage
                : BehaviorPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(PriorityPackage.eNS_URI);
        PriorityPackageImpl thePriorityPackage = (PriorityPackageImpl) (registeredPackage instanceof PriorityPackageImpl
                ? registeredPackage
                : PriorityPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(ConnectorPackage.eNS_URI);
        ConnectorPackageImpl theConnectorPackage = (ConnectorPackageImpl) (registeredPackage instanceof ConnectorPackageImpl
                ? registeredPackage
                : ConnectorPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(ComponentPackage.eNS_URI);
        ComponentPackageImpl theComponentPackage = (ComponentPackageImpl) (registeredPackage instanceof ComponentPackageImpl
                ? registeredPackage
                : ComponentPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(AtomPackage.eNS_URI);
        AtomPackageImpl theAtomPackage = (AtomPackageImpl) (registeredPackage instanceof AtomPackageImpl
                ? registeredPackage
                : AtomPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(CompoundPackage.eNS_URI);
        CompoundPackageImpl theCompoundPackage = (CompoundPackageImpl) (registeredPackage instanceof CompoundPackageImpl
                ? registeredPackage
                : CompoundPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(PackagingPackage.eNS_URI);
        PackagingPackageImpl thePackagingPackage = (PackagingPackageImpl) (registeredPackage instanceof PackagingPackageImpl
                ? registeredPackage
                : PackagingPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(ActionlangPackage.eNS_URI);
        ActionlangPackageImpl theActionlangPackage = (ActionlangPackageImpl) (registeredPackage instanceof ActionlangPackageImpl
                ? registeredPackage
                : ActionlangPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(InstancePackage.eNS_URI);
        InstancePackageImpl theInstancePackage = (InstancePackageImpl) (registeredPackage instanceof InstancePackageImpl
                ? registeredPackage
                : InstancePackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(AnnotationPackage.eNS_URI);
        AnnotationPackageImpl theAnnotationPackage = (AnnotationPackageImpl) (registeredPackage instanceof AnnotationPackageImpl
                ? registeredPackage
                : AnnotationPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(InvariantPackage.eNS_URI);
        InvariantPackageImpl theInvariantPackage = (InvariantPackageImpl) (registeredPackage instanceof InvariantPackageImpl
                ? registeredPackage
                : InvariantPackage.eINSTANCE);
        registeredPackage = EPackage.Registry.INSTANCE
                .getEPackage(TimePackage.eNS_URI);
        TimePackageImpl theTimePackage = (TimePackageImpl) (registeredPackage instanceof TimePackageImpl
                ? registeredPackage
                : TimePackage.eINSTANCE);

        // Create package meta-data objects
        thePropertyPackage.createPackageContents();
        theBip2Package.createPackageContents();
        theUjfPackage.createPackageContents();
        theVerimagPackage.createPackageContents();
        theBipPackage.createPackageContents();
        theTypesPackage.createPackageContents();
        theDataPackage.createPackageContents();
        thePortPackage.createPackageContents();
        theBehaviorPackage.createPackageContents();
        thePriorityPackage.createPackageContents();
        theConnectorPackage.createPackageContents();
        theComponentPackage.createPackageContents();
        theAtomPackage.createPackageContents();
        theCompoundPackage.createPackageContents();
        thePackagingPackage.createPackageContents();
        theActionlangPackage.createPackageContents();
        theInstancePackage.createPackageContents();
        theAnnotationPackage.createPackageContents();
        theInvariantPackage.createPackageContents();
        theTimePackage.createPackageContents();

        // Initialize created meta-data
        thePropertyPackage.initializePackageContents();
        theBip2Package.initializePackageContents();
        theUjfPackage.initializePackageContents();
        theVerimagPackage.initializePackageContents();
        theBipPackage.initializePackageContents();
        theTypesPackage.initializePackageContents();
        theDataPackage.initializePackageContents();
        thePortPackage.initializePackageContents();
        theBehaviorPackage.initializePackageContents();
        thePriorityPackage.initializePackageContents();
        theConnectorPackage.initializePackageContents();
        theComponentPackage.initializePackageContents();
        theAtomPackage.initializePackageContents();
        theCompoundPackage.initializePackageContents();
        thePackagingPackage.initializePackageContents();
        theActionlangPackage.initializePackageContents();
        theInstancePackage.initializePackageContents();
        theAnnotationPackage.initializePackageContents();
        theInvariantPackage.initializePackageContents();
        theTimePackage.initializePackageContents();

        // Mark meta-data to indicate it can't be changed
        thePropertyPackage.freeze();

        // Update the registry and return the package
        EPackage.Registry.INSTANCE.put(PropertyPackage.eNS_URI,
                thePropertyPackage);
        return thePropertyPackage;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getProperty() {
        return propertyEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getProperty_Reachability() {
        return (EAttribute) propertyEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getProperty_Expression() {
        return (EReference) propertyEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getProperties() {
        return propertiesEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getProperties_Properties() {
        return (EReference) propertiesEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getStringToPropertyMapEntry() {
        return stringToPropertyMapEntryEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getStringToPropertyMapEntry_Key() {
        return (EAttribute) stringToPropertyMapEntryEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getStringToPropertyMapEntry_Value() {
        return (EReference) stringToPropertyMapEntryEClass
                .getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public PropertyFactory getPropertyFactory() {
        return (PropertyFactory) getEFactoryInstance();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private boolean isCreated = false;

    /**
     * Creates the meta-model objects for the package.  This method is
     * guarded to have no affect on any invocation but its first.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void createPackageContents() {
        if (isCreated)
            return;
        isCreated = true;

        // Create classes and their features
        propertyEClass = createEClass(PROPERTY);
        createEAttribute(propertyEClass, PROPERTY__REACHABILITY);
        createEReference(propertyEClass, PROPERTY__EXPRESSION);

        propertiesEClass = createEClass(PROPERTIES);
        createEReference(propertiesEClass, PROPERTIES__PROPERTIES);

        stringToPropertyMapEntryEClass = createEClass(
                STRING_TO_PROPERTY_MAP_ENTRY);
        createEAttribute(stringToPropertyMapEntryEClass,
                STRING_TO_PROPERTY_MAP_ENTRY__KEY);
        createEReference(stringToPropertyMapEntryEClass,
                STRING_TO_PROPERTY_MAP_ENTRY__VALUE);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private boolean isInitialized = false;

    /**
     * Complete the initialization of the package and its meta-model.  This
     * method is guarded to have no affect on any invocation but its first.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void initializePackageContents() {
        if (isInitialized)
            return;
        isInitialized = true;

        // Initialize package
        setName(eNAME);
        setNsPrefix(eNS_PREFIX);
        setNsURI(eNS_URI);

        // Obtain other dependent packages
        ActionlangPackage theActionlangPackage = (ActionlangPackage) EPackage.Registry.INSTANCE
                .getEPackage(ActionlangPackage.eNS_URI);

        // Create type parameters

        // Set bounds for type parameters

        // Add supertypes to classes

        // Initialize classes and features; add operations and parameters
        initEClass(propertyEClass, Property.class, "Property", !IS_ABSTRACT,
                !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getProperty_Reachability(), ecorePackage.getEBoolean(),
                "reachability", "true", 1, 1, Property.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE,
                !IS_DERIVED, IS_ORDERED);
        initEReference(getProperty_Expression(),
                theActionlangPackage.getValuedExpression(), null, "expression",
                null, 1, 1, Property.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(propertiesEClass, Properties.class, "Properties",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getProperties_Properties(),
                this.getStringToPropertyMapEntry(), null, "properties", null, 0,
                -1, Properties.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(stringToPropertyMapEntryEClass, Map.Entry.class,
                "StringToPropertyMapEntry", !IS_ABSTRACT, !IS_INTERFACE,
                !IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getStringToPropertyMapEntry_Key(),
                ecorePackage.getEString(), "key", null, 1, 1, Map.Entry.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE,
                !IS_ID, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getStringToPropertyMapEntry_Value(), this.getProperty(),
                null, "value", null, 1, 1, Map.Entry.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
    }

} //PropertyPackageImpl
