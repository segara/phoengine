#pragma once

#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include <Metal/Metal.h>
#include <AppKit/AppKit.h>
#include <MetalKit/MetalKit.h>
#include <QuartzCore/CAMetalLayer.h>
#include <simd/simd.h>
class GraphicEngine
{
public:
	GraphicEngine(void* hwnd);
	~GraphicEngine();


public:
	void clear(const simd::float4& color);
    id<MTLDevice> device = nil;
    id<MTLCommandQueue> commandQueue = nil;
    CAMetalLayer* metalLayer = nil;
  
};

