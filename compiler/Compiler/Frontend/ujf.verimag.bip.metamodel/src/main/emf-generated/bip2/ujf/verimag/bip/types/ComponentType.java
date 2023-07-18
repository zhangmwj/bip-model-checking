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

package bip2.ujf.verimag.bip.types;

import bip2.ujf.verimag.bip.component.ComponentDataParameterDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclaration;

import bip2.ujf.verimag.bip.port.PortDeclaration;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Component Type</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.types.ComponentType#getExportedPortDeclarations <em>Exported Port Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.ComponentType#getExportedDataDeclarations <em>Exported Data Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.ComponentType#getDataParameterDeclarations <em>Data Parameter Declarations</em>}</li>
 * </ul>
 * </p>
 *
 * @see bip2.ujf.verimag.bip.types.TypesPackage#getComponentType()
 * @model interface="true" abstract="true"
 * @generated
 */
public interface ComponentType extends BipType {
    /**
     * Returns the value of the '<em><b>Exported Port Declarations</b></em>' reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.port.PortDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Exported Port Declarations</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Exported Port Declarations</em>' reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getComponentType_ExportedPortDeclarations()
     * @model
     * @generated
     */
    EList<PortDeclaration> getExportedPortDeclarations();

    /**
     * Returns the value of the '<em><b>Exported Data Declarations</b></em>' reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.data.DataDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Exported Data Declarations</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Exported Data Declarations</em>' reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getComponentType_ExportedDataDeclarations()
     * @model
     * @generated
     */
    EList<DataDeclaration> getExportedDataDeclarations();

    /**
     * Returns the value of the '<em><b>Data Parameter Declarations</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.component.ComponentDataParameterDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Data Parameter Declarations</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Data Parameter Declarations</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getComponentType_DataParameterDeclarations()
     * @model containment="true"
     * @generated
     */
    EList<ComponentDataParameterDeclaration> getDataParameterDeclarations();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    PortDeclaration getExportedPortDeclaration(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    DataDeclaration getExportedDataDeclaration(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model nameRequired="true"
     * @generated
     */
    ComponentDataParameterDeclaration getDataParameterDeclaration(String name);

} // ComponentType
