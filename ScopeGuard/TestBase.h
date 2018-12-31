#ifndef _TESTBASE_H_4481593C_1515_47C1_9BD7_944B4FCE736B_
#define _TESTBASE_H_4481593C_1515_47C1_9BD7_944B4FCE736B_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <vector>
#include <iostream>

class TestBase
{
    static int g_id;

    const int m_id = ++g_id;
    std::vector<int> m_vector;

public:

    TestBase()
    {
        std::cout << "TestBase() [default ctor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.size=" << m_vector.size();
        std::cout << std::endl;
    }

    explicit TestBase(int size) : m_vector(std::vector<int>(size))
    {
        std::cout << "explicit TestBase(int size) [custom ctor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.size=" << m_vector.size();
        std::cout << std::endl;
    }

    TestBase(const TestBase& other) : m_vector(other.m_vector)
    {
        std::cout << "TestBase(const TestBase& other) [copy ctor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.size=" << m_vector.size();
        std::cout << " other=" << &other;
        std::cout << " other.id=" << other.m_id;
        std::cout << " other.size=" << other.m_vector.size();
        std::cout << std::endl;
    }

    TestBase(TestBase&& other) : m_vector(std::move(other.m_vector))
    {
        std::cout << "TestBase(TestBase&& other) [move ctor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.size=" << m_vector.size();
        std::cout << " other=" << &other;
        std::cout << " other.id=" << other.m_id;
        std::cout << " other.size=" << other.m_vector.size();
        std::cout << std::endl;
    }

    TestBase& operator=(const TestBase& other)
    {
        std::cout << "TestBase& operator=(const TestBase& other) [copy assignment]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.size=" << m_vector.size();
        std::cout << " other=" << &other;
        std::cout << " other.id=" << other.m_id;
        std::cout << " other.size=" << other.m_vector.size();
        std::cout << std::endl;

        if (this != &other)
        {
            m_vector = other.m_vector;
        }

        return *this;
    }

    TestBase& operator=(TestBase&& other)
    {
        std::cout << "TestBase& operator=(TestBase&& other) [move assignment]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.size=" << m_vector.size();
        std::cout << " other=" << &other;
        std::cout << " other.id=" << other.m_id;
        std::cout << " other.size=" << other.m_vector.size();
        std::cout << std::endl;

        if (this != &other)
        {
            m_vector = std::move(other.m_vector);
        }

        return *this;
    }

    virtual ~TestBase()
    {
        std::cout << "~TestBase() [dtor]";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.size=" << m_vector.size();
        std::cout << std::endl;
    }

    size_t Size() const { return m_vector.size(); }

    void operator()() const
    {
        std::cout << "void operator()()";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.size=" << m_vector.size();
        std::cout << std::endl;
    }

    void Dump() const
    {
        std::cout << "void Dump()";
        std::cout << " this=" << this;
        std::cout << " this.id=" << m_id;
        std::cout << " this.size=" << m_vector.size();
        std::cout << std::endl;
    }

    static TestBase CreateTestBase1(int n);
    static TestBase CreateTestBase2(int n);
};

#endif
