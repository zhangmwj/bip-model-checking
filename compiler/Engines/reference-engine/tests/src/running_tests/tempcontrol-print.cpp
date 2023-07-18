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

#include "tempcontrol-print.hpp"
#include <iostream>
#include <iomanip>
#include <string>

std::string print_position (int pos) {
  switch (pos) {
  case 0:
    return std::string("down");
  case 1:
    return std::string("rest");
  case 2:
    return std::string("ready");
  default:
    return std::string("ERROR!");
  }
}

std::string print_command (int cmd) {
  switch (cmd) {
  case 0:
    return std::string("up");
  case 1:
    return std::string("down");
  case 2:
    return std::string("Shutdown!");
  default:
    return std::string("ERROR!");    
  }
}

void print(const std::string &s) {
  std::cout << s;
}

void print(int i, int j, const std::string &s1, const std::string &s2, const std::string &s3, const std::string &s4) {
  
  std::cout << std::setw(6) << i << std::setw(12) << j << std::setw(8) << s1 << std::setw(8) << s2 << std::setw(12) << s3 << std::setw(12) << s4 << std::endl;
}

