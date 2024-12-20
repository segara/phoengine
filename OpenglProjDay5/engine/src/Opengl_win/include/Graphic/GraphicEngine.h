#pragma once
#include <Vec4.h>
class GraphicEngine
{
public:
	GraphicEngine(void* hwnd);
	~GraphicEngine();


public:
	void clear(const Vec4& color);
};

