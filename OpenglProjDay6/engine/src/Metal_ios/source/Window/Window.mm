#include "Window.h"
#include "MetalView.h"
#include "MetalViewController.h"

#include <cassert>

OWindow::OWindow() {
    NSLog(@"[UIApplication sharedApplication].windows 1 = %@", [UIApplication sharedApplication].windows);
   
            CGRect rect = [[UIScreen mainScreen] bounds];
            // create a new window the size of the screen
            window = [[UIWindow alloc] initWithFrame:rect];
            window.hidden = NO;
 
 
            auto *view_controller = [[MetalViewController alloc]init];
            window.rootViewController = view_controller;
           
            view_controller.window = window;
            
            if (!view_controller.metalView) {
                NSLog(@"View is not initialized!");
            }
            [window addSubview:view_controller.metalView];
            view_controller.metalView.hidden = NO;
             m_handle = (__bridge void*)window;
          

    //퍼스트 리스폰더는 사용자 입력 이벤트(터치, 키보드 입력 등)를 가장 먼저 처리하는 객체입니다.
    //보통 입력을 받고 있는 텍스트 필드나 텍스트 뷰가 퍼스트 리스폰더가 됩니다.
   // resignFirstResponder는 해당 객체가 더 이상 퍼스트 리스폰더로서의 역할을 하지 않도록 요청합니다.
    
    
    // iOS에서 UIWindow 객체를 화면에 표시하고 해당 창을 "키 윈도우(Key Window)"로 설정하는 메서드 호출입니다. 이 메서드는 애플리케이션의 사용자 인터페이스를 활성화하고 표시하는 데 사용됩니다.

    [window makeKeyAndVisible];
    [window becomeFirstResponder];
    
    NSLog(@"Current key window: %@", [UIApplication sharedApplication].keyWindow);

    
}

OWindow::~OWindow() {
}

void OWindow::Present(bool vsync) {
    //todo : metal view 의 render()코드가 이쪽으로
}
