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

package bip2.ujf.verimag.bip.actionlang;

import bip2.ujf.verimag.bip.data.SubDataDeclarationReference;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Sub Data Declaration Reference Expression</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression#getSubDataDeclarationRef <em>Sub Data Declaration Ref</em>}</li>
 * </ul>
 *
 * @see bip2.ujf.verimag.bip.actionlang.ActionlangPackage#getSubDataDeclarationReferenceExpression()
 * @model annotation="http://www.eclipse.org/emf/2002/Ecore constraints='dataIsExportedInComponent dataRefInConnectorActionToInvolvedPort'"
 * @generated
 */
public interface SubDataDeclarationReferenceExpression
        extends ValuedExpression {
    /**
     * Returns the value of the '<em><b>Sub Data Declaration Ref</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Sub Data Declaration Ref</em>' containment reference isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Sub Data Declaration Ref</em>' containment reference.
     * @see #setSubDataDeclarationRef(SubDataDeclarationReference)
     * @see bip2.ujf.verimag.bip.actionlang.ActionlangPackage#getSubDataDeclarationReferenceExpression_SubDataDeclarationRef()
     * @model containment="true" required="true"
     * @generated
     */
    SubDataDeclarationReference getSubDataDeclarationRef();

    /**
     * Sets the value of the '{@link bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression#getSubDataDeclarationRef <em>Sub Data Declaration Ref</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Sub Data Declaration Ref</em>' containment reference.
     * @see #getSubDataDeclarationRef()
     * @generated
     */
    void setSubDataDeclarationRef(SubDataDeclarationReference value);

} // SubDataDeclarationReferenceExpression
