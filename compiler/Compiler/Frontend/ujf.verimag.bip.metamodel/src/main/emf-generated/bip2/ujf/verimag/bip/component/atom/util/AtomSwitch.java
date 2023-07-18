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

package bip2.ujf.verimag.bip.component.atom.util;

import bip2.ujf.verimag.bip.annotation.AnnotatedElement;
import bip2.ujf.verimag.bip.component.atom.*;

import bip2.ujf.verimag.bip.data.DataDeclaration;

import bip2.ujf.verimag.bip.data.ExplicitDataDeclaration;
import bip2.ujf.verimag.bip.port.PortDeclaration;

import java.util.List;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.util.Switch;

/**
 * <!-- begin-user-doc -->
 * The <b>Switch</b> for the model's inheritance hierarchy.
 * It supports the call {@link #doSwitch(EObject) doSwitch(object)}
 * to invoke the <code>caseXXX</code> method for each class of the model,
 * starting with the actual class of the object
 * and proceeding up the inheritance hierarchy
 * until a non-null result is returned,
 * which is the result of the switch.
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.component.atom.AtomPackage
 * @generated
 */
public class AtomSwitch<T> extends Switch<T> {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected static AtomPackage modelPackage;

    /**
     * Creates an instance of the switch.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomSwitch() {
        if (modelPackage == null) {
            modelPackage = AtomPackage.eINSTANCE;
        }
    }

    /**
     * Checks whether this is a switch for the given package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @parameter ePackage the package in question.
     * @return whether this is a switch for the given package.
     * @generated
     */
    @Override
    protected boolean isSwitchFor(EPackage ePackage) {
        return ePackage == modelPackage;
    }

    /**
     * Calls <code>caseXXX</code> for each class of the model until one returns a non null result; it yields that result.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the first non-null result returned by a <code>caseXXX</code> call.
     * @generated
     */
    @Override
    protected T doSwitch(int classifierID, EObject theEObject) {
        switch (classifierID) {
        case AtomPackage.ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION: {
            AtomInternalExternalPortDeclaration atomInternalExternalPortDeclaration = (AtomInternalExternalPortDeclaration) theEObject;
            T result = caseAtomInternalExternalPortDeclaration(atomInternalExternalPortDeclaration);
            if (result == null)
                result = casePortDeclaration(atomInternalExternalPortDeclaration);
            if (result == null)
                result = caseAnnotatedElement(atomInternalExternalPortDeclaration);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case AtomPackage.ATOM_INTERNAL_PORT_DECLARATION: {
            AtomInternalPortDeclaration atomInternalPortDeclaration = (AtomInternalPortDeclaration) theEObject;
            T result = caseAtomInternalPortDeclaration(atomInternalPortDeclaration);
            if (result == null)
                result = caseAtomInternalExternalPortDeclaration(atomInternalPortDeclaration);
            if (result == null)
                result = casePortDeclaration(atomInternalPortDeclaration);
            if (result == null)
                result = caseAnnotatedElement(atomInternalPortDeclaration);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case AtomPackage.ATOM_EXTERNAL_PORT_DECLARATION: {
            AtomExternalPortDeclaration atomExternalPortDeclaration = (AtomExternalPortDeclaration) theEObject;
            T result = caseAtomExternalPortDeclaration(atomExternalPortDeclaration);
            if (result == null)
                result = caseAtomInternalExternalPortDeclaration(atomExternalPortDeclaration);
            if (result == null)
                result = casePortDeclaration(atomExternalPortDeclaration);
            if (result == null)
                result = caseAnnotatedElement(atomExternalPortDeclaration);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case AtomPackage.ATOM_INTERNAL_DATA_DECLARATION: {
            AtomInternalDataDeclaration atomInternalDataDeclaration = (AtomInternalDataDeclaration) theEObject;
            T result = caseAtomInternalDataDeclaration(atomInternalDataDeclaration);
            if (result == null)
                result = caseExplicitDataDeclaration(atomInternalDataDeclaration);
            if (result == null)
                result = caseDataDeclaration(atomInternalDataDeclaration);
            if (result == null)
                result = caseAnnotatedElement(atomInternalDataDeclaration);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case AtomPackage.ATOM_EXPORT_PORT_DECLARATION: {
            AtomExportPortDeclaration atomExportPortDeclaration = (AtomExportPortDeclaration) theEObject;
            T result = caseAtomExportPortDeclaration(atomExportPortDeclaration);
            if (result == null)
                result = casePortDeclaration(atomExportPortDeclaration);
            if (result == null)
                result = caseAnnotatedElement(atomExportPortDeclaration);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        default:
            return defaultCase(theEObject);
        }
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Internal External Port Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Internal External Port Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseAtomInternalExternalPortDeclaration(
            AtomInternalExternalPortDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Internal Port Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Internal Port Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseAtomInternalPortDeclaration(AtomInternalPortDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>External Port Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>External Port Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseAtomExternalPortDeclaration(AtomExternalPortDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Internal Data Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Internal Data Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseAtomInternalDataDeclaration(AtomInternalDataDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Export Port Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Export Port Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseAtomExportPortDeclaration(AtomExportPortDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T casePortDeclaration(PortDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseDataDeclaration(DataDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Explicit Data Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Explicit Data Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseExplicitDataDeclaration(ExplicitDataDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Annotated Element</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Annotated Element</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseAnnotatedElement(AnnotatedElement object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>EObject</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch, but this is the last case anyway.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>EObject</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject)
     * @generated
     */
    @Override
    public T defaultCase(EObject object) {
        return null;
    }

} //AtomSwitch
