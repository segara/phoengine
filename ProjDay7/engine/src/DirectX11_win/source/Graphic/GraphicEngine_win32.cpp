#include "Graphic/GraphicEngine.h"
#include <windows.h>
#include <assert.h>
#include <stdexcept>
// Include necessary DirectX headers
#include <d3d11.h>
#include <dxgi.h>

// Global variables for DirectX device and context
//ID3D11Device
//Direct3D 리소스(버퍼, 텍스처, 셰이더 등)를 생성하고 관리할 수 있습니다.
//주요 역할 :
//렌더링에 필요한 그래픽 리소스를 생성합니다.
//GPU에 작업을 지시하는 명령을 준비합니다.
//Direct3D 11 기능 수준을 설정합니다.
ID3D11Device* g_pd3dDevice = NULL;
//렌더링 명령(그리기 명령, 상태 설정 등)을 GPU에 전달합니다.
//리소스 바인딩 및 셰이더 설정을 관리합니다.
//뷰포트 설정 및 렌더 타겟을 관리합니다.
ID3D11DeviceContext* g_pImmediateContext = NULL;
IDXGISwapChain* g_pSwapChain = NULL;
//렌더 타겟 뷰로, GPU가 그리기 작업을 수행할 대상(렌더 타겟)을 나타냅니다.
//일반적으로 스왑 체인의 백 버퍼를 가리키며, 그리기 명령은 이 렌더 타겟 뷰에 기록됩니다
ID3D11RenderTargetView* g_pRenderTargetView = NULL;

GraphicEngine::GraphicEngine(void* hwnd)
{
    HDC dummyDC = GetDC((HWND)hwnd);

    HRESULT hr = S_OK;

    // Swap chain description
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = 1024;
    sd.BufferDesc.Height = 768;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = (HWND)hwnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    // Create device, device context, and swap chain
    hr = D3D11CreateDeviceAndSwapChain(
        NULL,                     // Adapter
        D3D_DRIVER_TYPE_HARDWARE, // Driver Type
        NULL,                     // Software
        0,                        // Flags
        NULL,                     // Feature Levels
        0,                        // Feature Levels count
        D3D11_SDK_VERSION,        // SDK Version
        &sd,                      // Swap Chain Desc
        &g_pSwapChain,            // Swap Chain
        &g_pd3dDevice,            // Device
        NULL,                     // Feature Level
        &g_pImmediateContext      // Device Context
    );

    if (FAILED(hr))
    {
        fprintf(stderr, "Failed to create D3D11 device and swap chain\n");
    }

    // Create render target view
    ID3D11Texture2D* pBackBuffer = NULL;
    hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (FAILED(hr))
    {
        fprintf(stderr, "Failed to get back buffer\n");
    }

    hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
    pBackBuffer->Release();

    if (FAILED(hr))
    {
        fprintf(stderr, "Failed to create render target view\n");
    }

    g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

    // Set viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)1024;
    vp.Height = (FLOAT)768;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_pImmediateContext->RSSetViewports(1, &vp);
}
GraphicEngine::~GraphicEngine()
{
    // Clean-up:
    if (g_pImmediateContext) g_pImmediateContext->ClearState();
    if (g_pRenderTargetView) g_pRenderTargetView->Release();
    if (g_pSwapChain) g_pSwapChain->Release();
    if (g_pImmediateContext) g_pImmediateContext->Release();
    if (g_pd3dDevice) g_pd3dDevice->Release();
}
void GraphicEngine::clear(const Vec4& color)
{
    float clearColor[] = {color.x, color.y, color.z, color.w};
    g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, clearColor);
    g_pSwapChain->Present(0, 0);
}
