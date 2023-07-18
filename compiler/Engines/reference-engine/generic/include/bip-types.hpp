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

#ifndef _BIP_Engine_bip_types_HPP_
#define _BIP_Engine_bip_types_HPP_

#include <iostream>

namespace biptypes {
    enum ComponentType {
        ATOM = 0,
        COMPOUND = 1
    };
    enum ExportType {
        ATOM_EXPORT = 0,
        COMPOUND_EXPORT = 1,
        CONNECTOR_EXPORT = 2
    };
    enum ErrorType {
        NO_ERROR = 0,
        NON_DETERMINISTIC_PETRI_NET = 1,
        NON_ONE_SAFE_PETRI_NET = 2,
        CYCLE_IN_PRIORITIES = 3,
        CYCLE_IN_ATOM_PRIORITIES = 4,
        ATOM_INVARIANT_VIOLATION = 5,
        UNEXPECTED_EVENT = 6,
        TIME_SAFETY_VIOLATION = 7
    };
    enum EventConsumptionPolicy {
        REMEMBER = 0,
        IGNORE = 1,
        ERROR = 2
    };
    enum TimeUnit {
        NONE = 0,
        NANOSECOND = 1,
        MICROSECOND = 2,
        MILLISECOND = 3,
        SECOND = 4,
        MINUTE = 5,
        HOUR = 6,
        DAY = 7
    };
    enum Urgency {
        LAZY = 0,
        DELAYABLE = 1,
        EAGER = 2,
    };
}

#endif // _BIP_Engine_bip_types_HPP_
