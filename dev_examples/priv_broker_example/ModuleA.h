/*****************************************************************************

  Licensed to Accellera Systems Initiative Inc. (Accellera) under one or
  more contributor license agreements.  See the NOTICE file distributed
  with this work for additional information regarding copyright ownership.
  Accellera licenses this file to you under the Apache License, Version 2.0
  (the "License"); you may not use this file except in compliance with the
  License.  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
  implied.  See the License for the specific language governing
  permissions and limitations under the License.

 ****************************************************************************/

/**
 * @file   ModuleA.h
 * @author Christian Schroeder, GreenSocs
 * @author Mark Burton, GreenSocs
 */

#ifndef __MODULEA_H__
#define __MODULEA_H__

#include <systemc>
#include "ex_globals.h"
#include "cci_configuration"

#ifndef SC_INCLUDE_DYNAMIC_PROCESSES
  #define SC_INCLUDE_DYNAMIC_PROCESSES
#endif
#include "gs_cci_cnf_private_broker_handle.h"

#include "ModuleB.h"

/// Module which owns some cci parameters.
class ModuleA
: public sc_core::sc_module
{
protected:
  /// for secure access by parameters
  cci::cci_broker_if& m_broker;

public:
  
  SC_HAS_PROCESS(ModuleA);
	
  /// Constructor
  ModuleA(sc_core::sc_module_name name, cci::cci_broker_if&);
  // Important: never use a private_broker_manager anywhere else than as constructor argument!!!
  
  /// Main action to make tests with parameters.
  void main_action();
  
  /// Example parameter.
  cci::cci_param<int>             int_param;
  /// Example parameter.
  cci::cci_param<unsigned int>    uint_param;
  /// Example parameter.
  cci::cci_param<unsigned int>    uint_param2;
  /// Example parameter.
  cci::cci_param<std::string>     str_param;
  /// Example parameter.
  cci::cci_param<bool>            bool_param;
  
protected:
  ModuleB m_modB;
};


#endif
