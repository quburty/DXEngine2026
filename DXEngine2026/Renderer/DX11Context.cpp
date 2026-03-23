#include "DX11Context.h"
#include "../Core/Logger.h"

bool DX11Context::Initialize(HWND hwnd, int width, int height)
{
    DXGI_SWAP_CHAIN_DESC swapDesc = {};
    swapDesc.BufferCount = 1;
    swapDesc.BufferDesc.Width = width;
    swapDesc.BufferDesc.Height = height;
    swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapDesc.OutputWindow = hwnd;
    swapDesc.SampleDesc.Count = 1;
    swapDesc.Windowed = TRUE;
    swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createFlags = 0;
#if defined(_DEBUG)
    createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevel;
    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        createFlags,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapDesc,
        m_SwapChain.GetAddressOf(),
        m_Device.GetAddressOf(),
        &featureLevel,
        m_DeviceContext.GetAddressOf()
    );

    if (FAILED(hr))
    {
        Logger::Error("Failed to create D3D11 device and swap chain.");
        return false;
    }

    if (!CreateRenderTarget())
    {
        Logger::Error("Failed to create render target.");
        return false;
    }

    Logger::Info("DX11 initialized.");
    return true;
}

bool DX11Context::CreateRenderTarget()
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    HRESULT hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
    if (FAILED(hr))
        return false;

    hr = m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_RenderTargetView.GetAddressOf());
    if (FAILED(hr))
        return false;

    return true;
}

void DX11Context::BeginFrame(float r, float g, float b, float a)
{
    float clearColor[4] = { r, g, b, a };
    m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);
    m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);
}

void DX11Context::EndFrame()
{
    m_SwapChain->Present(1, 0);
}

void DX11Context::Shutdown()
{
    m_RenderTargetView.Reset();
    m_SwapChain.Reset();
    m_DeviceContext.Reset();
    m_Device.Reset();

    Logger::Info("DX11 shutdown.");
}