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

package bip2.ujf.verimag.bip.annotation.impl;

import bip2.ujf.verimag.bip.annotation.AnnotatedElement;
import bip2.ujf.verimag.bip.annotation.AnnotationPackage;
import bip2.ujf.verimag.bip.annotation.BipAnnotation;

import java.util.Collection;

import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.EMap;
import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EStructuralFeature;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.util.EcoreEMap;
import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.InternalEList;

import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Annotated Element</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.annotation.impl.AnnotatedElementImpl#getBipAnnotations <em>Bip Annotations</em>}</li>
 * </ul>
 *
 * @generated
 */
public abstract class AnnotatedElementImpl extends AnnotatedEObjectImpl
        implements AnnotatedElement {
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
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected AnnotatedElementImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return AnnotationPackage.Literals.ANNOTATED_ELEMENT;
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
                    AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS);
        }
        return bipAnnotations;
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
        case AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS:
            return ((InternalEList<?>) getBipAnnotations())
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
        case AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS:
            if (coreType)
                return getBipAnnotations();
            else
                return getBipAnnotations().map();
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
        case AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS:
            ((EStructuralFeature.Setting) getBipAnnotations()).set(newValue);
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
        case AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS:
            getBipAnnotations().clear();
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
        case AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS:
            return bipAnnotations != null && !bipAnnotations.isEmpty();
        }
        return super.eIsSet(featureID);
    }

} //AnnotatedElementImpl
