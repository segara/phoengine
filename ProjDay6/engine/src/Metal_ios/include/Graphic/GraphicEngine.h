#pragma once

#include <Metal/Metal.h>
#include <MetalKit/MetalKit.h>
#include <QuartzCore/CAMetalLayer.h>

class GraphicEngine
{
public:
	GraphicEngine(void* hwnd);
	~GraphicEngine();


public:
	void clear(const simd::float4& color);  

};

