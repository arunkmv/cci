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
 * @file   test_datatype_without_parameter_implementation.h
 * @author Christian Schroeder, GreenSocs
 */

#ifndef __test_datatype_without_parameter_implementation_h__
#define __test_datatype_without_parameter_implementation_h__

/// Test struct to be used for testing/demonstrating not implemented cci_value conversions
struct test_datatype_without_parameter_implementation {
  std::string strVal;
};

inline std::istream& operator >>(std::istream &is,test_datatype_without_parameter_implementation &obj)
{
  is>>obj.strVal;
  return is;
}
inline std::ostream& operator <<(std::ostream &os,const test_datatype_without_parameter_implementation &obj)
{
  os<<obj.strVal;
  return os;
}
inline bool operator==(test_datatype_without_parameter_implementation const& lhs, test_datatype_without_parameter_implementation const& rhs) {
  return lhs.strVal.compare(rhs.strVal);
}

namespace cci {
template<>
struct cci_value_traits< test_datatype_without_parameter_implementation >
{
  typedef test_datatype_without_parameter_implementation type;
  static bool pack( cci_value::reference dst, type const & src )
  {
    dst.set_string( src.strVal );
    return true;
  }
  static bool unpack( type & dst, cci_value::const_reference src )
  {
    if( !src.is_string() )
      return false;

    dst.strVal = src.get_string();
    return true;
  }

};
} /* namespace cci */

#endif