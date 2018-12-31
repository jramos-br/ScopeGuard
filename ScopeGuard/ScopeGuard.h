#ifndef _SCOPEGUARD_H_4481593C_1515_47C1_9BD7_944B4FCE736B_
#define _SCOPEGUARD_H_4481593C_1515_47C1_9BD7_944B4FCE736B_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <iostream>
#include <utility>
#include <tuple>

#include "StdApply.h"

template<typename Callback>
class ScopeGuard1;

template<typename Callback, typename... Args>
class ScopeGuard2;

class ScopeGuard
{
    static int Next()
    {
        static int id;
        return ++id;
    }

protected:

    const int m_id = Next();

    ScopeGuard() {}
    ScopeGuard(const ScopeGuard&) {}
    ScopeGuard& operator=(const ScopeGuard&) {}

public:

    ScopeGuard(ScopeGuard&&) = delete;
    ScopeGuard& operator=(ScopeGuard&&) = delete;

    virtual ~ScopeGuard()
    {
    }

    template<typename Callback>
    static ScopeGuard1<Callback> Create(Callback&& callback)
    {
        return ScopeGuard1<Callback>(std::forward<Callback>(callback));
    }

    template<typename Callback, typename... Args>
    static ScopeGuard2<Callback, Args...> Create(Callback&& callback, Args&&... args)
    {
        return ScopeGuard2<Callback, Args...>(std::forward<Callback>(callback), std::forward<Args>(args)...);
    }
};

template<typename Callback>
class ScopeGuard1 final : public ScopeGuard
{
    Callback m_callback;
    bool m_active;

    explicit ScopeGuard1(Callback&& callback) : m_callback(std::forward<Callback>(callback)), m_active(true)
    {
        std::cout << "explicit ScopeGuard1(Callback&& callback) [custom ctor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.active=" << m_active;
        std::cout << std::endl;
    }

    friend ScopeGuard1<Callback> ScopeGuard::Create<Callback>(Callback&&);

public:

    ScopeGuard1()
    {
        std::cout << "ScopeGuard1() [default ctor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.active=" << m_active;
        std::cout << std::endl;
    }

    ScopeGuard1(const ScopeGuard1& other) : m_callback(other.m_callback), m_active(other.m_active)
    {
        std::cout << "ScopeGuard1(const ScopeGuard1& other) [copy ctor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.active=" << m_active;
        std::cout << " other=" << &other;
        std::cout << " other.id=" << other.m_id;
        std::cout << " other.active=" << other.m_active;
        std::cout << std::endl;
    }

    ScopeGuard1(ScopeGuard1&& other) : m_callback(std::forward<Callback>(other.m_callback)), m_active(other.m_active)
    {
        std::cout << "ScopeGuard1(ScopeGuard1&& other) [move ctor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.active=" << m_active;
        std::cout << " other=" << &other;
        std::cout << " other.id=" << other.m_id;
        std::cout << " other.active=" << other.m_active;
        std::cout << std::endl;

        other.m_active = false;
    }

    ScopeGuard1& operator=(const ScopeGuard1& other)
    {
        std::cout << "ScopeGuard1& operator=(const ScopeGuard1& other) [copy assignment]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.active=" << m_active;
        std::cout << " other=" << &other;
        std::cout << " other.id=" << other.m_id;
        std::cout << " other.active=" << other.m_active;
        std::cout << std::endl;

        if (this != &other)
        {
            m_callback = other.m_callback;
            m_active = other.m_active;
        }

        return *this;
    }

    ScopeGuard1& operator=(ScopeGuard1&& other)
    {
        std::cout << "ScopeGuard1& operator=(ScopeGuard1&& other) [move assignment]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.active=" << m_active;
        std::cout << " other=" << &other;
        std::cout << " other.id=" << other.m_id;
        std::cout << " other.active=" << other.m_active;
        std::cout << std::endl;

        if (this != &other)
        {
            m_callback = std::forward<Callback>(other.m_callback);
            m_active = other.m_active;

            other.m_active = false;
        }

        return *this;
    }

    ~ScopeGuard1()
    {
        std::cout << "~ScopeGuard1() [dtor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.active=" << m_active;
        std::cout << std::endl;

        if (m_active)
        {
            m_callback();
        }
    }
};

template<typename Callback, typename... Args>
class ScopeGuard2 final : public ScopeGuard
{
    Callback m_callback;
    std::tuple<Args...> m_tuple;
    bool m_active;

    explicit ScopeGuard2(Callback&& callback, Args&&... args) : m_callback(std::forward<Callback>(callback)), m_tuple(std::forward<Args>(args)...), m_active(true)
    {
        std::cout << "explicit ScopeGuard2(Callback&& callback, Args&&... args) [custom ctor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.active=" << m_active;
        std::cout << " this.tuple_size=" << std::tuple_size<std::tuple<Args...>>::value;
        std::cout << std::endl;
    }

    friend ScopeGuard2<Callback, Args...> ScopeGuard::Create<Callback, Args...>(Callback&&, Args&&...);

public:

#if 0

    ScopeGuard2() = default;
    ScopeGuard2(const ScopeGuard2& other) = default;
    ScopeGuard2(ScopeGuard2&& other) = default;
    ScopeGuard2& operator=(const ScopeGuard2& other) = default;
    ScopeGuard2& operator=(ScopeGuard2&& other) = default;

#else

    ScopeGuard2()
    {
        std::cout << "ScopeGuard2() [default ctor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.active=" << m_active;
        std::cout << " this.tuple_size=" << std::tuple_size<std::tuple<Args...>>::value;
        std::cout << std::endl;
    }

    ScopeGuard2(const ScopeGuard2& other) : m_callback(other.m_callback), m_tuple(other.m_tuple), m_active(other.m_active)
    {
        std::cout << "ScopeGuard2(const ScopeGuard2& other) [copy ctor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.active=" << m_active;
        std::cout << " this.tuple_size=" << std::tuple_size<std::tuple<Args...>>::value;
        std::cout << " other=" << &other;
        std::cout << " other.id=" << other.m_id;
        std::cout << " other.active=" << other.m_active;
        std::cout << std::endl;
    }

    ScopeGuard2(ScopeGuard2&& other) : m_callback(std::forward<Callback>(other.m_callback)), m_tuple(std::forward<std::tuple<Args...>>(other.m_tuple)), m_active(other.m_active)
    {
        std::cout << "ScopeGuard2(ScopeGuard2&& other) [move ctor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.active=" << m_active;
        std::cout << " this.tuple_size=" << std::tuple_size<std::tuple<Args...>>::value;
        std::cout << " other=" << &other;
        std::cout << " other.id=" << other.m_id;
        std::cout << " other.active=" << other.m_active;
        std::cout << std::endl;

        other.m_active = false;
    }

    ScopeGuard2& operator=(const ScopeGuard2& other)
    {
        std::cout << "ScopeGuard2& operator=(const ScopeGuard2& other) [copy assignment]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.active=" << m_active;
        std::cout << " this.tuple_size=" << std::tuple_size<std::tuple<Args...>>::value;
        std::cout << " other=" << &other;
        std::cout << " other.id=" << other.m_id;
        std::cout << " other.active=" << other.m_active;
        std::cout << std::endl;

        if (this != &other)
        {
            m_callback = other.m_callback;
            m_tuple = other.m_tuple;
            m_active = other.m_active;
        }

        return *this;
    }

    ScopeGuard2& operator=(ScopeGuard2&& other)
    {
        std::cout << "ScopeGuard2& operator=(ScopeGuard2&& other) [move assignment]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.active=" << m_active;
        std::cout << " this.tuple_size=" << std::tuple_size<std::tuple<Args...>>::value;
        std::cout << " other=" << &other;
        std::cout << " other.id=" << other.m_id;
        std::cout << " other.active=" << other.m_active;
        std::cout << std::endl;

        if (this != &other)
        {
            m_callback = std::forward<Callback>(other.m_callback);
            m_tuple = std::forward<std::tuple<Args...>>(other.m_tuple);
            m_active = other.m_active;

            other.m_active = false;
        }

        return *this;
    }

#endif

    ~ScopeGuard2()
    {
        std::cout << "~ScopeGuard2() [dtor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.active=" << m_active;
        std::cout << " this.tuple_size=" << std::tuple_size<std::tuple<Args...>>::value;
        std::cout << std::endl;

        if (m_active)
        {
            std::apply(m_callback, m_tuple);
        }
    }
};

#endif
