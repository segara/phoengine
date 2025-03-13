
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


OWindow::OWindow()
{
	// Cocoa 창 생성
    NSRect frame = NSMakeRect(0, 0, 400, 400);
    NSWindow *window = [[NSWindow alloc] initWithContentRect:frame
                                              styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable)
                                                backing:NSBackingStoreBuffered
                                                  defer:NO];
    m_handle = window.contentView; // NSView 가져오기
    [window setTitle:@"metal Window"];
    [window makeKeyAndOrderFront:nil];
    WindowDelegate *delegate = [[WindowDelegate alloc] init];
    [window setDelegate:delegate];
   
}

OWindow::~OWindow()
{
	
}
void OWindow::Present(bool vsync)
{

}
