#include "Graphic/GraphicEngine.h"
#include "Window/Window.h"
#include "MetalView.h"
#include <stdexcept>




GraphicEngine::GraphicEngine(void* hwnd) {
    
    UIWindow* window = (__bridge UIWindow*)hwnd;
    
    view_controller = [[MetalViewController alloc]init];
    window.rootViewController = view_controller;
   
    view_controller.window = (__bridge UIWindow*)hwnd;
    
    if (!view_controller.metalView) {
        NSLog(@"View is not initialized!");
    }

    view_controller.metalView.hidden = NO;

}

GraphicEngine::~GraphicEngine() {
}

void GraphicEngine::clear(const simd::float4& color) {
    [view_controller renderLoop:color];
}
