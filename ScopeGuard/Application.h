#ifndef _APPLICATION_H_4481593C_1515_47C1_9BD7_944B4FCE736B_
#define _APPLICATION_H_4481593C_1515_47C1_9BD7_944B4FCE736B_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

class Application
{
    static Application* m_currentApplication;

    int m_exitStatus;
    int m_argc;
    const char** m_argv;

public:

    static Application* GetCurrentApplication();

    int ExitStatus() const { return m_exitStatus; }
    void ExitStatus(int value) { m_exitStatus = value; }

    int Argc() const { return m_argc; }
    const char** Argv() const { return m_argv; }

    Application(int argc, const char* argv[]);
    virtual ~Application();
    virtual void Run() = 0;

    Application() = delete;
    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;
};

#endif
