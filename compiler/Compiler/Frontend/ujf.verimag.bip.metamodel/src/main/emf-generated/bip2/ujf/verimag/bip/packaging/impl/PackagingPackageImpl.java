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

package bip2.ujf.verimag.bip.packaging.impl;

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
import bip2.ujf.verimag.bip.packaging.BinaryOpPrototype;
import bip2.ujf.verimag.bip.packaging.BipPackageSet;
import bip2.ujf.verimag.bip.packaging.ConstDataDeclaration;
import bip2.ujf.verimag.bip.packaging.FunctionCallPrototype;
import bip2.ujf.verimag.bip.packaging.PackagingFactory;
import bip2.ujf.verimag.bip.packaging.PackagingPackage;

import bip2.ujf.verimag.bip.packaging.Prototype;
import bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration;
import bip2.ujf.verimag.bip.packaging.UnaryOpPrototype;
import bip2.ujf.verimag.bip.packaging.util.PackagingValidator;
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
public class PackagingPackageImpl extends EPackageImpl
        implements PackagingPackage {
    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass bipPackageEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass bipPackageSetEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass constDataDeclarationEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass prototypeEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass functionCallPrototypeEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass binaryOpPrototypeEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass unaryOpPrototypeEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass prototypeParameterDeclarationEClass = null;

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
     * @see bip2.ujf.verimag.bip.packaging.PackagingPackage#eNS_URI
     * @see #init()
     * @generated
     */
    private PackagingPackageImpl() {
        super(eNS_URI, PackagingFactory.eINSTANCE);
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
     * <p>This method is used to initialize {@link PackagingPackage#eINSTANCE} when that field is accessed.
     * Clients should not invoke it directly. Instead, they should simply access that field to obtain the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #eNS_URI
     * @see #createPackageContents()
     * @see #initializePackageContents()
     * @generated
     */
    public static PackagingPackage init() {
        if (isInited)
            return (PackagingPackage) EPackage.Registry.INSTANCE
                    .getEPackage(PackagingPackage.eNS_URI);

        // Obtain or create and register package
        Object registeredPackagingPackage = EPackage.Registry.INSTANCE
                .get(eNS_URI);
        PackagingPackageImpl thePackagingPackage = registeredPackagingPackage instanceof PackagingPackageImpl
                ? (PackagingPackageImpl) registeredPackagingPackage
                : new PackagingPackageImpl();

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
        thePackagingPackage.createPackageContents();
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
        theActionlangPackage.createPackageContents();
        theInstancePackage.createPackageContents();
        theAnnotationPackage.createPackageContents();
        theInvariantPackage.createPackageContents();
        theTimePackage.createPackageContents();

        // Initialize created meta-data
        thePackagingPackage.initializePackageContents();
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
        theActionlangPackage.initializePackageContents();
        theInstancePackage.initializePackageContents();
        theAnnotationPackage.initializePackageContents();
        theInvariantPackage.initializePackageContents();
        theTimePackage.initializePackageContents();

        // Register package validator
        EValidator.Registry.INSTANCE.put(thePackagingPackage,
                new EValidator.Descriptor() {
                    @Override
                    public EValidator getEValidator() {
                        return PackagingValidator.INSTANCE;
                    }
                });

        // Mark meta-data to indicate it can't be changed
        thePackagingPackage.freeze();

        // Update the registry and return the package
        EPackage.Registry.INSTANCE.put(PackagingPackage.eNS_URI,
                thePackagingPackage);
        return thePackagingPackage;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getBipPackage() {
        return bipPackageEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getBipPackage_Name() {
        return (EAttribute) bipPackageEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getBipPackage_Used_packages() {
        return (EReference) bipPackageEClass.getEStructuralFeatures().get(6);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getBipPackage_ConstData() {
        return (EReference) bipPackageEClass.getEStructuralFeatures().get(7);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getBipPackage_Prototypes() {
        return (EReference) bipPackageEClass.getEStructuralFeatures().get(8);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getBipPackageSet() {
        return bipPackageSetEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getBipPackageSet_Packages() {
        return (EReference) bipPackageSetEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getConstDataDeclaration() {
        return constDataDeclarationEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getPrototype() {
        return prototypeEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getPrototype_ParameterDeclarations() {
        return (EReference) prototypeEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getPrototype_ReturnType() {
        return (EReference) prototypeEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getPrototype_Native() {
        return (EAttribute) prototypeEClass.getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getPrototype_Const() {
        return (EAttribute) prototypeEClass.getEStructuralFeatures().get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getFunctionCallPrototype() {
        return functionCallPrototypeEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getFunctionCallPrototype_FunctionName() {
        return (EAttribute) functionCallPrototypeEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getBinaryOpPrototype() {
        return binaryOpPrototypeEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getBinaryOpPrototype_Operator() {
        return (EAttribute) binaryOpPrototypeEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getUnaryOpPrototype() {
        return unaryOpPrototypeEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getUnaryOpPrototype_Operator() {
        return (EAttribute) unaryOpPrototypeEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EClass getPrototypeParameterDeclaration() {
        return prototypeParameterDeclarationEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getPrototypeParameterDeclaration_Type() {
        return (EReference) prototypeParameterDeclarationEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getPrototypeParameterDeclaration_Name() {
        return (EAttribute) prototypeParameterDeclarationEClass
                .getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EAttribute getPrototypeParameterDeclaration_Const() {
        return (EAttribute) prototypeParameterDeclarationEClass
                .getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getBipPackage_AtomTypes() {
        return (EReference) bipPackageEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getBipPackage_CompoundTypes() {
        return (EReference) bipPackageEClass.getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getBipPackage_ConnectorTypes() {
        return (EReference) bipPackageEClass.getEStructuralFeatures().get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getBipPackage_PortTypes() {
        return (EReference) bipPackageEClass.getEStructuralFeatures().get(4);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EReference getBipPackage_DataTypes() {
        return (EReference) bipPackageEClass.getEStructuralFeatures().get(5);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public PackagingFactory getPackagingFactory() {
        return (PackagingFactory) getEFactoryInstance();
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
        bipPackageEClass = createEClass(BIP_PACKAGE);
        createEAttribute(bipPackageEClass, BIP_PACKAGE__NAME);
        createEReference(bipPackageEClass, BIP_PACKAGE__ATOM_TYPES);
        createEReference(bipPackageEClass, BIP_PACKAGE__COMPOUND_TYPES);
        createEReference(bipPackageEClass, BIP_PACKAGE__CONNECTOR_TYPES);
        createEReference(bipPackageEClass, BIP_PACKAGE__PORT_TYPES);
        createEReference(bipPackageEClass, BIP_PACKAGE__DATA_TYPES);
        createEReference(bipPackageEClass, BIP_PACKAGE__USED_PACKAGES);
        createEReference(bipPackageEClass, BIP_PACKAGE__CONST_DATA);
        createEReference(bipPackageEClass, BIP_PACKAGE__PROTOTYPES);

        bipPackageSetEClass = createEClass(BIP_PACKAGE_SET);
        createEReference(bipPackageSetEClass, BIP_PACKAGE_SET__PACKAGES);

        constDataDeclarationEClass = createEClass(CONST_DATA_DECLARATION);

        prototypeEClass = createEClass(PROTOTYPE);
        createEReference(prototypeEClass, PROTOTYPE__PARAMETER_DECLARATIONS);
        createEReference(prototypeEClass, PROTOTYPE__RETURN_TYPE);
        createEAttribute(prototypeEClass, PROTOTYPE__NATIVE);
        createEAttribute(prototypeEClass, PROTOTYPE__CONST);

        functionCallPrototypeEClass = createEClass(FUNCTION_CALL_PROTOTYPE);
        createEAttribute(functionCallPrototypeEClass,
                FUNCTION_CALL_PROTOTYPE__FUNCTION_NAME);

        binaryOpPrototypeEClass = createEClass(BINARY_OP_PROTOTYPE);
        createEAttribute(binaryOpPrototypeEClass,
                BINARY_OP_PROTOTYPE__OPERATOR);

        unaryOpPrototypeEClass = createEClass(UNARY_OP_PROTOTYPE);
        createEAttribute(unaryOpPrototypeEClass, UNARY_OP_PROTOTYPE__OPERATOR);

        prototypeParameterDeclarationEClass = createEClass(
                PROTOTYPE_PARAMETER_DECLARATION);
        createEReference(prototypeParameterDeclarationEClass,
                PROTOTYPE_PARAMETER_DECLARATION__TYPE);
        createEAttribute(prototypeParameterDeclarationEClass,
                PROTOTYPE_PARAMETER_DECLARATION__NAME);
        createEAttribute(prototypeParameterDeclarationEClass,
                PROTOTYPE_PARAMETER_DECLARATION__CONST);
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
        DataPackage theDataPackage = (DataPackage) EPackage.Registry.INSTANCE
                .getEPackage(DataPackage.eNS_URI);
        ActionlangPackage theActionlangPackage = (ActionlangPackage) EPackage.Registry.INSTANCE
                .getEPackage(ActionlangPackage.eNS_URI);
        TimePackage theTimePackage = (TimePackage) EPackage.Registry.INSTANCE
                .getEPackage(TimePackage.eNS_URI);

        // Create type parameters

        // Set bounds for type parameters

        // Add supertypes to classes
        bipPackageEClass.getESuperTypes()
                .add(theAnnotationPackage.getAnnotatedElement());
        constDataDeclarationEClass.getESuperTypes()
                .add(theDataPackage.getExplicitDataDeclaration());
        prototypeEClass.getESuperTypes()
                .add(theAnnotationPackage.getAnnotatedElement());
        functionCallPrototypeEClass.getESuperTypes().add(this.getPrototype());
        binaryOpPrototypeEClass.getESuperTypes().add(this.getPrototype());
        unaryOpPrototypeEClass.getESuperTypes().add(this.getPrototype());

        // Initialize classes and features; add operations and parameters
        initEClass(bipPackageEClass,
                bip2.ujf.verimag.bip.packaging.BipPackage.class, "BipPackage",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getBipPackage_Name(), ecorePackage.getEString(), "name",
                null, 1, 1, bip2.ujf.verimag.bip.packaging.BipPackage.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE,
                !IS_ID, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getBipPackage_AtomTypes(), theTypesPackage.getAtomType(),
                null, "atomTypes", null, 0, -1,
                bip2.ujf.verimag.bip.packaging.BipPackage.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getBipPackage_CompoundTypes(),
                theTypesPackage.getCompoundType(), null, "compoundTypes", null,
                0, -1, bip2.ujf.verimag.bip.packaging.BipPackage.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getBipPackage_ConnectorTypes(),
                theTypesPackage.getConnectorType(), null, "connectorTypes",
                null, 0, -1, bip2.ujf.verimag.bip.packaging.BipPackage.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getBipPackage_PortTypes(), theTypesPackage.getPortType(),
                null, "portTypes", null, 0, -1,
                bip2.ujf.verimag.bip.packaging.BipPackage.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getBipPackage_DataTypes(), theDataPackage.getDataType(),
                null, "dataTypes", null, 0, -1,
                bip2.ujf.verimag.bip.packaging.BipPackage.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getBipPackage_Used_packages(), this.getBipPackage(),
                null, "used_packages", null, 0, -1,
                bip2.ujf.verimag.bip.packaging.BipPackage.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getBipPackage_ConstData(),
                this.getConstDataDeclaration(), null, "constData", null, 0, -1,
                bip2.ujf.verimag.bip.packaging.BipPackage.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getBipPackage_Prototypes(), this.getPrototype(), null,
                "prototypes", null, 0, -1,
                bip2.ujf.verimag.bip.packaging.BipPackage.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        EOperation op = addEOperation(bipPackageEClass,
                theTypesPackage.getAtomType(), "getAtomType", 0, 1, IS_UNIQUE,
                IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(bipPackageEClass, theTypesPackage.getCompoundType(),
                "getCompoundType", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(bipPackageEClass, theTypesPackage.getConnectorType(),
                "getConnectorType", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(bipPackageEClass, theTypesPackage.getPortType(),
                "getPortType", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(bipPackageEClass, theDataPackage.getDataType(),
                "getDataType", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(bipPackageEClass, this.getConstDataDeclaration(),
                "getConstDataDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(bipPackageEClass, this.getFunctionCallPrototype(),
                "getFunctionCallPrototypes", 0, -1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "functionName", 0, 1,
                IS_UNIQUE, IS_ORDERED);

        op = addEOperation(bipPackageEClass, this.getFunctionCallPrototype(),
                "getFunctionCallPrototypes", 0, -1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "functionName", 0, 1,
                IS_UNIQUE, IS_ORDERED);
        addEParameter(op, theTypesPackage.getType(), "parametersTypes", 0, -1,
                !IS_UNIQUE, IS_ORDERED);

        op = addEOperation(bipPackageEClass, this.getBinaryOpPrototype(),
                "getBinaryOpPrototypes", 0, -1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, theActionlangPackage.getBinaryOperators(), "operator",
                0, 1, IS_UNIQUE, IS_ORDERED);

        op = addEOperation(bipPackageEClass, this.getBinaryOpPrototype(),
                "getBinaryOpPrototypes", 0, -1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, theActionlangPackage.getBinaryOperators(), "operator",
                0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, theTypesPackage.getType(), "parametersTypes", 0, -1,
                !IS_UNIQUE, IS_ORDERED);

        op = addEOperation(bipPackageEClass, this.getUnaryOpPrototype(),
                "getUnaryOpPrototypes", 0, -1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, theActionlangPackage.getUnaryOperators(), "operator",
                0, 1, IS_UNIQUE, IS_ORDERED);

        op = addEOperation(bipPackageEClass, this.getUnaryOpPrototype(),
                "getUnaryOpPrototypes", 0, -1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, theActionlangPackage.getUnaryOperators(), "operator",
                0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, theTypesPackage.getType(), "parametersTypes", 0, -1,
                !IS_UNIQUE, IS_ORDERED);

        addEOperation(bipPackageEClass, theDataPackage.getDataType(),
                "getBoolDataType", 1, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(bipPackageEClass, theDataPackage.getDataType(),
                "getIntDataType", 1, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(bipPackageEClass, theDataPackage.getDataType(),
                "getFloatDataType", 1, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(bipPackageEClass, theDataPackage.getDataType(),
                "getStringDataType", 1, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(bipPackageEClass, theTimePackage.getTime(),
                "getNanosecondType", 1, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(bipPackageEClass, theTimePackage.getTime(),
                "getMicrosecondType", 1, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(bipPackageEClass, theTimePackage.getTime(),
                "getMillisecondType", 1, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(bipPackageEClass, theTimePackage.getTime(),
                "getSecondType", 1, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(bipPackageEClass, theTimePackage.getTime(),
                "getMinuteType", 1, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(bipPackageEClass, theTimePackage.getTime(), "getHourType",
                1, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(bipPackageEClass, theTimePackage.getTime(), "getDayType",
                1, 1, IS_UNIQUE, IS_ORDERED);

        initEClass(bipPackageSetEClass, BipPackageSet.class, "BipPackageSet",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getBipPackageSet_Packages(), this.getBipPackage(), null,
                "packages", null, 0, -1, BipPackageSet.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(constDataDeclarationEClass, ConstDataDeclaration.class,
                "ConstDataDeclaration", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);

        initEClass(prototypeEClass, Prototype.class, "Prototype", IS_ABSTRACT,
                !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getPrototype_ParameterDeclarations(),
                this.getPrototypeParameterDeclaration(), null,
                "parameterDeclarations", null, 0, -1, Prototype.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getPrototype_ReturnType(), theTypesPackage.getType(),
                null, "returnType", null, 0, 1, Prototype.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getPrototype_Native(), ecorePackage.getEBoolean(),
                "native", null, 1, 1, Prototype.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE,
                !IS_DERIVED, IS_ORDERED);
        initEAttribute(getPrototype_Const(), ecorePackage.getEBoolean(),
                "const", null, 1, 1, Prototype.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE,
                !IS_DERIVED, IS_ORDERED);

        op = addEOperation(prototypeEClass, ecorePackage.getEBoolean(),
                "isBetterMatchingThan", 1, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, theTypesPackage.getType(), "types", 0, -1, !IS_UNIQUE,
                IS_ORDERED);
        addEParameter(op, this.getPrototype(), "prototype", 1, 1, IS_UNIQUE,
                IS_ORDERED);

        initEClass(functionCallPrototypeEClass, FunctionCallPrototype.class,
                "FunctionCallPrototype", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getFunctionCallPrototype_FunctionName(),
                ecorePackage.getEString(), "functionName", null, 1, 1,
                FunctionCallPrototype.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        initEClass(binaryOpPrototypeEClass, BinaryOpPrototype.class,
                "BinaryOpPrototype", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getBinaryOpPrototype_Operator(),
                theActionlangPackage.getBinaryOperators(), "operator", null, 1,
                1, BinaryOpPrototype.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        initEClass(unaryOpPrototypeEClass, UnaryOpPrototype.class,
                "UnaryOpPrototype", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getUnaryOpPrototype_Operator(),
                theActionlangPackage.getUnaryOperators(), "operator", null, 1,
                1, UnaryOpPrototype.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        initEClass(prototypeParameterDeclarationEClass,
                PrototypeParameterDeclaration.class,
                "PrototypeParameterDeclaration", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEReference(getPrototypeParameterDeclaration_Type(),
                theTypesPackage.getType(), null, "type", null, 1, 1,
                PrototypeParameterDeclaration.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getPrototypeParameterDeclaration_Name(),
                ecorePackage.getEString(), "name", null, 1, 1,
                PrototypeParameterDeclaration.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE,
                !IS_DERIVED, IS_ORDERED);
        initEAttribute(getPrototypeParameterDeclaration_Const(),
                ecorePackage.getEBoolean(), "const", null, 1, 1,
                PrototypeParameterDeclaration.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE,
                !IS_DERIVED, IS_ORDERED);

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
        addAnnotation(bipPackageEClass, source,
                new String[] { "constraints", "checkForCyclesInSubTyping" });
        addAnnotation(constDataDeclarationEClass, source,
                new String[] { "constraints", "hasCorrectConst" });
        addAnnotation(prototypeEClass, source, new String[] { "constraints",
                "involveOnlyDataTypeIfNotNative" });
    }

} //PackagingPackageImpl
