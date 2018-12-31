#include "TestBase.h"

int TestBase::g_id;

TestBase TestBase::CreateTestBase1(int n)
{
    std::cout << "CreateTestBase1 n=" << n << std::endl;
    return TestBase(n);
}

TestBase TestBase::CreateTestBase2(int n)
{
    std::cout << "CreateTestBase2 n=" << n << std::endl;
    auto result = TestBase(n);
    return result;
}
