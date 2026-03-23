#pragma once
#include "../Platform/Window.h"
#include "../Renderer/DX11Context.h"

class Application
{
public:
    bool Initialize();
    void Run();
    void Shutdown();

private:
    Window m_Window;
    DX11Context m_Renderer;
    bool m_Running = true;
};