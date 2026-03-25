#pragma once
#include "../Framework.h"

class D3D final
{
private:
	D3D();
	~D3D();

public:
	static D3D* Get()
	{
		static D3D object;
		return &object;
	}

	void Initialize(HWND hwnd, uint width, uint height);
	void Resize();
	void Destroy();

	void Update();
	void Render_Begin();	// set VS, PS buffer
	void Render_End();		// swapchain->present

	IDXGISwapChain* GetSwapChain() { return swapChain; }
	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return deviceContext; }

	D3D11_VIEWPORT* GetViewport() { return &viewport; }

	ID3D11RenderTargetView* GetRTV() { return rtv; }

	void SetRenderTarget(ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv);
	void SetRenderTargets(uint viewNum, ID3D11RenderTargetView* const* rtvs, ID3D11DepthStencilView* dsv);

private:
	IDXGISwapChain* swapChain = nullptr;
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;

	ID3D11Debug* debug;

	D3D11_VIEWPORT viewport;

	ID3D11RenderTargetView* rtv;

	struct ViewProj
	{
		//temp
		float view[16];
		float projection[16];
	} viewProj;

	ID3D11Buffer* vp_cbuffer;

	ID3D11Texture2D* depthTexture;
	ID3D11DepthStencilView* dsv;
};