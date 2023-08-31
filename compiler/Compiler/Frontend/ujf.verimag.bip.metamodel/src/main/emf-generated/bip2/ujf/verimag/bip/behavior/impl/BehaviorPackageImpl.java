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

package bip2.ujf.verimag.bip.behavior.impl;

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
import bip2.ujf.verimag.bip.behavior.BehaviorFactory;
import bip2.ujf.verimag.bip.behavior.BehaviorPackage;
import bip2.ujf.verimag.bip.behavior.InternalTransition;
import bip2.ujf.verimag.bip.behavior.PetriNet;
import bip2.ujf.verimag.bip.behavior.State;
import bip2.ujf.verimag.bip.behavior.Transition;

import bip2.ujf.verimag.bip.behavior.util.BehaviorValidator;
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
import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EOperation;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EReference;

import org.eclipse.emf.ecore.EValidator;
import org.eclipse.emf.ecore.impl.EPackageImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Package</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class BehaviorPackageImpl extends EPackageImpl
        implements BehaviorPackage {
    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass petriNetEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass stateEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass transitionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass internalTransitionEClass = null;

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
     * @see bip2.ujf.verimag.bip.behavior.BehaviorPackage#eNS_URI
     * @see #init()
     * @generated
     */
    private BehaviorPackageImpl() {
        super(eNS_URI, BehaviorFactory.eINSTANCE);
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
     * <p>This method is used to initialize {@link BehaviorPackage#eINSTANCE} when that field is accessed.
     * Clients should not invoke it directly. Instead, they should simply access that field to obtain the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #eNS_URI
     * @see #createPackageContents()
     * @see #initializePackageContents()
     * @generated
     */
    public static BehaviorPackage init() {
        if (isInited)
            return (BehaviorPackage) EPackage.Registry.INSTANCE
                    .getEPackage(BehaviorPackage.eNS_URI);

        // Obtain or create and register package
        Object registeredBehaviorPackage = EPackage.Registry.INSTANCE
                .get(eNS_URI);
        BehaviorPackageImpl theBehaviorPackage = registeredBehaviorPackage instanceof BehaviorPackageImpl
                ? (BehaviorPackageImpl) registeredBehaviorPackage
                : new BehaviorPackageImpl();

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
        theBehaviorPackage.createPackageContents();
        theBip2Package.createPackageContents();
        theUjfPackage.createPackageContents();
        theVerimagPackage.createPackageContents();
        theBipPackage.createPackageContents();
        theTypesPackage.createPackageContents();
        theDataPackage.createPackageContents();
        thePortPackage.createPackageContents();
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
        theBehaviorPackage.initializePackageContents();
        theBip2Package.initializePackageContents();
        theUjfPackage.initializePackageContents();
        theVerimagPackage.initializePackageContents();
        theBipPackage.initializePackageContents();
        theTypesPackage.initializePackageContents();
        theDataPackage.initializePackageContents();
        thePortPackage.initializePackageContents();
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

        // Register package validator
        EValidator.Registry.INSTANCE.put(theBehaviorPackage,
                new EValidator.Descriptor() {
                    @Override
                    public EValidator getEValidator() {
                        return BehaviorValidator.INSTANCE;
                    }
                });

        // Mark meta-data to indicate it can't be changed
        theBehaviorPackage.freeze();

        // Update the registry and return the package
        EPackage.Registry.INSTANCE.put(BehaviorPackage.eNS_URI,
                theBehaviorPackage);
        return theBehaviorPackage;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getPetriNet() {
        return petriNetEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getPetriNet_States() {
        return (EReference) petriNetEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getPetriNet_InitStates() {
        return (EReference) petriNetEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getPetriNet_Transitions() {
        return (EReference) petriNetEClass.getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getPetriNet_InitialActions() {
        return (EReference) petriNetEClass.getEStructuralFeatures().get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getPetriNet_InitialResume() {
        return (EReference) petriNetEClass.getEStructuralFeatures().get(4);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getState() {
        return stateEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getState_Name() {
        return (EAttribute) stateEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getTransition() {
        return transitionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getTransition_Sources() {
        return (EReference) transitionEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getTransition_Destinations() {
        return (EReference) transitionEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getTransition_TriggerPort() {
        return (EReference) transitionEClass.getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getTransition_Actions() {
        return (EReference) transitionEClass.getEStructuralFeatures().get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getInternalTransition() {
        return internalTransitionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public BehaviorFactory getBehaviorFactory() {
        return (BehaviorFactory) getEFactoryInstance();
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
        petriNetEClass = createEClass(PETRI_NET);
        createEReference(petriNetEClass, PETRI_NET__STATES);
        createEReference(petriNetEClass, PETRI_NET__INIT_STATES);
        createEReference(petriNetEClass, PETRI_NET__TRANSITIONS);
        createEReference(petriNetEClass, PETRI_NET__INITIAL_ACTIONS);
        createEReference(petriNetEClass, PETRI_NET__INITIAL_RESUME);

        stateEClass = createEClass(STATE);
        createEAttribute(stateEClass, STATE__NAME);

        transitionEClass = createEClass(TRANSITION);
        createEReference(transitionEClass, TRANSITION__SOURCES);
        createEReference(transitionEClass, TRANSITION__DESTINATIONS);
        createEReference(transitionEClass, TRANSITION__TRIGGER_PORT);
        createEReference(transitionEClass, TRANSITION__ACTIONS);

        internalTransitionEClass = createEClass(INTERNAL_TRANSITION);
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
        TimePackage theTimePackage = (TimePackage) EPackage.Registry.INSTANCE
                .getEPackage(TimePackage.eNS_URI);
        DataPackage theDataPackage = (DataPackage) EPackage.Registry.INSTANCE
                .getEPackage(DataPackage.eNS_URI);
        AnnotationPackage theAnnotationPackage = (AnnotationPackage) EPackage.Registry.INSTANCE
                .getEPackage(AnnotationPackage.eNS_URI);
        AtomPackage theAtomPackage = (AtomPackage) EPackage.Registry.INSTANCE
                .getEPackage(AtomPackage.eNS_URI);

        // Create type parameters

        // Set bounds for type parameters

        // Add supertypes to classes
        transitionEClass.getESuperTypes()
                .add(theAnnotationPackage.getAnnotatedElement());
        transitionEClass.getESuperTypes().add(theTimePackage.getGuarded());
        transitionEClass.getESuperTypes().add(theTimePackage.getResumed());
        transitionEClass.getESuperTypes()
                .add(theTimePackage.getUrgentElement());
        internalTransitionEClass.getESuperTypes().add(this.getTransition());
        internalTransitionEClass.getESuperTypes()
                .add(theTimePackage.getGuardedUntimed());

        // Initialize classes and features; add operations and parameters
        initEClass(petriNetEClass, PetriNet.class, "PetriNet", !IS_ABSTRACT,
                !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getPetriNet_States(), this.getState(), null, "states",
                null, 1, -1, PetriNet.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getPetriNet_InitStates(), this.getState(), null,
                "initStates", null, 1, -1, PetriNet.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getPetriNet_Transitions(), this.getTransition(), null,
                "transitions", null, 0, -1, PetriNet.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getPetriNet_InitialActions(),
                theActionlangPackage.getExpression(), null, "initialActions",
                null, 0, -1, PetriNet.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getPetriNet_InitialResume(), theTimePackage.getResume(),
                null, "initialResume", null, 0, 1, PetriNet.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        EOperation op = addEOperation(petriNetEClass, this.getState(),
                "getState", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(petriNetEClass, ecorePackage.getEBooleanObject(),
                "isOneSafe", 1, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, this.getState(), "state", 1, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(petriNetEClass, ecorePackage.getEBooleanObject(),
                "mayBeOneSafe", 1, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, this.getState(), "state", 1, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(petriNetEClass, ecorePackage.getEBooleanObject(),
                "isCoverable", 1, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, this.getState(), "states", 0, -1, !IS_UNIQUE,
                !IS_ORDERED);

        op = addEOperation(petriNetEClass, ecorePackage.getEBooleanObject(),
                "mayBeCoverable", 1, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, this.getState(), "states", 0, -1, !IS_UNIQUE,
                !IS_ORDERED);

        addEOperation(petriNetEClass, theActionlangPackage.getExpression(),
                "getUninitializedVariables", 0, -1, IS_UNIQUE, IS_ORDERED);

        addEOperation(petriNetEClass, theDataPackage.getDataDeclaration(),
                "getUninitializedExportedVariables", 0, -1, IS_UNIQUE,
                !IS_ORDERED);

        op = addEOperation(petriNetEClass, theDataPackage.getDataDeclaration(),
                "getUninitializedExportedVariables", 0, -1, IS_UNIQUE,
                !IS_ORDERED);
        addEParameter(op, this.getTransition(), "transition", 1, 1, IS_UNIQUE,
                IS_ORDERED);

        initEClass(stateEClass, State.class, "State", !IS_ABSTRACT,
                !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getState_Name(), ecorePackage.getEString(), "name", null,
                1, 1, State.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE,
                !IS_UNSETTABLE, IS_ID, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(transitionEClass, Transition.class, "Transition",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getTransition_Sources(), this.getState(), null,
                "sources", null, 1, -1, Transition.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getTransition_Destinations(), this.getState(), null,
                "destinations", null, 1, -1, Transition.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getTransition_TriggerPort(),
                theAtomPackage.getAtomInternalExternalPortDeclaration(), null,
                "triggerPort", null, 0, 1, Transition.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getTransition_Actions(),
                theActionlangPackage.getExpression(), null, "actions", null, 0,
                -1, Transition.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(internalTransitionEClass, InternalTransition.class,
                "InternalTransition", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);

        // Create annotations
        // http://www.eclipse.org/emf/2002/Ecore
        createEcoreAnnotations();
    }

    /**
     * Initializes the annotations for <b>http://www.eclipse.org/emf/2002/Ecore</b>.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected void createEcoreAnnotations() {
        String source = "http://www.eclipse.org/emf/2002/Ecore";
        addAnnotation(petriNetEClass, source, new String[] { "constraints",
                "checkIllFormed checkUninitializedVariablesOfPetriNet checkUninitializedVariablesExportedByPortOfAtom checkUninitializedVariablesExportedAtom" });
        addAnnotation(transitionEClass, source, new String[] { "constraints",
                "hasNoVariableModifiedBetweenProvidedAndDo eagerHasNoClocksInGuard" });
        addAnnotation(internalTransitionEClass, source, new String[] {
                "constraints", "internalTransitionHasNoTriggerPort" });
    }

} //BehaviorPackageImpl
