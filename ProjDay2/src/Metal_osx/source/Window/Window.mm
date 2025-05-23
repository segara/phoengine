
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
    [window setTitle:@"gl3dWindow"];
    [window makeKeyAndOrderFront:nil];
    WindowDelegate *delegate = [[WindowDelegate alloc] init];
    [window setDelegate:delegate];
   
}

Window::~Window()
{
	
}
