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
 * @author Enrico Galli, Intel
 */

#include "cci_cfg/cci_param_untyped_handle.h"
#include "cci_cfg/cci_broker_manager.h"
#include "cci_cfg/cci_report_handler.h"
#include "cci_core/cci_name_gen.h"

CCI_OPEN_NAMESPACE_

cci_param_untyped_handle::cci_param_untyped_handle(
        cci_param_if & orig_param,
        const cci_originator & originator)
        : m_originator(originator), m_orig_param(&orig_param),
          m_orig_param_name(cci_get_name(orig_param.get_name().c_str()))
{
    m_orig_param->add_param_handle(this);
}

cci_param_untyped_handle::cci_param_untyped_handle(
        const cci_originator & originator)
        : m_originator(originator), m_orig_param(NULL), m_orig_param_name(NULL)
{}

cci_param_untyped_handle::cci_param_untyped_handle(
        const cci_param_untyped_handle& param_handle)
        : m_originator(param_handle.m_originator),
          m_orig_param(param_handle.m_orig_param),
          m_orig_param_name(param_handle.m_orig_param_name)
{
    if(is_valid()) {
        m_orig_param->add_param_handle(this);
    }
}

cci_param_untyped_handle::~cci_param_untyped_handle()
{
    if(m_orig_param) {
        m_orig_param->remove_param_handle(this);
    }
}

std::string cci_param_untyped_handle::get_description() const
{
    check_is_valid();
    return m_orig_param->get_description();
}

cci_value_map cci_param_untyped_handle::get_metadata() const
{
    check_is_valid();
    return m_orig_param->get_metadata();
}

void cci_param_untyped_handle::set_cci_value(const cci_value& val)
{
    check_is_valid();
    m_orig_param->set_cci_value(val, m_originator);
}

cci_value cci_param_untyped_handle::get_cci_value() const
{
    check_is_valid();
    return m_orig_param->get_cci_value();
}

cci_param_mutable_type cci_param_untyped_handle::get_mutable_type() const
{
    check_is_valid();
    return m_orig_param->get_mutable_type();
}

bool cci_param_untyped_handle::is_default_value()
{
    check_is_valid();
    return m_orig_param->is_default_value();
}

bool cci_param_untyped_handle::is_initial_value() const
{
    check_is_valid();
    return m_orig_param->is_initial_value();
}

const cci_originator&
cci_param_untyped_handle::get_latest_write_originator() const
{
    check_is_valid();
    return m_orig_param->get_latest_write_originator();
}

#define CCI_PARAM_UNTYPED_HANDLE_CALLBACK_IMPL_(name)                          \
cci_callback_untyped_handle                                                    \
cci_param_untyped_handle::register_##name##_callback(                          \
        const cci_param_##name##_callback_untyped &cb,                         \
        cci_untyped_tag)                                                       \
{                                                                              \
    check_is_valid();                                                          \
    return m_orig_param->register_##name##_callback(cb, m_originator);         \
}                                                                              \
                                                                               \
cci_callback_untyped_handle                                                    \
cci_param_untyped_handle::register_##name##_callback(                          \
        const cci_callback_untyped_handle& cb, cci_typed_tag<void>)            \
{                                                                              \
    check_is_valid();                                                          \
    return m_orig_param->register_##name##_callback(cb, m_originator);         \
}                                                                              \
                                                                               \
bool cci_param_untyped_handle::unregister_##name##_callback(                   \
        const cci_callback_untyped_handle &cb)                                 \
{                                                                              \
    check_is_valid();                                                          \
    return m_orig_param->unregister_##name##_callback(cb, m_originator);       \
}

// Pre write callback
CCI_PARAM_UNTYPED_HANDLE_CALLBACK_IMPL_(pre_write)

// Post write callback
CCI_PARAM_UNTYPED_HANDLE_CALLBACK_IMPL_(post_write)

// Pre read callback
CCI_PARAM_UNTYPED_HANDLE_CALLBACK_IMPL_(pre_read)

// Post read callback
CCI_PARAM_UNTYPED_HANDLE_CALLBACK_IMPL_(post_read)

bool cci_param_untyped_handle::unregister_all_callbacks()
{
    check_is_valid();
    return m_orig_param->unregister_all_callbacks(m_originator);
}

bool cci_param_untyped_handle::has_callbacks() const
{
    check_is_valid();
    return m_orig_param->has_callbacks();
}

bool cci_param_untyped_handle::lock(void* pwd)
{
    check_is_valid();
    return m_orig_param->lock(pwd);
}

bool cci_param_untyped_handle::unlock(void* pwd)
{
    check_is_valid();
    return m_orig_param->unlock(pwd);
}

bool cci_param_untyped_handle::is_locked() const
{
    check_is_valid();
    return m_orig_param->is_locked();
}

basic_param_type cci_param_untyped_handle::get_basic_type() const
{
    check_is_valid();
    return m_orig_param->get_basic_type();
}

const std::string& cci_param_untyped_handle::get_name() const
{
    check_is_valid();
    return m_orig_param->get_name();
}

cci_originator cci_param_untyped_handle::get_originator() const
{
    return m_originator;
}

const void* cci_param_untyped_handle::get_raw_value() const
{
    check_is_valid();
    return m_orig_param->get_raw_value();
}

const void* cci_param_untyped_handle::get_default_value_raw() const
{
    check_is_valid();
    return m_orig_param->get_default_value_raw();
}

void cci_param_untyped_handle::set_raw_value(const void* vp)
{
    check_is_valid();
    m_orig_param->set_raw_value(vp, m_originator);
}

void cci_param_untyped_handle::set_raw_value(const void* vp, const void* pwd)
{
    check_is_valid();
    m_orig_param->set_raw_value(vp, pwd, m_originator);
}

bool cci_param_untyped_handle::equals(const cci_param_untyped_handle& rhs) const
{
    check_is_valid();
    return m_orig_param->equals(*rhs.m_orig_param);
}

bool cci_param_untyped_handle::equals(const cci_param_if& rhs) const
{
    check_is_valid();
    return m_orig_param->equals(rhs);
}

const std::type_info& cci_param_untyped_handle::get_type_info() const
{
    check_is_valid();
    return m_orig_param->get_type_info();
}

void cci_param_untyped_handle::init()
{
    check_is_valid();
    m_orig_param->init();
}

void cci_param_untyped_handle::destroy()
{
    check_is_valid();
    m_orig_param->destroy();
}

bool cci_param_untyped_handle::is_valid(bool check) const
{
    if(check && !m_orig_param) {
        check_is_valid(false);
    }
    return m_orig_param ? true : false;
}

void cci_param_untyped_handle::invalidate(bool remove) {
    if(is_valid() && remove) {
        m_orig_param->remove_param_handle(this);
    }
    m_orig_param = NULL;
}

void cci_param_untyped_handle::check_is_valid(bool report_error) const
{
    if(!is_valid()) {
        cci_param_handle param_handle =
                cci_broker_manager::get_current_broker(m_originator).
                        get_param_handle(m_orig_param_name);
        if(!param_handle.is_valid()) {
            if(report_error) {
                CCI_REPORT_ERROR("cci_param_untyped_handle/check_is_valid",
                                 "The handled parameter is not valid.");
            }
        } else {
            m_orig_param = param_handle.m_orig_param;
        }
    }
}

#undef CCI_PARAM_UNTYPED_HANDLE_CALLBACK_IMPL_

CCI_CLOSE_NAMESPACE_