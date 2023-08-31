/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
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

import bip2.ujf.verimag.bip.packaging.FunctionCallPrototype;
import bip2.ujf.verimag.bip.packaging.PackagingPackage;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.ecore.EClass;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Function Call Prototype</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.impl.FunctionCallPrototypeImpl#getFunctionName <em>Function Name</em>}</li>
 * </ul>
 *
 * @generated
 */
public class FunctionCallPrototypeImpl extends PrototypeImpl
        implements FunctionCallPrototype {
    /**
     * The default value of the '{@link #getFunctionName() <em>Function Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getFunctionName()
     * @generated
     * @ordered
     */
    protected static final String FUNCTION_NAME_EDEFAULT = null;

    /**
     * The cached value of the '{@link #getFunctionName() <em>Function Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getFunctionName()
     * @generated
     * @ordered
     */
    protected String functionName = FUNCTION_NAME_EDEFAULT;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected FunctionCallPrototypeImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return PackagingPackage.Literals.FUNCTION_CALL_PROTOTYPE;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public String getFunctionName() {
        return functionName;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void setFunctionName(String newFunctionName) {
        String oldFunctionName = functionName;
        functionName = newFunctionName;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PackagingPackage.FUNCTION_CALL_PROTOTYPE__FUNCTION_NAME,
                    oldFunctionName, functionName));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case PackagingPackage.FUNCTION_CALL_PROTOTYPE__FUNCTION_NAME:
            return getFunctionName();
        }
        return super.eGet(featureID, resolve, coreType);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void eSet(int featureID, Object newValue) {
        switch (featureID) {
        case PackagingPackage.FUNCTION_CALL_PROTOTYPE__FUNCTION_NAME:
            setFunctionName((String) newValue);
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
        case PackagingPackage.FUNCTION_CALL_PROTOTYPE__FUNCTION_NAME:
            setFunctionName(FUNCTION_NAME_EDEFAULT);
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
        case PackagingPackage.FUNCTION_CALL_PROTOTYPE__FUNCTION_NAME:
            return FUNCTION_NAME_EDEFAULT == null ? functionName != null
                    : !FUNCTION_NAME_EDEFAULT.equals(functionName);
        }
        return super.eIsSet(featureID);
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
        result.append(" (functionName: ");
        result.append(functionName);
        result.append(')');
        return result.toString();
    }

} //FunctionCallPrototypeImpl
