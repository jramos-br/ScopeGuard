#include <stdlib.h>
#include <locale.h>
#include <time.h>

#include "Application.h"

Application* Application::m_currentApplication;

Application* Application::GetCurrentApplication()
{
    return m_currentApplication;
}

Application::Application(int argc, const char* argv[])
{
    setlocale(LC_ALL, "");
    _tzset();

    m_currentApplication = this;
    m_exitStatus = EXIT_SUCCESS;
    m_argc = argc;
    m_argv = argv;
}

Application::~Application()
{
    m_currentApplication = nullptr;
}
