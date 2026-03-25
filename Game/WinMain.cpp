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
}

void Update()
{
}

void Render()
{
}

void Destroy()
{
	Window::Get()->Destroy();
}
