
//Windows

#include "Window/Window.h"
#import <Cocoa/Cocoa.h>
#include <cassert>

@interface WindowDelegate : NSObject <NSWindowDelegate>
@end

@implementation WindowDelegate
- (void)windowWillClose:(NSNotification *)notification {
    NSLog(@"Window is closing!");
    // This will close the entire application
       [NSApp terminate:nil];
   
}
@end


Window::Window()
{
	// Cocoa 창 생성
    NSRect frame = NSMakeRect(0, 0, 1024, 768);
    NSWindow *window = [[NSWindow alloc] initWithContentRect:frame
                                              styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable)
                                                backing:NSBackingStoreBuffered
                                                  defer:NO];
    // NSView 넘겨주기
    //NSView는 macOS 앱에서 화면에 무언가를 보여주고 싶을 때 사용하는 "화면 박스"
    m_handle = window.contentView;
    [window setTitle:@"metal Window"];
    [window makeKeyAndOrderFront:nil];
    WindowDelegate *delegate = [[WindowDelegate alloc] init];
    [window setDelegate:delegate];
   
}

Window::~Window()
{
	
}
void Window::Present(bool vsync)
{

}
