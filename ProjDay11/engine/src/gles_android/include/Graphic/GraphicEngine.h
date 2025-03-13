#pragma once
#include "../Vec4.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <DeviceContext.h>

class GraphicEngine
{
public:
	GraphicEngine(void* nativeApp);
	~GraphicEngine();
public:
	void clear(const Vec4& color);
	void present();

	//ANativeWindow* m_nativeWindow;
	void* m_nativeApp;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;

	DeviceContext* m_deviceContext = nullptr;
};

