#pragma once
#include <Vec4.h>
#include <DeviceContext.h>
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

