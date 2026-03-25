#include "stdafx.h"

void Initialize();
void Update();
void Render();
void Destroy();

using namespace std;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Window::Get()->Initialize(hInstance, hPrevInstance, pCmdLine, nCmdShow, L"TEST");

	Initialize();

	MSG msg = {};

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Update();
		Render();
	}

	Destroy();

	return 0;
}

void Initialize()
{
	D3D::Get()->Initialize(Window::Get()->GetHWND(), Window::Get()->GetDisplayWidth(), Window::Get()->GetDisplayHeight());
}

void Update()
{
	D3D::Get()->Update();
}

void Render()
{
	D3D::Get()->Render_Begin();

	D3D::Get()->Render_End();
}

void Destroy()
{
	Window::Get()->Destroy();
}
