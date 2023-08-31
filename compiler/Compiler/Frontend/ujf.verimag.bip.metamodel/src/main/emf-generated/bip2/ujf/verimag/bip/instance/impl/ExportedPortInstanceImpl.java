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

package bip2.ujf.verimag.bip.instance.impl;

import bip2.ujf.verimag.bip.instance.ExportedPortInstance;
import bip2.ujf.verimag.bip.instance.InstancePackage;
import bip2.ujf.verimag.bip.instance.PortInstance;

import bip2.ujf.verimag.bip.port.PortDeclaration;
import java.util.Collection;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;
import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.emf.ecore.util.EObjectResolvingEList;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Exported Port Instance</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.ExportedPortInstanceImpl#getDeclaration <em>Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.ExportedPortInstanceImpl#getReferencedPorts <em>Referenced Ports</em>}</li>
 * </ul>
 *
 * @generated
 */
public class ExportedPortInstanceImpl extends AnnotatedEObjectImpl
        implements ExportedPortInstance {
    /**
     * The cached value of the '{@link #getDeclaration() <em>Declaration</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDeclaration()
     * @generated
     * @ordered
     */
    protected PortDeclaration declaration;
    /**
     * The cached value of the '{@link #getReferencedPorts() <em>Referenced Ports</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getReferencedPorts()
     * @generated
     * @ordered
     */
    protected EList<PortInstance> referencedPorts;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected ExportedPortInstanceImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return InstancePackage.Literals.EXPORTED_PORT_INSTANCE;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public PortDeclaration getDeclaration() {
        if (declaration != null && ((EObject) declaration).eIsProxy()) {
            InternalEObject oldDeclaration = (InternalEObject) declaration;
            declaration = (PortDeclaration) eResolveProxy(oldDeclaration);
            if (declaration != oldDeclaration) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            InstancePackage.EXPORTED_PORT_INSTANCE__DECLARATION,
                            oldDeclaration, declaration));
            }
        }
        return declaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PortDeclaration basicGetDeclaration() {
        return declaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void setDeclaration(PortDeclaration newDeclaration) {
        PortDeclaration oldDeclaration = declaration;
        declaration = newDeclaration;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    InstancePackage.EXPORTED_PORT_INSTANCE__DECLARATION,
                    oldDeclaration, declaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EList<PortInstance> getReferencedPorts() {
        if (referencedPorts == null) {
            referencedPorts = new EObjectResolvingEList<PortInstance>(
                    PortInstance.class, this,
                    InstancePackage.EXPORTED_PORT_INSTANCE__REFERENCED_PORTS);
        }
        return referencedPorts;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case InstancePackage.EXPORTED_PORT_INSTANCE__DECLARATION:
            if (resolve)
                return getDeclaration();
            return basicGetDeclaration();
        case InstancePackage.EXPORTED_PORT_INSTANCE__REFERENCED_PORTS:
            return getReferencedPorts();
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
        case InstancePackage.EXPORTED_PORT_INSTANCE__DECLARATION:
            setDeclaration((PortDeclaration) newValue);
            return;
        case InstancePackage.EXPORTED_PORT_INSTANCE__REFERENCED_PORTS:
            getReferencedPorts().clear();
            getReferencedPorts()
                    .addAll((Collection<? extends PortInstance>) newValue);
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
        case InstancePackage.EXPORTED_PORT_INSTANCE__DECLARATION:
            setDeclaration((PortDeclaration) null);
            return;
        case InstancePackage.EXPORTED_PORT_INSTANCE__REFERENCED_PORTS:
            getReferencedPorts().clear();
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
        case InstancePackage.EXPORTED_PORT_INSTANCE__DECLARATION:
            return declaration != null;
        case InstancePackage.EXPORTED_PORT_INSTANCE__REFERENCED_PORTS:
            return referencedPorts != null && !referencedPorts.isEmpty();
        }
        return super.eIsSet(featureID);
    }

} //ExportedPortInstanceImpl
