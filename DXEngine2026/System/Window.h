#pragma once
#include "../Framework.h"

#define INITIAL_WIDTH 1280
#define INITIAL_HEIGHT 720

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window final
{
private:
	Window();
	~Window();

public:
	static Window* Get()
	{
		static Window object;
		return &object;
	}

	void Initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine,
		int nCmdShow, LPCWSTR lpWindowName);
	void Destroy();

	void Resize(uint newWidth, uint newHeight, bool bIsFullScreen = false) {}

	const uint& GetDisplayWidth() { return displayWidth; }
	const uint& GetDisplayHeight() { return displayHeight; }

	float GetWindowWidthFloat() { return static_cast<float>(windowWidth); }
	float GetWindowHeightFloat() { return static_cast<float>(windowHeight); }

	HWND GetHWND() { return hwnd; }

private:
	uint displayWidth = INITIAL_WIDTH;
	uint displayHeight = INITIAL_HEIGHT;

	uint windowWidth = INITIAL_WIDTH;
	uint windowHeight = INITIAL_HEIGHT;

	HWND hwnd = NULL;
	HINSTANCE hInstance = NULL;
	const wchar_t* CLASS_NAME = L"DirectX Window Class";
};