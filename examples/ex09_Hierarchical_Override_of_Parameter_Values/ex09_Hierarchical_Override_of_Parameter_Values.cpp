/*****************************************************************************
  Copyright 2006-2014 Accellera Systems Initiative Inc.
  All rights reserved.

  Copyright 2010-2015 CircuitSutra Technologies Pvt. Ltd.
  All rights reserved.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 *****************************************************************************/

#ifndef SC_INCLUDE_DYNAMIC_PROCESSES
  #define SC_INCLUDE_DYNAMIC_PROCESSES
#endif

/**
 *  @file     main.cpp
 *  @brief    Testbench file
 *            This file declares and implements the functionality of the target.
 *            Few of the parameters of the target sc_module are configured by the
 *            router sc_module.
 *  @author   P V S Phaneendra, CircuitSutra Technologies   <pvs@circuitsutra.com>
 *  @date     29th April, 2011 (Friday)
 */

#include <cci_configuration>
#include <cassert>
#include <string>
#include "ex09_top_module.h"

/**
 *  @fn     int sc_main(int argc, char* argv[])
 *  @brief  The testbench for the hierarchical override of parameter values example
 *  @param  argc  The number of input arguments
 *  @param  argv  The list of input arguments
 *  @return An integer for the execution status
 */
int sc_main(int sc_argc, char* sc_argv[]) {
  // Instantiating originator to get access to the global broker
  std::string myString = "sc_main_originator";
  cci::cci_originator myOriginator(myString);

  // Get handle to the default broker
  cci::cci_broker_if* myGlobalBroker =
      &cci::cci_broker_manager::get_current_broker(myOriginator);

  // Assert if broker handle returned is NULL
  assert(myGlobalBroker != NULL
         && "Handle of the returned global broker is NULL");

  SC_REPORT_INFO("sc_main",
                 "[MAIN] : Setting initial value of the number of initiators"
                 " to 2");

  // Set initial value to the number of initiator(s) (within top_module)
  std::string initiatorHierarchicalName = "top_module_inst.number_of_initiators";
  myGlobalBroker->set_initial_cci_value(initiatorHierarchicalName,
                                        cci::cci_value::from_json("2"));

  SC_REPORT_INFO("sc_main", "[MAIN] : Setting initial value of the number"
                 " of initiators to 1");

  // The program considers only the last set initial value
  myGlobalBroker->set_initial_cci_value(initiatorHierarchicalName,
                                        cci::cci_value::from_json("1"));

  SC_REPORT_INFO("sc_main",
                 "[MAIN] : Setting initial value of the number of targets to 4");

  // Set initial value to the number of target(s) (within top_module)
  std::string targetHierarchicalName = "top_module_inst.number_of_targets";
  myGlobalBroker->set_initial_cci_value(targetHierarchicalName,
                                        cci::cci_value::from_json("4"));

  // Set the maximum addressing limit for the router
  myGlobalBroker->set_initial_cci_value(
      "top_module_inst.RouterInstance.addr_max",
      cci::cci_value::from_json("1024"));

  // Set and lock the Router Table initials values for target_1
  //  These values have again been tried to set within the Top_MODULE
  //  @see top_module.h
  SC_REPORT_INFO("sc_main",
                 "[MAIN] : Set and lock Router Table target_1 contents");
  myGlobalBroker->set_initial_cci_value(
      "top_module_inst.RouterInstance.r_index_1",
      cci::cci_value::from_json("1"));
  myGlobalBroker->lock_initial_value(
      "top_module_inst.RouterInstance.r_index_1");

  SC_REPORT_INFO("sc_main",
                 "[MAIN] : Set and lock Router Table Start Address for target_1"
                 " to 128");
  myGlobalBroker->set_initial_cci_value(
      "top_module_inst.RouterInstance.r_sa_1",
      cci::cci_value::from_json("128"));
  myGlobalBroker->lock_initial_value("top_module_inst.RouterInstance.r_sa_1");

  SC_REPORT_INFO("sc_main",
                 "[MAIN] : Set and lock Router Table End Address for target_1"
                 " to 255");
  myGlobalBroker->set_initial_cci_value(
      "top_module_inst.RouterInstance.r_ea_1",
      cci::cci_value::from_json("255"));
  myGlobalBroker->lock_initial_value("top_module_inst.RouterInstance.r_ea_1");

  SC_REPORT_INFO("sc_main",
                 "[MAIN] : Instantiate top module after setting initial"
                 " values to top_module, router and target parameters");

  // Instantiate TOP_MODULE responsible for creating the model hierarchy
  ex09_top_module top_mod("top_module_inst");

  // Start the simulation
  sc_core::sc_start(1140, sc_core::SC_NS);

  return EXIT_SUCCESS;
}  // End of 'sc_main'
