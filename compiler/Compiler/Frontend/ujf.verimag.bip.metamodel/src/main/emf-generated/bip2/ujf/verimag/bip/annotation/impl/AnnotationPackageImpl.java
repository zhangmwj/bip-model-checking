/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 * 
 * This software is a computer program whose purpose is to generate
 * executable code from BIP models.
 * 
 * This software is governed by the CeCILL-B license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-B
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security.
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-B license and that you accept its terms.
 */

package bip2.ujf.verimag.bip.annotation.impl;

import bip2.Bip2Package;
import bip2.impl.Bip2PackageImpl;
import bip2.ujf.UjfPackage;
import bip2.ujf.impl.UjfPackageImpl;
import bip2.ujf.verimag.VerimagPackage;
import bip2.ujf.verimag.bip.BipPackage;
import bip2.ujf.verimag.bip.actionlang.ActionlangPackage;

import bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl;

import bip2.ujf.verimag.bip.annotation.AnnotatedElement;
import bip2.ujf.verimag.bip.annotation.AnnotationFactory;
import bip2.ujf.verimag.bip.annotation.AnnotationPackage;
import bip2.ujf.verimag.bip.annotation.BipAnnotation;

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
public class AnnotationPackageImpl extends EPackageImpl
        implements AnnotationPackage {
    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass annotatedElementEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass bipAnnotationEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass stringToAnnotationMapEntryEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass stringToStringMapEntryEClass = null;

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
     * @see bip2.ujf.verimag.bip.annotation.AnnotationPackage#eNS_URI
     * @see #init()
     * @generated
     */
    private AnnotationPackageImpl() {
        super(eNS_URI, AnnotationFactory.eINSTANCE);
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
     * <p>This method is used to initialize {@link AnnotationPackage#eINSTANCE} when that field is accessed.
     * Clients should not invoke it directly. Instead, they should simply access that field to obtain the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #eNS_URI
     * @see #createPackageContents()
     * @see #initializePackageContents()
     * @generated
     */
    public static AnnotationPackage init() {
        if (isInited)
            return (AnnotationPackage) EPackage.Registry.INSTANCE
                    .getEPackage(AnnotationPackage.eNS_URI);

        // Obtain or create and register package
        Object registeredAnnotationPackage = EPackage.Registry.INSTANCE
                .get(eNS_URI);
        AnnotationPackageImpl theAnnotationPackage = registeredAnnotationPackage instanceof AnnotationPackageImpl
                ? (AnnotationPackageImpl) registeredAnnotationPackage
                : new AnnotationPackageImpl();

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
        theAnnotationPackage.createPackageContents();
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
        theInvariantPackage.createPackageContents();
        theTimePackage.createPackageContents();

        // Initialize created meta-data
        theAnnotationPackage.initializePackageContents();
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
        theInvariantPackage.initializePackageContents();
        theTimePackage.initializePackageContents();

        // Mark meta-data to indicate it can't be changed
        theAnnotationPackage.freeze();

        // Update the registry and return the package
        EPackage.Registry.INSTANCE.put(AnnotationPackage.eNS_URI,
                theAnnotationPackage);
        return theAnnotationPackage;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getAnnotatedElement() {
        return annotatedElementEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getAnnotatedElement_BipAnnotations() {
        return (EReference) annotatedElementEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getBipAnnotation() {
        return bipAnnotationEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getBipAnnotation_Name() {
        return (EAttribute) bipAnnotationEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getBipAnnotation_Parameters() {
        return (EReference) bipAnnotationEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getStringToAnnotationMapEntry() {
        return stringToAnnotationMapEntryEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getStringToAnnotationMapEntry_Key() {
        return (EAttribute) stringToAnnotationMapEntryEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getStringToAnnotationMapEntry_Value() {
        return (EReference) stringToAnnotationMapEntryEClass
                .getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getStringToStringMapEntry() {
        return stringToStringMapEntryEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getStringToStringMapEntry_Key() {
        return (EAttribute) stringToStringMapEntryEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getStringToStringMapEntry_Value() {
        return (EAttribute) stringToStringMapEntryEClass
                .getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public AnnotationFactory getAnnotationFactory() {
        return (AnnotationFactory) getEFactoryInstance();
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
        annotatedElementEClass = createEClass(ANNOTATED_ELEMENT);
        createEReference(annotatedElementEClass,
                ANNOTATED_ELEMENT__BIP_ANNOTATIONS);

        bipAnnotationEClass = createEClass(BIP_ANNOTATION);
        createEAttribute(bipAnnotationEClass, BIP_ANNOTATION__NAME);
        createEReference(bipAnnotationEClass, BIP_ANNOTATION__PARAMETERS);

        stringToAnnotationMapEntryEClass = createEClass(
                STRING_TO_ANNOTATION_MAP_ENTRY);
        createEAttribute(stringToAnnotationMapEntryEClass,
                STRING_TO_ANNOTATION_MAP_ENTRY__KEY);
        createEReference(stringToAnnotationMapEntryEClass,
                STRING_TO_ANNOTATION_MAP_ENTRY__VALUE);

        stringToStringMapEntryEClass = createEClass(STRING_TO_STRING_MAP_ENTRY);
        createEAttribute(stringToStringMapEntryEClass,
                STRING_TO_STRING_MAP_ENTRY__KEY);
        createEAttribute(stringToStringMapEntryEClass,
                STRING_TO_STRING_MAP_ENTRY__VALUE);
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

        // Create type parameters

        // Set bounds for type parameters

        // Add supertypes to classes

        // Initialize classes and features; add operations and parameters
        initEClass(annotatedElementEClass, AnnotatedElement.class,
                "AnnotatedElement", IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEReference(getAnnotatedElement_BipAnnotations(),
                this.getStringToAnnotationMapEntry(), null, "bipAnnotations",
                null, 0, -1, AnnotatedElement.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(bipAnnotationEClass, BipAnnotation.class, "BipAnnotation",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getBipAnnotation_Name(), ecorePackage.getEString(),
                "name", null, 1, 1, BipAnnotation.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE,
                !IS_DERIVED, IS_ORDERED);
        initEReference(getBipAnnotation_Parameters(),
                this.getStringToStringMapEntry(), null, "parameters", null, 0,
                -1, BipAnnotation.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(stringToAnnotationMapEntryEClass, Map.Entry.class,
                "StringToAnnotationMapEntry", !IS_ABSTRACT, !IS_INTERFACE,
                !IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getStringToAnnotationMapEntry_Key(),
                ecorePackage.getEString(), "key", null, 1, 1, Map.Entry.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE,
                !IS_ID, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getStringToAnnotationMapEntry_Value(),
                this.getBipAnnotation(), null, "value", null, 1, 1,
                Map.Entry.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE,
                IS_COMPOSITE, !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE,
                !IS_DERIVED, IS_ORDERED);

        initEClass(stringToStringMapEntryEClass, Map.Entry.class,
                "StringToStringMapEntry", !IS_ABSTRACT, !IS_INTERFACE,
                !IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getStringToStringMapEntry_Key(),
                ecorePackage.getEString(), "key", null, 1, 1, Map.Entry.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE,
                !IS_ID, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getStringToStringMapEntry_Value(),
                ecorePackage.getEString(), "value", null, 1, 1, Map.Entry.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE,
                !IS_ID, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
    }

} //AnnotationPackageImpl
