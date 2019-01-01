#include "ScopeExit.hpp"
#include "ScopeExitTest.h"
#include "TestBase.h"

void Foo1()
{
    std::vector<int>* v = new std::vector<int>(2);
    try
    {
        // more stuff...
        int i = v->at(2); // Oops!
        // even more stuff...
    }
    catch (...)
    {
        delete v;
        throw;
    }
    delete v;
}

void Foo2()
{
    std::vector<int>* v = new std::vector<int>(2);
    SCOPE_EXIT([v] { delete v; });
    // more stuff...
    int i = v->at(2); // Oops!
    // even more stuff...
} // delete v is executed before Foo returns,
  // even if Foo throws an exception.

struct DbContext
{
    virtual void BeginTransaction() = 0;
    virtual void Update() = 0;
    virtual void Commit() = 0;
    virtual void Rollback() = 0;
};

void Foo3(DbContext* ctx)
{
    ctx->BeginTransaction();
    try
    {
        // more stuff...
        ctx->Commit();
    }
    catch (...)
    {
        ctx->Rollback();
        throw;
    }
    // even more stuff...
}

void Foo4(DbContext* ctx)
{
    ctx->BeginTransaction();
    SCOPE_EXIT_DECL(sg, [ctx] { ctx->Rollback(); });
    // more stuff...
    ctx->Commit();
    sg.Dismiss();
    // even more stuff...
} // Rollback is called before Foo returns even if Foo
  // throws an exception (before Dismiss is called). After
  // the Dismiss call, sg will not call Rollback anymore.

static void Callback1()
{
    std::cout << "Callback1" << std::endl;
}

static void Callback2()
{
    std::cout << "Callback2" << std::endl;
}

static void Callback3()
{
    std::cout << "Callback3" << std::endl;
}

static void Callback4(int id, int value)
{
    std::cout << "Callback4" << " id=" << id << " value=" << value << std::endl;
}

static void Callback4(int id, const char* value)
{
    std::cout << "Callback4" << " id=" << id << " value=" << value << std::endl;
}

void ScopeExitTest(int funcCode)
{
    if (funcCode == 2)
    {
        try
        {
            Foo1();
        }
        catch (const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }

        return;
    }
    auto cb1 = [] { Callback1(); };
    auto cb2 = [] { Callback4(42, 43); };
    auto cb3 = [] { Callback4(42, "text-42"); };

    SCOPE_EXIT([] { std::cout << "OK" << std::endl; });

    if ((funcCode & 1) != 0)
    {
        {
            std::cout << "ScopeExit copy ctor not available" << std::endl;

            //auto g1 = CreateScopeExit(&Callback1);
            //auto g2 = g1;
        }

        std::cout << std::endl;

        {
            std::cout << "ScopeExit move ctor test" << std::endl;

            auto g1 = CreateScopeExit(&Callback1);
            auto g2 = std::move(g1);
        }

        std::cout << std::endl;

        {
            std::cout << "ScopeExit copy assignment not available" << std::endl;

            //auto g1 = CreateScopeExit(&Callback1);
            //auto g2 = CreateScopeExit(&Callback2);
            //g1 = g2;
        }

        std::cout << std::endl;

        {
            std::cout << "ScopeExit move assignment not available" << std::endl;

            //auto g1 = CreateScopeExit(&Callback1);
            //auto g2 = CreateScopeExit(&Callback2);
            //g1 = std::move(g2);
        }

        std::cout << std::endl;

        {
            std::cout << "pre built lambda test" << std::endl;

            auto g1 = CreateScopeExit(cb1);
            auto g2 = CreateScopeExit(cb2);
            auto g3 = CreateScopeExit(cb3);
        }

        std::cout << std::endl;

        {
            std::cout << "inline lambda test" << std::endl;

            auto g1 = CreateScopeExit([] { Callback1(); });
            auto g2 = CreateScopeExit([] { Callback4(44, 45); });
            auto g3 = CreateScopeExit([] { Callback4(44, "text-44"); });
        }

        std::cout << std::endl;

        {
            std::cout << "object byref lambda test" << std::endl;

            TestBase tb1(12);
            auto g1 = CreateScopeExit([&tb1] { tb1(); });
            auto g2 = CreateScopeExit([&tb1] { tb1.Dump(); });
        }

        std::cout << std::endl;

        {
            std::cout << "object byval lambda test" << std::endl;

            TestBase tb2(16);
            auto g9 = CreateScopeExit([tb2] { tb2(); });
            auto g10 = CreateScopeExit([tb2] { tb2.Dump(); });
        }

        std::cout << std::endl;

        {
            std::cout << "ScopeExit cancel test" << std::endl;

            auto g1 = CreateScopeExit(&Callback1);
            g1.Dismiss();
            std::cout << "Canceled" << std::endl;
        }

        std::cout << std::endl;
    }
}
