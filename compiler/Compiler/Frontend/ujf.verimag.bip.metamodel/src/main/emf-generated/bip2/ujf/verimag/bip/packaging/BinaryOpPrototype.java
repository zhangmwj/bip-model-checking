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

package bip2.ujf.verimag.bip.packaging;

import bip2.ujf.verimag.bip.actionlang.BinaryOperators;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Binary Op Prototype</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.BinaryOpPrototype#getOperator <em>Operator</em>}</li>
 * </ul>
 * </p>
 *
 * @see bip2.ujf.verimag.bip.packaging.PackagingPackage#getBinaryOpPrototype()
 * @model
 * @generated
 */
public interface BinaryOpPrototype extends Prototype {
    /**
     * Returns the value of the '<em><b>Operator</b></em>' attribute.
     * The literals are from the enumeration {@link bip2.ujf.verimag.bip.actionlang.BinaryOperators}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Operator</em>' attribute isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Operator</em>' attribute.
     * @see bip2.ujf.verimag.bip.actionlang.BinaryOperators
     * @see #setOperator(BinaryOperators)
     * @see bip2.ujf.verimag.bip.packaging.PackagingPackage#getBinaryOpPrototype_Operator()
     * @model required="true"
     * @generated
     */
    BinaryOperators getOperator();

    /**
     * Sets the value of the '{@link bip2.ujf.verimag.bip.packaging.BinaryOpPrototype#getOperator <em>Operator</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Operator</em>' attribute.
     * @see bip2.ujf.verimag.bip.actionlang.BinaryOperators
     * @see #getOperator()
     * @generated
     */
    void setOperator(BinaryOperators value);

} // BinaryOpPrototype
