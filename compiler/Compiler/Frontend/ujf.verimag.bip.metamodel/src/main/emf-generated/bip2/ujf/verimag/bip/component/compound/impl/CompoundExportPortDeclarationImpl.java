/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
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

package bip2.ujf.verimag.bip.component.compound.impl;

import bip2.ujf.verimag.bip.annotation.AnnotatedElement;
import bip2.ujf.verimag.bip.annotation.AnnotationPackage;
import bip2.ujf.verimag.bip.annotation.BipAnnotation;
import bip2.ujf.verimag.bip.annotation.impl.StringToAnnotationMapEntryImpl;
import bip2.ujf.verimag.bip.component.compound.CompoundExportPortDeclaration;
import bip2.ujf.verimag.bip.component.compound.CompoundPackage;

import bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter;

import bip2.ujf.verimag.bip.port.SubPortDeclarationReference;

import bip2.ujf.verimag.bip.types.PortType;

import java.util.Collection;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.common.util.EMap;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EStructuralFeature;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.emf.ecore.impl.EObjectImpl;

import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.EcoreEMap;
import org.eclipse.emf.ecore.util.InternalEList;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Export Port Declaration</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.component.compound.impl.CompoundExportPortDeclarationImpl#getPortType <em>Port Type</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.component.compound.impl.CompoundExportPortDeclarationImpl#getName <em>Name</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.component.compound.impl.CompoundExportPortDeclarationImpl#getDataParameters <em>Data Parameters</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.component.compound.impl.CompoundExportPortDeclarationImpl#getBipAnnotations <em>Bip Annotations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.component.compound.impl.CompoundExportPortDeclarationImpl#getPortDeclarationReferences <em>Port Declaration References</em>}</li>
 * </ul>
 *
 * @generated
 */
public class CompoundExportPortDeclarationImpl extends AnnotatedEObjectImpl
        implements CompoundExportPortDeclaration {
    /**
     * The cached value of the '{@link #getPortType() <em>Port Type</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPortType()
     * @generated
     * @ordered
     */
    protected PortType portType;

    /**
     * The default value of the '{@link #getName() <em>Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getName()
     * @generated
     * @ordered
     */
    protected static final String NAME_EDEFAULT = null;

    /**
     * The cached value of the '{@link #getName() <em>Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getName()
     * @generated
     * @ordered
     */
    protected String name = NAME_EDEFAULT;

    /**
     * The cached value of the '{@link #getDataParameters() <em>Data Parameters</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDataParameters()
     * @generated
     * @ordered
     */
    protected EList<DataDeclarationReferenceDataParameter> dataParameters;

    /**
     * The cached value of the '{@link #getBipAnnotations() <em>Bip Annotations</em>}' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getBipAnnotations()
     * @generated
     * @ordered
     */
    protected EMap<String, BipAnnotation> bipAnnotations;

    /**
     * The cached value of the '{@link #getPortDeclarationReferences() <em>Port Declaration References</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPortDeclarationReferences()
     * @generated
     * @ordered
     */
    protected EList<SubPortDeclarationReference> portDeclarationReferences;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected CompoundExportPortDeclarationImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return CompoundPackage.Literals.COMPOUND_EXPORT_PORT_DECLARATION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public PortType getPortType() {
        if (portType != null && ((EObject) portType).eIsProxy()) {
            InternalEObject oldPortType = (InternalEObject) portType;
            portType = (PortType) eResolveProxy(oldPortType);
            if (portType != oldPortType) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__PORT_TYPE,
                            oldPortType, portType));
            }
        }
        return portType;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PortType basicGetPortType() {
        return portType;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void setPortType(PortType newPortType) {
        PortType oldPortType = portType;
        portType = newPortType;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__PORT_TYPE,
                    oldPortType, portType));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public String getName() {
        return name;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void setName(String newName) {
        String oldName = name;
        name = newName;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__NAME,
                    oldName, name));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EList<DataDeclarationReferenceDataParameter> getDataParameters() {
        if (dataParameters == null) {
            dataParameters = new EObjectContainmentEList<DataDeclarationReferenceDataParameter>(
                    DataDeclarationReferenceDataParameter.class, this,
                    CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__DATA_PARAMETERS);
        }
        return dataParameters;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EMap<String, BipAnnotation> getBipAnnotations() {
        if (bipAnnotations == null) {
            bipAnnotations = new EcoreEMap<String, BipAnnotation>(
                    AnnotationPackage.Literals.STRING_TO_ANNOTATION_MAP_ENTRY,
                    StringToAnnotationMapEntryImpl.class, this,
                    CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__BIP_ANNOTATIONS);
        }
        return bipAnnotations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EList<SubPortDeclarationReference> getPortDeclarationReferences() {
        if (portDeclarationReferences == null) {
            portDeclarationReferences = new EObjectContainmentEList<SubPortDeclarationReference>(
                    SubPortDeclarationReference.class, this,
                    CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__PORT_DECLARATION_REFERENCES);
        }
        return portDeclarationReferences;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public DataDeclarationReferenceDataParameter getDataParameter(String name) {
        // Getting data parameters on such port is not possible (there can be multiple
        // ports behind.
        throw new UnsupportedOperationException();
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
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__DATA_PARAMETERS:
            return ((InternalEList<?>) getDataParameters())
                    .basicRemove(otherEnd, msgs);
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__BIP_ANNOTATIONS:
            return ((InternalEList<?>) getBipAnnotations())
                    .basicRemove(otherEnd, msgs);
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__PORT_DECLARATION_REFERENCES:
            return ((InternalEList<?>) getPortDeclarationReferences())
                    .basicRemove(otherEnd, msgs);
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
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__PORT_TYPE:
            if (resolve)
                return getPortType();
            return basicGetPortType();
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__NAME:
            return getName();
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__DATA_PARAMETERS:
            return getDataParameters();
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__BIP_ANNOTATIONS:
            if (coreType)
                return getBipAnnotations();
            else
                return getBipAnnotations().map();
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__PORT_DECLARATION_REFERENCES:
            return getPortDeclarationReferences();
        }
        return super.eGet(featureID, resolve, coreType);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @SuppressWarnings("unchecked")
    @Override
    public void eSet(int featureID, Object newValue) {
        switch (featureID) {
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__PORT_TYPE:
            setPortType((PortType) newValue);
            return;
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__NAME:
            setName((String) newValue);
            return;
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__DATA_PARAMETERS:
            getDataParameters().clear();
            getDataParameters().addAll(
                    (Collection<? extends DataDeclarationReferenceDataParameter>) newValue);
            return;
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__BIP_ANNOTATIONS:
            ((EStructuralFeature.Setting) getBipAnnotations()).set(newValue);
            return;
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__PORT_DECLARATION_REFERENCES:
            getPortDeclarationReferences().clear();
            getPortDeclarationReferences().addAll(
                    (Collection<? extends SubPortDeclarationReference>) newValue);
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
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__PORT_TYPE:
            setPortType((PortType) null);
            return;
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__NAME:
            setName(NAME_EDEFAULT);
            return;
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__DATA_PARAMETERS:
            getDataParameters().clear();
            return;
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__BIP_ANNOTATIONS:
            getBipAnnotations().clear();
            return;
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__PORT_DECLARATION_REFERENCES:
            getPortDeclarationReferences().clear();
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
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__PORT_TYPE:
            return portType != null;
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__NAME:
            return NAME_EDEFAULT == null ? name != null
                    : !NAME_EDEFAULT.equals(name);
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__DATA_PARAMETERS:
            return dataParameters != null && !dataParameters.isEmpty();
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__BIP_ANNOTATIONS:
            return bipAnnotations != null && !bipAnnotations.isEmpty();
        case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__PORT_DECLARATION_REFERENCES:
            return portDeclarationReferences != null
                    && !portDeclarationReferences.isEmpty();
        }
        return super.eIsSet(featureID);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public int eBaseStructuralFeatureID(int derivedFeatureID,
            Class<?> baseClass) {
        if (baseClass == AnnotatedElement.class) {
            switch (derivedFeatureID) {
            case CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__BIP_ANNOTATIONS:
                return AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS;
            default:
                return -1;
            }
        }
        return super.eBaseStructuralFeatureID(derivedFeatureID, baseClass);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public int eDerivedStructuralFeatureID(int baseFeatureID,
            Class<?> baseClass) {
        if (baseClass == AnnotatedElement.class) {
            switch (baseFeatureID) {
            case AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS:
                return CompoundPackage.COMPOUND_EXPORT_PORT_DECLARATION__BIP_ANNOTATIONS;
            default:
                return -1;
            }
        }
        return super.eDerivedStructuralFeatureID(baseFeatureID, baseClass);
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
        result.append(" (name: ");
        result.append(name);
        result.append(')');
        return result.toString();
    }

} //CompoundExportPortDeclarationImpl
