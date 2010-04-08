// LICENSETEXT
//
//   Copyright (C) 2009 : GreenSocs Ltd
// 	 http://www.greensocs.com/ , email: info@greensocs.com
//
//   Developed by:
//    Christian Schroeder <schroeder@eis.cs.tu-bs.de>,
//    Mark Burton, mark@greensocs.com
//
//
//   This program is free software.
// 
//   If you have no applicable agreement with GreenSocs Ltd, this software
//   is licensed to you, and you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
// 
//   If you have a applicable agreement with GreenSocs Ltd, the terms of that
//   agreement prevail.
// 
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// 
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
//   02110-1301  USA 
// 
// ENDLICENSETEXT


#ifndef __GS_CCI_VALUE_H__
#define __GS_CCI_VALUE_H__


#ifndef __INCLUDE_ONLY_FROM_MAIN_INCLUDE_CHECK__
#error "failed include check"
#else
#undef __INCLUDE_ONLY_FROM_MAIN_INCLUDE_CHECK__
#endif


inline cci::cnf::cci_value::cci_value() 
: m_type(partype_not_available) {
}
      
inline cci::cnf::cci_value::cci_value(const char* value) 
: m_type(partype_string) 
, m_value_string(value) {
}

inline cci::cnf::cci_value::cci_value(const std::string& value)
: m_type(partype_string)
, m_value_string(value) {
}

inline cci::cnf::cci_value::cci_value(bool value) 
: m_type(partype_bool) 
, m_value_bool(value) {
}

inline cci::cnf::cci_value::cci_value(int value)
: m_type(partype_number)
, m_value_number(value) {
}

inline cci::cnf::cci_value::cci_value(boost::int64_t value)
: m_type(partype_number)
, m_value_number(value) {
}

inline cci::cnf::cci_value::cci_value(double value)
: m_type(partype_real)
, m_value_real(value) {
}

inline cci::cnf::cci_value::cci_value(const cci_value_list& value) 
: m_type(partype_list)
, m_value_list(value) {
}

inline cci::cnf::cci_value::cci_value(const cci::cnf::cci_value& other) {
  operator=(other);
}

inline bool cci::cnf::cci_value::operator==(const cci::cnf::cci_value& lhs) const {
  if (lhs.type() != type()) return false;
  switch(lhs.type()) {
    case cci::cnf::partype_not_available:
      return true;
      break;
    case cci::cnf::partype_number:
      return (lhs.get_int64() == get_int64());
      break;
    case cci::cnf::partype_real:
      return (lhs.get_real() == get_real());
      break;
    case cci::cnf::partype_bool:
      return (lhs.get_bool() == get_bool());
      break;
    case cci::cnf::partype_string:
      return (lhs.get_string() == get_string());
      break;
    case cci::cnf::partype_list:
      return (lhs.get_list() == get_list());
      break;
    case cci::cnf::partype_other:
      CCI_THROW_ERROR(cci::cnf::cci_report_types::type().cci_value_failure, "not implemented");
      break;
    default:
      assert(false && "This should never happen!");
      CCI_THROW_ERROR(cci::cnf::cci_report_types::type().cci_value_failure, "not implemented");
  }
  return false;
}

inline cci::cnf::cci_value& cci::cnf::cci_value::operator=(const cci::cnf::cci_value& lhs) {
  m_type = lhs.type();
  switch(lhs.type()) {
    case cci::cnf::partype_not_available:
      break;
    case cci::cnf::partype_number:
      m_value_number = lhs.get_int64();
      break;
    case cci::cnf::partype_real:
      m_value_real = lhs.get_real();
      break;
    case cci::cnf::partype_bool:
      m_value_bool = lhs.get_bool();
      break;
    case cci::cnf::partype_string:
      m_value_string = lhs.get_string();
      break;
    case cci::cnf::partype_list:
      m_value_list = lhs.get_list();
      break;
    case cci::cnf::partype_other:
      CCI_THROW_ERROR(cci::cnf::cci_report_types::type().cci_value_failure, "Not implemented.");
      break;
    default:
      assert(false && "This should never happen!");
      CCI_THROW_ERROR(cci::cnf::cci_report_types::type().cci_value_failure, "Not implemented.");
  }
  return *this;
}

inline cci::cnf::basic_param_type cci::cnf::cci_value::type() const { return m_type; }

inline const std::string&      cci::cnf::cci_value::get_string()   const {
  if (m_type != cci::cnf::partype_string)
    CCI_THROW_ERROR(cci::cnf::cci_report_types::type().cci_value_failure, "Wrong cci value type (no string).");
  return m_value_string;
}

inline const cci::cnf::cci_value_list&   cci::cnf::cci_value::get_list() const {
  if (m_type != cci::cnf::partype_list)
    CCI_THROW_ERROR(cci::cnf::cci_report_types::type().cci_value_failure, "Wrong cci value type (no list).");
  return m_value_list;
}

inline bool cci::cnf::cci_value::get_bool()  const {
  if (m_type != cci::cnf::partype_bool)
    CCI_THROW_ERROR(cci::cnf::cci_report_types::type().cci_value_failure, "Wrong cci value type (no bool).");
  return m_value_bool;
}

inline int cci::cnf::cci_value::get_int()   const {
  if (m_type != cci::cnf::partype_number)
    CCI_THROW_ERROR(cci::cnf::cci_report_types::type().cci_value_failure, "Wrong cci value type (no number).");
  if (m_value_number > INT_MAX || m_value_number < INT_MIN)
    CCI_THROW_WARNING(cci::cnf::cci_report_types::type().cci_value_failure, "Overflow cci value (number is larger than int can hold).");
  return static_cast<int>(m_value_number);
}

inline sc_dt::int64 cci::cnf::cci_value::get_int64() const {
  if (m_type != cci::cnf::partype_number)
    CCI_THROW_ERROR(cci::cnf::cci_report_types::type().cci_value_failure, "Wrong cci value type (no number).");
  return m_value_number;
}

inline double cci::cnf::cci_value::get_real()  const {
  if (m_type != cci::cnf::partype_real)
    CCI_THROW_ERROR(cci::cnf::cci_report_types::type().cci_value_failure, "Wrong cci value type (no real).");
  return m_value_real;
}

namespace cci {

  /// Value class for objects representing arbitrary types of cci parameters
  /**
   *
   */
  /*
   class gs_cci_value 
  : public cci_value {
  public:
    gs_cci_value() 
    : my_type(partype_not_available) {
    }
    
    gs_cci_value(const char*           value) 
    : my_type(partype_string) 
    , m_value_string(value) {
    }
    
    gs_cci_value(const std::string&    value)
    : my_type(partype_string)
    , m_value_string(value) {
    }
    
    gs_cci_value(bool                  value) 
    : my_type(partype_bool) 
    , m_value_bool(value) {
    }
    
    gs_cci_value(int                   value)
    : my_type(partype_number)
    , m_value_number(value) {
    }
    
    gs_cci_value(sc_dt::int64          value)
    : my_type(partype_number)
    , m_value_number(value) {
    }
    
    gs_cci_value(double                value)
    : my_type(partype_real)
    , m_value_real(value) {
    }
    
    gs_cci_value(const cci_value_list& value) 
    : my_type(partype_list)
    , m_value_list(value) {
    }
    
    gs_cci_value(const cci_value& other) {
      operator=(other);
    }
    
    gs_cci_value(const gs_cci_value& other) {
      operator=(other);
    }
    
    bool operator==(const cci_value& lhs) const {
      if (lhs.type() != type()) return false;
      switch(lhs.type()) {
        case partype_not_available:
          return true;
          break;
        case partype_number:
          return (lhs.get_int64() == get_int64());
          break;
        case partype_real:
          return (lhs.get_real() == get_real());
          break;
        case partype_bool:
          return (lhs.get_bool() == get_bool());
          break;
        case partype_string:
          return (lhs.get_string() == get_string());
          break;
        case partype_list:
          return (lhs.get_list() == get_list());
          break;
        case partype_other:
          throw_error(cci_report_types::type().cci_value_failure, "not implemented");
          break;
        default:
          assert(false && "This should never happen!");
          throw_error(cci_report_types::type().cci_value_failure, "not implemented");
      }
    }
    
    cci_value& operator=(const cci_value& lhs) {
      my_type = lhs.type();
      switch(lhs.type()) {
        case partype_not_available:
          break;
        case partype_number:
          m_value_number = lhs.get_int64();
          break;
        case partype_real:
          m_value_real = lhs.get_real();
          break;
        case partype_bool:
          m_value_bool = lhs.get_bool();
          break;
        case partype_string:
          m_value_string = lhs.get_string();
          break;
        case partype_list:
          m_value_list = lhs.get_list();
          break;
        case partype_other:
          throw_error(cci_report_types::type().cci_value_failure, "Not implemented.");
          break;
        default:
          assert(false && "This should never happen!");
          throw_error(cci_report_types::type().cci_value_failure, "Not implemented.");
      }
    }
    
    basic_param_type type() const { return my_type; }
    
    const std::string&      get_string()   const {
      if (my_type != partype_string)
        throw_error(cci_report_types::type().cci_value_failure, "Wrong cci value type (no string).");
      return m_value_string;
    }
    
    const cci_value_list&   get_list() const {
      if (my_type != partype_list)
        throw_error(cci_report_types::type().cci_value_failure, "Wrong cci value type (no list).");
      return m_value_list;
    }
    
    bool get_bool()  const {
      if (my_type != partype_bool)
        throw_error(cci_report_types::type().cci_value_failure, "Wrong cci value type (no bool).");
      return m_value_bool;
    }
    
    int get_int()   const {
      if (my_type != partype_number)
        throw_error(cci_report_types::type().cci_value_failure, "Wrong cci value type (no number).");
      if (m_value_number > INT_MAX || m_value_number < INT_MIN)
        throw_warning(cci_report_types::type().cci_value_failure, "Overflow cci value (number is larger than int can hold).");
      return static_cast<int>(m_value_number);
    }
    
    sc_dt::int64 get_int64() const {
      if (my_type != partype_number)
        throw_error(cci_report_types::type().cci_value_failure, "Wrong cci value type (no number).");
      return m_value_number;
    }
    
    double get_real()  const {
      if (my_type != partype_real)
        throw_error(cci_report_types::type().cci_value_failure, "Wrong cci value type (no real).");
      return m_value_real;
    }
    
  protected:
    basic_param_type my_type;

    std::string m_value_string;
    bool m_value_bool;
    sc_dt::int64 m_value_number;
    double m_value_real;
    cci_value_list m_value_list;
    
  };
   */
  
} // end namespace cci




#endif