#include <stdlib.h>

#include "Application.h"
#include "ScopeGuardTest1.h"
#include "ScopeGuardTest2.h"
#include "ScopeExitTest.h"

class ScopeGuardApplication : public Application
{
    int m_testCode;
    int m_funcCode;

public:

    ScopeGuardApplication(int argc, const char* argv[]) : Application(argc, argv)
    {
        m_testCode = 1;
        m_funcCode = 1;

        if (argc >= 2)
        {
            m_testCode = atoi(argv[1]);

            if (argc >= 3)
            {
                m_funcCode = atoi(argv[2]);
            }
        }
    }

    virtual void Run()
    {
        switch (m_testCode)
        {
        case 1:
            ScopeGuardTest1(m_funcCode);
            break;
        case 2:
            ScopeGuardTest2(m_funcCode);
            break;
        case 3:
            ScopeExitTest(m_funcCode);
            break;
        }
    }
};

int main(int argc, const char* argv[])
{
    ScopeGuardApplication application(argc, argv);
    application.Run();
    return application.ExitStatus();
}
