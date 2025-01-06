#pragma once
#include "../Vec4.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
class GraphicEngine
{
public:
	GraphicEngine(void* window);
	~GraphicEngine();
public:
	void clear(const Vec4& color);


	ANativeWindow* m_nativeWindow;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
};

