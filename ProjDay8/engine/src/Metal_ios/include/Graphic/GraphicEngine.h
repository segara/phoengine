#pragma once

#import <UIKit/UIKit.h>
#include <Metal/Metal.h>
#include <MetalKit/MetalKit.h>
#include <QuartzCore/CAMetalLayer.h>
#include "MetalView.h"
#include "MetalViewController.h"
class GraphicEngine
{
public:
	GraphicEngine(void* hwnd);
	~GraphicEngine();


public:
	void clear(const simd::float4& color);  
    MetalViewController* view_controller;
};

