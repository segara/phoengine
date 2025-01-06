#pragma once
#import <UIKit/UIKit.h>
#include <Metal/Metal.h>

@interface MetalView : UIView
@property(nonatomic, strong) id<MTLDevice> device;
@property(nonatomic, strong) id<MTLCommandQueue> commandQueue;
@property(nonatomic, strong) CAMetalLayer *metalLayer;
- (void)render:(simd_float4)color;
@end

@implementation MetalView {
}
+ (Class)layerClass {
    return [CAMetalLayer class];
}
- (instancetype)init
{
    if ((self = [super initWithFrame:[[UIScreen mainScreen] bounds]]))
    {
        // basic metal setup
        _metalLayer = (CAMetalLayer *)[self layer];
        _device = MTLCreateSystemDefaultDevice();
        
        _metalLayer.device = _device;
        _metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        _metalLayer.frame = self.layer.frame;
        //_metalLayer.framebufferOnly = YES;
      
        self.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        //self.contentScaleFactor = iris::Root::window_manager().current_window()->screen_scale();
        [self setUserInteractionEnabled:YES];
        [super setUserInteractionEnabled:YES];
        [self setBackgroundColor:[UIColor redColor]];

        // Command Queue 초기화
        _commandQueue = [_device newCommandQueue];

    }

    return self;
}



- (void)render:(simd_float4)color {
    // 다음 drawable 가져오기
    id<CAMetalDrawable> drawable = [_metalLayer nextDrawable];
    if (!drawable) return;
    
    // Render Pass Descriptor 설정
    MTLRenderPassDescriptor *renderPassDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
    renderPassDescriptor.colorAttachments[0].texture = drawable.texture;
    renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
    renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(color.x, color.y, color.z, color.w);
    renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
    
    // Command Buffer 및 Render Command Encoder 생성
    id<MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];
    id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
    [renderEncoder endEncoding];
    
    // Drawable 출력 및 Command Buffer 커밋
    [commandBuffer presentDrawable:drawable];
    [commandBuffer commit];
}
@end
