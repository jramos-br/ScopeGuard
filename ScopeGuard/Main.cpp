#include "Application.h"
#include "ScopeGuardTest.h"

class ScopeGuardApplication : public Application
{
public:

    ScopeGuardApplication(int argc, const char* argv[]) : Application(argc, argv)
    {
    }

    virtual void Run()
    {
        ScopeGuardTest();
    }
};

int main(int argc, const char* argv[])
{
    ScopeGuardApplication application(argc, argv);
    application.Run();
    return application.ExitStatus();
}
