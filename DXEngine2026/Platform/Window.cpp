#include "Window.h"
#include "../Core/Logger.h"
#include "Input.h"

bool Window::Create(const std::wstring& title, int width, int height)
{
    m_Width = width;
    m_Height = height;
    m_hInstance = GetModuleHandle(nullptr);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = L"MiniEngineWindowClass";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClass(&wc);

    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    m_hWnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        nullptr,
        nullptr,
        m_hInstance,
        this
    );

    if (!m_hWnd)
    {
        Logger::Error("Failed to create window.");
        return false;
    }

    ShowWindow(m_hWnd, SW_SHOW);
    Logger::Info("Window created.");
    return true;
}

void Window::Destroy()
{
    if (m_hWnd)
    {
        DestroyWindow(m_hWnd);
        m_hWnd = nullptr;
    }
}

void Window::PollEvents()
{
    MSG msg = {};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            m_ShouldClose = true;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_KEYDOWN:
        Input::SetKeyDown(static_cast<uint8_t>(wParam));
        return 0;

    case WM_KEYUP:
        Input::SetKeyUp(static_cast<uint8_t>(wParam));
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}