#pragma once
#include <DeviceContext.h>
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

    void present();
    void clear(const simd::float4& color);
    // Getters for Metal objects
    id<MTLDevice> getDevice() const { return device; }
    id<MTLCommandQueue> getCommandQueue() const { return commandQueue; }
    id<MTLRenderCommandEncoder> renderEncoder;
    id<MTLCommandBuffer> commandBuffer;
    id<CAMetalDrawable> drawable;
    //Metal을 사용하여 GPU에 접근하고 자원을 생성·관리하기 위한 인터페이스
    id<MTLDevice> device = nil;
    //Metal API에서 GPU에 제출할 명령 버퍼(Command Buffer)를 생성하고 관리하는 객체
    id<MTLCommandQueue> commandQueue = nil;
    //레이어는 Metal을 사용하여 렌더링한 결과물을 화면에 표시할 수 있는 drawable(그림 그릴 수 있는) 표면을 제공
    //dedrived CALayer
    CAMetalLayer* metalLayer = nil;

        
public:

    MetalViewController* view_controller;
	DeviceContext* m_deviceContext = nullptr;
};

