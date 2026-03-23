#pragma once
#include <Windows.h>
#include <string>

class Window
{
public:
    Window() = default;
    ~Window() = default;

    bool Create(const std::wstring& title, int width, int height);
    void Destroy();

    void PollEvents();

    HWND GetHWND() const { return m_hWnd; }
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    bool ShouldClose() const { return m_ShouldClose; }

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    HWND m_hWnd = nullptr;
    HINSTANCE m_hInstance = nullptr;
    int m_Width = 1280;
    int m_Height = 720;
    bool m_ShouldClose = false;
};