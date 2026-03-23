#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <Windows.h>

class DX11Context
{
public:
    bool Initialize(HWND hwnd, int width, int height);
    void Shutdown();

    void BeginFrame(float r, float g, float b, float a);
    void EndFrame();

private:
    bool CreateRenderTarget();

private:
    Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
    Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
};