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

package bip2.ujf.verimag.bip.time.impl;

import bip2.ujf.verimag.bip.time.*;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EDataType;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.impl.EFactoryImpl;

import org.eclipse.emf.ecore.plugin.EcorePlugin;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Factory</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class TimeFactoryImpl extends EFactoryImpl implements TimeFactory {
    /**
     * Creates the default factory implementation.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static TimeFactory init() {
        try {
            TimeFactory theTimeFactory = (TimeFactory) EPackage.Registry.INSTANCE
                    .getEFactory("http://bip2/ujf/verimag/bip/time/1.0");
            if (theTimeFactory != null) {
                return theTimeFactory;
            }
        } catch (Exception exception) {
            EcorePlugin.INSTANCE.log(exception);
        }
        return new TimeFactoryImpl();
    }

    /**
     * Creates an instance of the factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public TimeFactoryImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EObject create(EClass eClass) {
        switch (eClass.getClassifierID()) {
        case TimePackage.CLOCK_DECLARATION:
            return (EObject) createClockDeclaration();
        case TimePackage.TIME:
            return (EObject) createTime();
        case TimePackage.GUARDED_UNTIMED:
            return (EObject) createGuardedUntimed();
        case TimePackage.RESUMED:
            return (EObject) createResumed();
        case TimePackage.RESUME:
            return (EObject) createResume();
        default:
            throw new IllegalArgumentException("The class '" + eClass.getName()
                    + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object createFromString(EDataType eDataType, String initialValue) {
        switch (eDataType.getClassifierID()) {
        case TimePackage.URGENCY:
            return createUrgencyFromString(eDataType, initialValue);
        default:
            throw new IllegalArgumentException("The datatype '"
                    + eDataType.getName() + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public String convertToString(EDataType eDataType, Object instanceValue) {
        switch (eDataType.getClassifierID()) {
        case TimePackage.URGENCY:
            return convertUrgencyToString(eDataType, instanceValue);
        default:
            throw new IllegalArgumentException("The datatype '"
                    + eDataType.getName() + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ClockDeclaration createClockDeclaration() {
        ClockDeclarationImpl clockDeclaration = new ClockDeclarationImpl();
        return clockDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Time createTime() {
        TimeImpl time = new TimeImpl();
        return time;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public GuardedUntimed createGuardedUntimed() {
        GuardedUntimedImpl guardedUntimed = new GuardedUntimedImpl();
        return guardedUntimed;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Resumed createResumed() {
        ResumedImpl resumed = new ResumedImpl();
        return resumed;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Resume createResume() {
        ResumeImpl resume = new ResumeImpl();
        return resume;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Urgency createUrgencyFromString(EDataType eDataType,
            String initialValue) {
        Urgency result = Urgency.get(initialValue);
        if (result == null)
            throw new IllegalArgumentException("The value '" + initialValue
                    + "' is not a valid enumerator of '" + eDataType.getName()
                    + "'");
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String convertUrgencyToString(EDataType eDataType,
            Object instanceValue) {
        return instanceValue == null ? null : instanceValue.toString();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public TimePackage getTimePackage() {
        return (TimePackage) getEPackage();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @deprecated
     * @generated
     */
    @Deprecated
    public static TimePackage getPackage() {
        return TimePackage.eINSTANCE;
    }

} //TimeFactoryImpl
