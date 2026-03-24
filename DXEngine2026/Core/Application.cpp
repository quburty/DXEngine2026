#include "Application.h"
#include "Logger.h"
#include "Time.h"
#include "../Platform/Input.h"
#include <Windows.h>

bool Application::Initialize()
{
    Input::Initialize();

    if (!m_Window.Create(L"Mini Engine - Week 1", 1280, 720))
    {
        Logger::Error("Window initialization failed.");
        return false;
    }

    if (!m_Renderer.Initialize(m_Window.GetHWND(), m_Window.GetWidth(), m_Window.GetHeight()))
    {
        Logger::Error("Renderer initialization failed.");
        return false;
    }

    Time::Init();

    Logger::Info("Application initialized.");
    return true;
}

void Application::Run()
{
    Logger::Info("Main loop started.");

    while (m_Running && !m_Window.ShouldClose())
    {
        m_Window.PollEvents();

        if (Input::IsKeyDown(VK_ESCAPE))
        {
            Logger::Info("ESC pressed. Exiting...");
            m_Running = false;
        }

        m_Renderer.BeginFrame(0.1f, 0.1f, 0.25f, 1.0f);
        m_Renderer.EndFrame();

        Time::Update();
        Input::Update();
    }
}

void Application::Shutdown()
{
    m_Renderer.Shutdown();
    m_Window.Destroy();
    Logger::Info("Application shutdown.");
}