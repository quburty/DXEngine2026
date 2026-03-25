#include "../Framework.h"
#include "D3D.h"

D3D::D3D()
{
}

D3D::~D3D()
{
}

void D3D::Initialize(HWND hwnd, uint width, uint height)
{
	// Create SwapChain, Device, DeviceContext
	{
		DXGI_MODE_DESC bufferDesc; //후면 버퍼의 속성들을 서술.
		ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
		bufferDesc.Width = width;
		bufferDesc.Height = height;
		bufferDesc.RefreshRate.Numerator = 60;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //디스플레이 스캔 라인 모드
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //텍스쳐 사용 형식

		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
		desc.BufferCount = 1;
		desc.BufferDesc = bufferDesc;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.OutputWindow = hwnd;
		desc.SampleDesc.Count = 1; //픽셀당 추출할 표본의 개수, 1이면 멀티샘플링 사용하지 않음
		desc.SampleDesc.Quality = 0;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //버퍼를 언제 비울지 옵션, discard는 바로 폐기
		desc.Windowed = TRUE;

		D3D_FEATURE_LEVEL feature_levels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0
		};

		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr, //비디오카드 인터페이스 설정
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr, //d11이 핸들을 지정
			D3D11_CREATE_DEVICE_DEBUG, //사용할 d11의 api 레이어
			feature_levels,
			sizeof(feature_levels) / sizeof(D3D_FEATURE_LEVEL),
			D3D11_SDK_VERSION,
			&desc,
			&swapChain,
			&device,
			nullptr,
			&deviceContext
		);

		assert(hr == S_OK);

		// Create RTV
		{
			ID3D11Texture2D* backBuffer;
			HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
			assert(SUCCEEDED(hr));

			hr = device->CreateRenderTargetView(backBuffer, nullptr, &rtv);
			assert(SUCCEEDED(hr));

			SAFE_RELEASE(backBuffer);
		}

		deviceContext->OMSetRenderTargets(1, &rtv, nullptr);

		// Create viewport
		{
			viewport.Width = Window::Get()->GetWindowWidthFloat();
			viewport.Height = Window::Get()->GetWindowHeightFloat();
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			viewport.TopLeftX = 0.0f;
			viewport.TopLeftY = 0.0f;
			deviceContext->RSSetViewports(1, &viewport);
		}
	}
}

void D3D::Resize()
{
}

void D3D::Destroy()
{
	SAFE_RELEASE(rtv);

	SAFE_RELEASE(swapChain);
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
}

void D3D::Update()
{
}

void D3D::Render_Begin()
{
	float color[4] = { 0.2f,0.2f,0.2f,0.2f };
	deviceContext->ClearRenderTargetView(rtv, color);

}

void D3D::Render_End()
{
	swapChain->Present(0, 0);
}

void D3D::SetRenderTarget(ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv)
{
	deviceContext->OMSetRenderTargets(1, &rtv, dsv);
}

void D3D::SetRenderTargets(uint viewNum, ID3D11RenderTargetView* const* rtvs, ID3D11DepthStencilView* dsv)
{
	deviceContext->OMSetRenderTargets(viewNum, rtvs, dsv);
}
