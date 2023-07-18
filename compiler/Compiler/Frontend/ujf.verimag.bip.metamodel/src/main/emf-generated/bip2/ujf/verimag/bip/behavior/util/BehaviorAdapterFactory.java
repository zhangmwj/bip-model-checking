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

package bip2.ujf.verimag.bip.behavior.util;

import bip2.ujf.verimag.bip.annotation.AnnotatedElement;
import bip2.ujf.verimag.bip.behavior.*;

import bip2.ujf.verimag.bip.time.Guarded;
import bip2.ujf.verimag.bip.time.GuardedUntimed;
import bip2.ujf.verimag.bip.time.Resumed;
import bip2.ujf.verimag.bip.time.UrgentElement;
import org.eclipse.emf.common.notify.Adapter;
import org.eclipse.emf.common.notify.Notifier;

import org.eclipse.emf.common.notify.impl.AdapterFactoryImpl;

import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * The <b>Adapter Factory</b> for the model.
 * It provides an adapter <code>createXXX</code> method for each class of the model.
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.behavior.BehaviorPackage
 * @generated
 */
public class BehaviorAdapterFactory extends AdapterFactoryImpl {
    /**
     * The cached model package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected static BehaviorPackage modelPackage;

    /**
     * Creates an instance of the adapter factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public BehaviorAdapterFactory() {
        if (modelPackage == null) {
            modelPackage = BehaviorPackage.eINSTANCE;
        }
    }

    /**
     * Returns whether this factory is applicable for the type of the object.
     * <!-- begin-user-doc -->
     * This implementation returns <code>true</code> if the object is either the model's package or is an instance object of the model.
     * <!-- end-user-doc -->
     * @return whether this factory is applicable for the type of the object.
     * @generated
     */
    @Override
    public boolean isFactoryForType(Object object) {
        if (object == modelPackage) {
            return true;
        }
        if (object instanceof EObject) {
            return ((EObject) object).eClass().getEPackage() == modelPackage;
        }
        return false;
    }

    /**
     * The switch that delegates to the <code>createXXX</code> methods.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected BehaviorSwitch<Adapter> modelSwitch = new BehaviorSwitch<Adapter>() {
        @Override
        public Adapter casePetriNet(PetriNet object) {
            return createPetriNetAdapter();
        }

        @Override
        public Adapter caseState(State object) {
            return createStateAdapter();
        }

        @Override
        public Adapter caseTransition(Transition object) {
            return createTransitionAdapter();
        }

        @Override
        public Adapter caseInternalTransition(InternalTransition object) {
            return createInternalTransitionAdapter();
        }

        @Override
        public Adapter caseAnnotatedElement(AnnotatedElement object) {
            return createAnnotatedElementAdapter();
        }

        @Override
        public Adapter caseGuarded(Guarded object) {
            return createGuardedAdapter();
        }

        @Override
        public Adapter caseResumed(Resumed object) {
            return createResumedAdapter();
        }

        @Override
        public Adapter caseUrgentElement(UrgentElement object) {
            return createUrgentElementAdapter();
        }

        @Override
        public Adapter caseGuardedUntimed(GuardedUntimed object) {
            return createGuardedUntimedAdapter();
        }

        @Override
        public Adapter defaultCase(EObject object) {
            return createEObjectAdapter();
        }
    };

    /**
     * Creates an adapter for the <code>target</code>.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param target the object to adapt.
     * @return the adapter for the <code>target</code>.
     * @generated
     */
    @Override
    public Adapter createAdapter(Notifier target) {
        return modelSwitch.doSwitch((EObject) target);
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.behavior.PetriNet <em>Petri Net</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.behavior.PetriNet
     * @generated
     */
    public Adapter createPetriNetAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.behavior.State <em>State</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.behavior.State
     * @generated
     */
    public Adapter createStateAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.behavior.Transition <em>Transition</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.behavior.Transition
     * @generated
     */
    public Adapter createTransitionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.behavior.InternalTransition <em>Internal Transition</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.behavior.InternalTransition
     * @generated
     */
    public Adapter createInternalTransitionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.annotation.AnnotatedElement <em>Annotated Element</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.annotation.AnnotatedElement
     * @generated
     */
    public Adapter createAnnotatedElementAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.time.Guarded <em>Guarded</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.time.Guarded
     * @generated
     */
    public Adapter createGuardedAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.time.Resumed <em>Resumed</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.time.Resumed
     * @generated
     */
    public Adapter createResumedAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.time.UrgentElement <em>Urgent Element</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.time.UrgentElement
     * @generated
     */
    public Adapter createUrgentElementAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.time.GuardedUntimed <em>Guarded Untimed</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.time.GuardedUntimed
     * @generated
     */
    public Adapter createGuardedUntimedAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for the default case.
     * <!-- begin-user-doc -->
     * This default implementation returns null.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @generated
     */
    public Adapter createEObjectAdapter() {
        return null;
    }

} //BehaviorAdapterFactory
