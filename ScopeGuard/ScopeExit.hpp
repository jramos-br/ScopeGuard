/**
 * ScopeExit
 *
 * This class is a generic RAII wrapper which ties one resource to a completion
 * routine which is bound by scope, ensuring execution at scope exit (as the
 * object is destroyed) unless released early.
 *
 * Based on N4189 proposal: Generic Scope Guard and RAII Wrapper for the
 * Standard Library by Peter Sommerlad and Andrew L. Sandoval. 2014-10-08
 *
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4189.pdf
 *
 * This program is free software, licensed under the terms of the MIT License
 * as published by the Open Source Initiative. It is distributed in the hope
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the file LICENSE for more details. If you don't find it, please see the
 * MIT License template at http://opensource.org/licenses/MIT.
 *
 * Copyright (C) 2018 Jorge Ramos https://github.com/jramos-br
 */

#ifndef _SCOPEEXIT_HPP_4481593C_1515_47C1_9BD7_944B4FCE736B_
#define _SCOPEEXIT_HPP_4481593C_1515_47C1_9BD7_944B4FCE736B_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <utility>
#include <tuple>

template<typename Callback>
class ScopeExit;

template<typename Callback>
static ScopeExit<Callback> CreateScopeExit(Callback&& callback)
{
    return ScopeExit<Callback>(std::forward<Callback>(callback));
}

template<typename Callback>
class ScopeExit final
{
    Callback m_callback;
    bool m_active;

    explicit ScopeExit(Callback&& callback) : m_callback(std::forward<Callback>(callback)), m_active(true)
    {
    }

    friend ScopeExit<Callback> CreateScopeExit<Callback>(Callback&&);

public:

    ScopeExit() = delete;
    ScopeExit(const ScopeExit&) = delete;
    ScopeExit& operator=(const ScopeExit&) = delete;
    ScopeExit& operator=(ScopeExit&&) = delete;

    ScopeExit(ScopeExit&& other) : m_callback(std::forward<Callback>(other.m_callback)), m_active(std::move(other.m_active))
    {
        other.m_active = false;
    }

    ~ScopeExit()
    {
        if (m_active)
        {
            m_callback();
        }
    }

    void Dismiss() throw()
    {
        m_active = false;
    }
};

#define SCOPE_EXIT_CAT_IMPL(A, B) A##B
#define SCOPE_EXIT_CAT(A, B) SCOPE_EXIT_CAT_IMPL(A, B)

#define SCOPE_EXIT_DECL(var, callback) auto var = CreateScopeExit(callback)
#define SCOPE_EXIT(callback) SCOPE_EXIT_DECL(SCOPE_EXIT_CAT(SCOPE_EXIT_, __LINE__), callback)

#endif
