/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2009 by all Contributors.
  All Rights reserved.

  Developed by GreenSocs : http://www.greensocs.com/
   Christian Schroeder, schroeder@eis.cs.tu-bs.de
   Mark Burton, mark@greensocs.com

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 3.0 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/


#include "ParamManipulateModule.h"
#include <systemc.h>


ParamManipulateModule::ParamManipulateModule(sc_core::sc_module_name name)
: sc_core::sc_module(name)
{ 
  mApi = cci::get_cnf_api_instance(this);
  SC_THREAD(main_action);
  
  mApi->set_init_value("Owner.int_param", "11");
  if (mApi->exists_param("Owner.int_param"))
    cout << "Owner.int_param exists (implicit or explicit)" << endl;
  else
    SC_REPORT_WARNING(name, "ERROR: Owner.int_param NOT exists!");
}


void ParamManipulateModule::main_action() {

  wait(10, SC_NS);
  
  cci::cci_base_param *int_param_ptr = mApi->get_param("Owner.int_param");
  if (int_param_ptr == NULL) return;
  cci::gs_cci_param<int> &int_param_p = *static_cast<cci::gs_cci_param<int>* >(int_param_ptr);

  cci::cci_base_param *uint_param_ptr = mApi->get_param("Owner.uint_param");
  if (uint_param_ptr == NULL) return;
  cci::gs_cci_param<unsigned int> &uint_param_p = *static_cast<cci::gs_cci_param<unsigned int>* >(uint_param_ptr);
  
  DEMO_DUMP(name(), "Set parameter Owner.int_param to value=5000");
  int_param_p.json_deserialize("5000");
  cout << endl;
  wait(SC_ZERO_TIME);
  
  DEMO_DUMP(name(), "Set parameter Owner.int_param to value=5001");
  int_param_p.set(5001);
  cout << endl;
  wait(SC_ZERO_TIME);
  
  DEMO_DUMP(name(), "Set parameter Owner.int_param to value=5002");
  int_param_p = 5002;
  cout << endl;
  wait(SC_ZERO_TIME);

  DEMO_DUMP(name(), "Set parameter Owner.uint_param to value=9000");
  uint_param_p = 9000;
  cout << endl;
  wait(SC_ZERO_TIME);
  
  /*DEMO_DUMP(name(), "Set parameter Owner.str_param to value=\"SHOW THIS\"");
  pu = "SHOW THIS";
  cout << endl;
  wait(SC_ZERO_TIME);*/

}