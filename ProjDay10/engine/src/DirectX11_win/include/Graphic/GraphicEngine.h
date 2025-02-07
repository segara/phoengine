#pragma once
#include <Windows.h>
#include <minwindef.h>
#include <Vec4.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <DeviceContext.h>

// Include necessary DirectX headers

class GraphicEngine
{
public:
	GraphicEngine(void* hwnd);
	~GraphicEngine();

public:
	void clear(const Vec4& color);
	void present();

	DeviceContext* m_deviceContext = nullptr;
};

