/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Anakreontas Mentis
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

package bip2.ujf.verimag.bip.connector.impl;

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

import bip2.ujf.verimag.bip.connector.ConnectorDataDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorExportedPortDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorFactory;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionAction;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionNestedDefinition;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionNestedDefinition;
import bip2.ujf.verimag.bip.connector.ConnectorPackage;
import bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration;

import bip2.ujf.verimag.bip.connector.util.ConnectorValidator;
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
import org.eclipse.emf.ecore.EDataType;
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
public class ConnectorPackageImpl extends EPackageImpl implements
        ConnectorPackage {
    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass connectorDeclarationEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass connectorPortParameterDeclarationEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass connectorExportedPortDeclarationEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass connectorDataDeclarationEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass connectorInteractionActionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass connectorInteractionDefinitionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass connectorInteractionPortReferenceEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass connectorInteractionNestedDefinitionEClass = null;

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
     * @see bip2.ujf.verimag.bip.connector.ConnectorPackage#eNS_URI
     * @see #init()
     * @generated
     */
    private ConnectorPackageImpl() {
        super(eNS_URI, ConnectorFactory.eINSTANCE);
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
     * <p>This method is used to initialize {@link ConnectorPackage#eINSTANCE} when that field is accessed.
     * Clients should not invoke it directly. Instead, they should simply access that field to obtain the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #eNS_URI
     * @see #createPackageContents()
     * @see #initializePackageContents()
     * @generated
     */
    public static ConnectorPackage init() {
        if (isInited)
            return (ConnectorPackage) EPackage.Registry.INSTANCE
                    .getEPackage(ConnectorPackage.eNS_URI);

        // Obtain or create and register package
        ConnectorPackageImpl theConnectorPackage = (ConnectorPackageImpl) (EPackage.Registry.INSTANCE
                .get(eNS_URI) instanceof ConnectorPackageImpl ? EPackage.Registry.INSTANCE
                .get(eNS_URI) : new ConnectorPackageImpl());

        isInited = true;

        // Obtain or create and register interdependencies
        Bip2PackageImpl theBip2Package = (Bip2PackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(Bip2Package.eNS_URI) instanceof Bip2PackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(Bip2Package.eNS_URI) : Bip2Package.eINSTANCE);
        UjfPackageImpl theUjfPackage = (UjfPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(UjfPackage.eNS_URI) instanceof UjfPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(UjfPackage.eNS_URI) : UjfPackage.eINSTANCE);
        VerimagPackageImpl theVerimagPackage = (VerimagPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(VerimagPackage.eNS_URI) instanceof VerimagPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(VerimagPackage.eNS_URI) : VerimagPackage.eINSTANCE);
        BipPackageImpl theBipPackage = (BipPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(BipPackage.eNS_URI) instanceof BipPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(BipPackage.eNS_URI) : BipPackage.eINSTANCE);
        TypesPackageImpl theTypesPackage = (TypesPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(TypesPackage.eNS_URI) instanceof TypesPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(TypesPackage.eNS_URI) : TypesPackage.eINSTANCE);
        DataPackageImpl theDataPackage = (DataPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(DataPackage.eNS_URI) instanceof DataPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(DataPackage.eNS_URI) : DataPackage.eINSTANCE);
        PortPackageImpl thePortPackage = (PortPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(PortPackage.eNS_URI) instanceof PortPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(PortPackage.eNS_URI) : PortPackage.eINSTANCE);
        BehaviorPackageImpl theBehaviorPackage = (BehaviorPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(BehaviorPackage.eNS_URI) instanceof BehaviorPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(BehaviorPackage.eNS_URI)
                : BehaviorPackage.eINSTANCE);
        PriorityPackageImpl thePriorityPackage = (PriorityPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(PriorityPackage.eNS_URI) instanceof PriorityPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(PriorityPackage.eNS_URI)
                : PriorityPackage.eINSTANCE);
        ComponentPackageImpl theComponentPackage = (ComponentPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(ComponentPackage.eNS_URI) instanceof ComponentPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(ComponentPackage.eNS_URI)
                : ComponentPackage.eINSTANCE);
        AtomPackageImpl theAtomPackage = (AtomPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(AtomPackage.eNS_URI) instanceof AtomPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(AtomPackage.eNS_URI) : AtomPackage.eINSTANCE);
        CompoundPackageImpl theCompoundPackage = (CompoundPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(CompoundPackage.eNS_URI) instanceof CompoundPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(CompoundPackage.eNS_URI)
                : CompoundPackage.eINSTANCE);
        PackagingPackageImpl thePackagingPackage = (PackagingPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(PackagingPackage.eNS_URI) instanceof PackagingPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(PackagingPackage.eNS_URI)
                : PackagingPackage.eINSTANCE);
        ActionlangPackageImpl theActionlangPackage = (ActionlangPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(ActionlangPackage.eNS_URI) instanceof ActionlangPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(ActionlangPackage.eNS_URI)
                : ActionlangPackage.eINSTANCE);
        InstancePackageImpl theInstancePackage = (InstancePackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(InstancePackage.eNS_URI) instanceof InstancePackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(InstancePackage.eNS_URI)
                : InstancePackage.eINSTANCE);
        AnnotationPackageImpl theAnnotationPackage = (AnnotationPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(AnnotationPackage.eNS_URI) instanceof AnnotationPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(AnnotationPackage.eNS_URI)
                : AnnotationPackage.eINSTANCE);
        InvariantPackageImpl theInvariantPackage = (InvariantPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(InvariantPackage.eNS_URI) instanceof InvariantPackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(InvariantPackage.eNS_URI)
                : InvariantPackage.eINSTANCE);
        TimePackageImpl theTimePackage = (TimePackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(TimePackage.eNS_URI) instanceof TimePackageImpl ? EPackage.Registry.INSTANCE
                .getEPackage(TimePackage.eNS_URI) : TimePackage.eINSTANCE);

        // Create package meta-data objects
        theConnectorPackage.createPackageContents();
        theBip2Package.createPackageContents();
        theUjfPackage.createPackageContents();
        theVerimagPackage.createPackageContents();
        theBipPackage.createPackageContents();
        theTypesPackage.createPackageContents();
        theDataPackage.createPackageContents();
        thePortPackage.createPackageContents();
        theBehaviorPackage.createPackageContents();
        thePriorityPackage.createPackageContents();
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
        theConnectorPackage.initializePackageContents();
        theBip2Package.initializePackageContents();
        theUjfPackage.initializePackageContents();
        theVerimagPackage.initializePackageContents();
        theBipPackage.initializePackageContents();
        theTypesPackage.initializePackageContents();
        theDataPackage.initializePackageContents();
        thePortPackage.initializePackageContents();
        theBehaviorPackage.initializePackageContents();
        thePriorityPackage.initializePackageContents();
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
        EValidator.Registry.INSTANCE.put(theConnectorPackage,
                new EValidator.Descriptor() {
                    public EValidator getEValidator() {
                        return ConnectorValidator.INSTANCE;
                    }
                });

        // Mark meta-data to indicate it can't be changed
        theConnectorPackage.freeze();

        // Update the registry and return the package
        EPackage.Registry.INSTANCE.put(ConnectorPackage.eNS_URI,
                theConnectorPackage);
        return theConnectorPackage;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getConnectorDeclaration() {
        return connectorDeclarationEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorDeclaration_Type() {
        return (EReference) connectorDeclarationEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getConnectorDeclaration_Name() {
        return (EAttribute) connectorDeclarationEClass.getEStructuralFeatures()
                .get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorDeclaration_PortParameters() {
        return (EReference) connectorDeclarationEClass.getEStructuralFeatures()
                .get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getConnectorPortParameterDeclaration() {
        return connectorPortParameterDeclarationEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getConnectorExportedPortDeclaration() {
        return connectorExportedPortDeclarationEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getConnectorDataDeclaration() {
        return connectorDataDeclarationEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getConnectorInteractionAction() {
        return connectorInteractionActionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorInteractionAction_OnPorts() {
        return (EReference) connectorInteractionActionEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorInteractionAction_Up() {
        return (EReference) connectorInteractionActionEClass
                .getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorInteractionAction_Down() {
        return (EReference) connectorInteractionActionEClass
                .getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getConnectorInteractionDefinition() {
        return connectorInteractionDefinitionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getConnectorInteractionDefinition_Quoted() {
        return (EAttribute) connectorInteractionDefinitionEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getConnectorInteractionPortReference() {
        return connectorInteractionPortReferenceEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorInteractionPortReference_Port() {
        return (EReference) connectorInteractionPortReferenceEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getConnectorInteractionNestedDefinition() {
        return connectorInteractionNestedDefinitionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorInteractionNestedDefinition_SubInteractions() {
        return (EReference) connectorInteractionNestedDefinitionEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorFactory getConnectorFactory() {
        return (ConnectorFactory) getEFactoryInstance();
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
        connectorDeclarationEClass = createEClass(CONNECTOR_DECLARATION);
        createEReference(connectorDeclarationEClass,
                CONNECTOR_DECLARATION__TYPE);
        createEReference(connectorDeclarationEClass,
                CONNECTOR_DECLARATION__PORT_PARAMETERS);
        createEAttribute(connectorDeclarationEClass,
                CONNECTOR_DECLARATION__NAME);

        connectorPortParameterDeclarationEClass = createEClass(CONNECTOR_PORT_PARAMETER_DECLARATION);

        connectorExportedPortDeclarationEClass = createEClass(CONNECTOR_EXPORTED_PORT_DECLARATION);

        connectorDataDeclarationEClass = createEClass(CONNECTOR_DATA_DECLARATION);

        connectorInteractionActionEClass = createEClass(CONNECTOR_INTERACTION_ACTION);
        createEReference(connectorInteractionActionEClass,
                CONNECTOR_INTERACTION_ACTION__ON_PORTS);
        createEReference(connectorInteractionActionEClass,
                CONNECTOR_INTERACTION_ACTION__UP);
        createEReference(connectorInteractionActionEClass,
                CONNECTOR_INTERACTION_ACTION__DOWN);

        connectorInteractionDefinitionEClass = createEClass(CONNECTOR_INTERACTION_DEFINITION);
        createEAttribute(connectorInteractionDefinitionEClass,
                CONNECTOR_INTERACTION_DEFINITION__QUOTED);

        connectorInteractionPortReferenceEClass = createEClass(CONNECTOR_INTERACTION_PORT_REFERENCE);
        createEReference(connectorInteractionPortReferenceEClass,
                CONNECTOR_INTERACTION_PORT_REFERENCE__PORT);

        connectorInteractionNestedDefinitionEClass = createEClass(CONNECTOR_INTERACTION_NESTED_DEFINITION);
        createEReference(connectorInteractionNestedDefinitionEClass,
                CONNECTOR_INTERACTION_NESTED_DEFINITION__SUB_INTERACTIONS);
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
        AnnotationPackage theAnnotationPackage = (AnnotationPackage) EPackage.Registry.INSTANCE
                .getEPackage(AnnotationPackage.eNS_URI);
        TypesPackage theTypesPackage = (TypesPackage) EPackage.Registry.INSTANCE
                .getEPackage(TypesPackage.eNS_URI);
        PortPackage thePortPackage = (PortPackage) EPackage.Registry.INSTANCE
                .getEPackage(PortPackage.eNS_URI);
        DataPackage theDataPackage = (DataPackage) EPackage.Registry.INSTANCE
                .getEPackage(DataPackage.eNS_URI);
        TimePackage theTimePackage = (TimePackage) EPackage.Registry.INSTANCE
                .getEPackage(TimePackage.eNS_URI);
        ActionlangPackage theActionlangPackage = (ActionlangPackage) EPackage.Registry.INSTANCE
                .getEPackage(ActionlangPackage.eNS_URI);

        // Create type parameters

        // Set bounds for type parameters

        // Add supertypes to classes
        connectorDeclarationEClass.getESuperTypes().add(
                theAnnotationPackage.getAnnotatedElement());
        connectorPortParameterDeclarationEClass.getESuperTypes().add(
                thePortPackage.getPortDeclaration());
        connectorExportedPortDeclarationEClass.getESuperTypes().add(
                thePortPackage.getPortDeclaration());
        connectorExportedPortDeclarationEClass.getESuperTypes().add(
                theAnnotationPackage.getAnnotatedElement());
        connectorDataDeclarationEClass.getESuperTypes().add(
                theDataPackage.getExplicitDataDeclaration());
        connectorInteractionActionEClass.getESuperTypes().add(
                theAnnotationPackage.getAnnotatedElement());
        connectorInteractionActionEClass.getESuperTypes().add(
                theTimePackage.getGuarded());
        connectorInteractionPortReferenceEClass.getESuperTypes().add(
                this.getConnectorInteractionDefinition());
        connectorInteractionNestedDefinitionEClass.getESuperTypes().add(
                this.getConnectorInteractionDefinition());

        // Initialize classes and features; add operations and parameters
        initEClass(connectorDeclarationEClass, ConnectorDeclaration.class,
                "ConnectorDeclaration", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEReference(getConnectorDeclaration_Type(),
                theTypesPackage.getConnectorType(), null, "type", null, 1, 1,
                ConnectorDeclaration.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getConnectorDeclaration_PortParameters(),
                thePortPackage.getPortDeclarationReferenceParameter(), null,
                "portParameters", null, 0, -1, ConnectorDeclaration.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEAttribute(getConnectorDeclaration_Name(),
                ecorePackage.getEString(), "name", null, 1, 1,
                ConnectorDeclaration.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_UNSETTABLE, IS_ID, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        initEClass(connectorPortParameterDeclarationEClass,
                ConnectorPortParameterDeclaration.class,
                "ConnectorPortParameterDeclaration", !IS_ABSTRACT,
                !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);

        initEClass(connectorExportedPortDeclarationEClass,
                ConnectorExportedPortDeclaration.class,
                "ConnectorExportedPortDeclaration", !IS_ABSTRACT,
                !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);

        initEClass(connectorDataDeclarationEClass,
                ConnectorDataDeclaration.class, "ConnectorDataDeclaration",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);

        initEClass(connectorInteractionActionEClass,
                ConnectorInteractionAction.class, "ConnectorInteractionAction",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getConnectorInteractionAction_OnPorts(),
                this.getConnectorPortParameterDeclaration(), null, "onPorts",
                null, 1, -1, ConnectorInteractionAction.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getConnectorInteractionAction_Up(),
                theActionlangPackage.getExpression(), null, "up", null, 0, -1,
                ConnectorInteractionAction.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getConnectorInteractionAction_Down(),
                theActionlangPackage.getExpression(), null, "down", null, 0,
                -1, ConnectorInteractionAction.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(connectorInteractionDefinitionEClass,
                ConnectorInteractionDefinition.class,
                "ConnectorInteractionDefinition", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getConnectorInteractionDefinition_Quoted(),
                ecorePackage.getEBoolean(), "quoted", null, 1, 1,
                ConnectorInteractionDefinition.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE,
                !IS_DERIVED, IS_ORDERED);

        initEClass(connectorInteractionPortReferenceEClass,
                ConnectorInteractionPortReference.class,
                "ConnectorInteractionPortReference", !IS_ABSTRACT,
                !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getConnectorInteractionPortReference_Port(),
                this.getConnectorPortParameterDeclaration(), null, "port",
                null, 1, 1, ConnectorInteractionPortReference.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE,
                IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        initEClass(connectorInteractionNestedDefinitionEClass,
                ConnectorInteractionNestedDefinition.class,
                "ConnectorInteractionNestedDefinition", !IS_ABSTRACT,
                !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(
                getConnectorInteractionNestedDefinition_SubInteractions(),
                this.getConnectorInteractionDefinition(), null,
                "subInteractions", null, 1, -1,
                ConnectorInteractionNestedDefinition.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

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
        addAnnotation(
                connectorDeclarationEClass,
                source,
                new String[] {
                        "constraints",
                        "hasCorrectNumberOfPortParameters connectorDeclarationHasnoDuplicatedPortReferenceParameter connectorHasExportPortBound" });
        addAnnotation(
                connectorInteractionActionEClass,
                source,
                new String[] {
                        "constraints",
                        "onPortInConnectorParameters upDoesNotContainExternalSubDataRefOnLHSAssignments connectorActionNotEmpty noUpIfNoExportedPort triggerPortsValidWrtDefine missingUpForExportedPort hasNoVariableModifiedBetweenUpAndDown checkUninitializedVariablesOfConnectorInteractionAction checkUninitializedVariablesExportedByPortOfConnector" });
    }

} //ConnectorPackageImpl
