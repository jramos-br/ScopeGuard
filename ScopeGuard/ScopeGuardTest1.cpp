#include "ScopeGuardTest2.h"
#include "TestBase.h"

void ScopeGuardTest1(int funcCode)
{
    {
        std::cout << "default ctor test" << std::endl;
        TestBase tb1;
    }

    std::cout << std::endl;

    {
        std::cout << "copy ctor test" << std::endl;
        TestBase tb2(16);
        TestBase tb3(tb2);
        TestBase tb4 = tb3;
    }

    std::cout << std::endl;

    {
        std::cout << "move ctor test" << std::endl;
        TestBase tb5(32);
        TestBase tb6(std::move(tb5));
        TestBase tb7 = std::move(tb6);
    }

    std::cout << std::endl;

    {
        std::cout << "copy assignment test" << std::endl;
        TestBase tb8(16);
        TestBase tb9(32);
        tb8 = tb9;
    }

    std::cout << std::endl;

    {
        std::cout << "move assignment test" << std::endl;
        TestBase tb10(16);
        TestBase tb11(32);
        tb10 = std::move(tb11);
    }

    std::cout << std::endl;

    {
        std::cout << "copy elision test" << std::endl;
        TestBase tb12 = TestBase::CreateTestBase1(16);
        TestBase tb13 = tb12;
    }

    std::cout << std::endl;

    {
        // does copy elision in release mode
        std::cout << "no copy elision assignment test" << std::endl;
        TestBase tb15 = TestBase::CreateTestBase2(16);
        TestBase tb16 = tb15;
    }
}
