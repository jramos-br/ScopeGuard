#if 0
#define TEST_SCOPE_GUARD
#endif

#if 1
#define TEST_SCOPEGUARD
#endif

#ifdef TEST_SCOPE_GUARD
#include "scope_guard.hpp"
#endif

#ifdef TEST_SCOPEGUARD
#include "ScopeGuard.h"
#endif

#include "ScopeGuardTest.h"
#include "TestBase.h"

static void Callback1()
{
    std::cout << "Callback1" << std::endl;
}

static void Callback2(int id, int value)
{
    std::cout << "Callback2" << " id=" << id << " value=" << value << std::endl;
}

static void Callback3(int id, const char* value)
{
    std::cout << "Callback3" << " id=" << id << " value=" << value << std::endl;
}

void ScopeGuardTest()
{
    auto cb1 = [] { Callback1(); };
    auto cb2 = [] { Callback2(42, 43); };
    auto cb3 = [] { Callback3(42, "text-42"); };

#ifdef TEST_SCOPEGUARD

    {
        std::cout << "ScopeGuard1 basic test" << std::endl;

        ScopeGuard1<void(*)()> g1 = ScopeGuard::Create(&Callback1);
        ScopeGuard1<void(*)()> g2 = g1;
        ScopeGuard1<void(*)()> g3;
        g3 = g2;
        ScopeGuard1<void(*)()> g4 = std::move(g2);
        ScopeGuard1<void(*)()> g5;
        g5 = std::move(g3);
    }

    std::cout << std::endl;

    {
        std::cout << "ScopeGuard2 basic test" << std::endl;

        ScopeGuard2<void(*)(int, int), int, int> g1 = ScopeGuard::Create(&Callback2, 33, 34);
        ScopeGuard2<void(*)(int, int), int, int> g2 = g1;
        ScopeGuard2<void(*)(int, int), int, int> g3;
        g3 = g2;
        ScopeGuard2<void(*)(int, int), int, int> g4 = std::move(g2);
        ScopeGuard2<void(*)(int, int), int, int> g5;
        g5 = std::move(g3);
    }

    std::cout << std::endl;

    {
        std::cout << "pre built lambda test" << std::endl;

        auto g1 = ScopeGuard::Create(cb1);
        auto g2 = ScopeGuard::Create(cb2);
        auto g3 = ScopeGuard::Create(cb3);
    }

    std::cout << std::endl;

    {
        std::cout << "inline lambda test" << std::endl;

        auto g4 = ScopeGuard::Create([] { Callback1(); });
        auto g5 = ScopeGuard::Create([] { Callback2(44, 45); });
        auto g6 = ScopeGuard::Create([] { Callback3(44, "text-44"); });
    }

    std::cout << std::endl;

    {
        std::cout << "object byref lambda test" << std::endl;

        TestBase tb1(12);
        auto g7 = ScopeGuard::Create([&tb1] { tb1(); });
        auto g8 = ScopeGuard::Create([&tb1] { tb1.Dump(); });
    }

    std::cout << std::endl;

    {
        std::cout << "object byval lambda test" << std::endl;

        TestBase tb2(16);
        auto g9 = ScopeGuard::Create([tb2] { tb2(); });
        auto g10 = ScopeGuard::Create([tb2] { tb2.Dump(); });
    }

    std::cout << std::endl;

#endif

#ifdef TEST_SCOPE_GUARD

    {
        std::cout << "pre built lambda test" << std::endl;

        auto g1 = sg::make_scope_guard(cb1);
        auto g2 = sg::make_scope_guard(cb2);
        auto g3 = sg::make_scope_guard(cb3);
    }

    std::cout << std::endl;

    {
        std::cout << "inline lambda test" << std::endl;

        auto g4 = sg::make_scope_guard([] { Callback1(); });
        auto g5 = sg::make_scope_guard([] { Callback2(44, 45); });
        auto g6 = sg::make_scope_guard([] { Callback3(44, "text-44"); });
    }

    std::cout << std::endl;

    {
        std::cout << "object byref lambda test" << std::endl;

        TestBase tb1(12);
        auto g7 = sg::make_scope_guard([&tb1] { tb1(); });
        auto g8 = sg::make_scope_guard([&tb1] { tb1.Dump(); });
    }

    std::cout << std::endl;

    {
        std::cout << "object byval lambda test" << std::endl;

        TestBase tb2(16);
        auto g9 = sg::make_scope_guard([tb2] { tb2(); });
        auto g10 = sg::make_scope_guard([tb2] { tb2.Dump(); });
    }

    std::cout << std::endl;

#endif
}
