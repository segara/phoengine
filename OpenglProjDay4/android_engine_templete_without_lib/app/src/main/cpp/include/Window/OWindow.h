#pragma once
#include <EGL/egl.h>
#include <GLES3/gl3.h>
class OWindow
{
public:
	OWindow();
	~OWindow();
	void Present(bool vsync);


};

