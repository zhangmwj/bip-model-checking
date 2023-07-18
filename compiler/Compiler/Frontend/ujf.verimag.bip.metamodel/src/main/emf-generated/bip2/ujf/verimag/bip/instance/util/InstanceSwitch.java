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

package bip2.ujf.verimag.bip.instance.util;

import bip2.ujf.verimag.bip.instance.*;

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
 * @see bip2.ujf.verimag.bip.instance.InstancePackage
 * @generated
 */
public class InstanceSwitch<T> extends Switch<T> {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected static InstancePackage modelPackage;

    /**
     * Creates an instance of the switch.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public InstanceSwitch() {
        if (modelPackage == null) {
            modelPackage = InstancePackage.eINSTANCE;
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
        case InstancePackage.CONNECTOR_INSTANCE: {
            ConnectorInstance connectorInstance = (ConnectorInstance) theEObject;
            T result = caseConnectorInstance(connectorInstance);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case InstancePackage.DATA_INSTANCE: {
            DataInstance dataInstance = (DataInstance) theEObject;
            T result = caseDataInstance(dataInstance);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE: {
            CompoundPriorityInstance compoundPriorityInstance = (CompoundPriorityInstance) theEObject;
            T result = caseCompoundPriorityInstance(compoundPriorityInstance);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case InstancePackage.ATOM_INSTANCE: {
            AtomInstance atomInstance = (AtomInstance) theEObject;
            T result = caseAtomInstance(atomInstance);
            if (result == null)
                result = caseComponentInstance(atomInstance);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case InstancePackage.COMPOUND_INSTANCE: {
            CompoundInstance compoundInstance = (CompoundInstance) theEObject;
            T result = caseCompoundInstance(compoundInstance);
            if (result == null)
                result = caseComponentInstance(compoundInstance);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case InstancePackage.COMPONENT_INSTANCE: {
            ComponentInstance componentInstance = (ComponentInstance) theEObject;
            T result = caseComponentInstance(componentInstance);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case InstancePackage.PORT_INSTANCE: {
            PortInstance portInstance = (PortInstance) theEObject;
            T result = casePortInstance(portInstance);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case InstancePackage.EXPORTED_PORT_INSTANCE: {
            ExportedPortInstance exportedPortInstance = (ExportedPortInstance) theEObject;
            T result = caseExportedPortInstance(exportedPortInstance);
            if (result == null)
                result = casePortInstance(exportedPortInstance);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case InstancePackage.ATOM_INTERNAL_PORT_INSTANCE: {
            AtomInternalPortInstance atomInternalPortInstance = (AtomInternalPortInstance) theEObject;
            T result = caseAtomInternalPortInstance(atomInternalPortInstance);
            if (result == null)
                result = casePortInstance(atomInternalPortInstance);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case InstancePackage.ATOM_EXTERNAL_PORT_INSTANCE: {
            AtomExternalPortInstance atomExternalPortInstance = (AtomExternalPortInstance) theEObject;
            T result = caseAtomExternalPortInstance(atomExternalPortInstance);
            if (result == null)
                result = casePortInstance(atomExternalPortInstance);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case InstancePackage.CONNECTOR_PORT_INSTANCE: {
            ConnectorPortInstance connectorPortInstance = (ConnectorPortInstance) theEObject;
            T result = caseConnectorPortInstance(connectorPortInstance);
            if (result == null)
                result = casePortInstance(connectorPortInstance);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        default:
            return defaultCase(theEObject);
        }
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Component Instance</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Component Instance</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseComponentInstance(ComponentInstance object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Connector Instance</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Connector Instance</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseConnectorInstance(ConnectorInstance object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Port Instance</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Port Instance</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T casePortInstance(PortInstance object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Exported Port Instance</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Exported Port Instance</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseExportedPortInstance(ExportedPortInstance object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Atom Internal Port Instance</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Atom Internal Port Instance</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseAtomInternalPortInstance(AtomInternalPortInstance object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Atom External Port Instance</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Atom External Port Instance</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseAtomExternalPortInstance(AtomExternalPortInstance object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Connector Port Instance</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Connector Port Instance</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseConnectorPortInstance(ConnectorPortInstance object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Data Instance</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Data Instance</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseDataInstance(DataInstance object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Compound Priority Instance</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Compound Priority Instance</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseCompoundPriorityInstance(CompoundPriorityInstance object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Atom Instance</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Atom Instance</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseAtomInstance(AtomInstance object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Compound Instance</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Compound Instance</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseCompoundInstance(CompoundInstance object) {
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

} //InstanceSwitch
