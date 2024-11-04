
//Windows

#include "Window/OWindow.h"

#include <cassert>
#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (assign) NSWindow *window;
@end


@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
}

- (void)applicationWillTerminate:(NSNotification *)notification {

}
- (void)windowWillClose:(NSNotification *)notification {
    // Handle the window close event
    [[NSApplication sharedApplication] terminate:nil];
}

@end

OWindow::OWindow()
{
	 // Initialize Cocoa application
    [NSApplication sharedApplication];
    AppDelegate *appDelegate = [[AppDelegate alloc] init];
    [NSApp setDelegate:appDelegate];
	// Cocoa 창 생성
    NSRect frame = NSMakeRect(0, 0, 1024, 768);
    appDelegate.window = [[NSWindow alloc] initWithContentRect:frame
                                              styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable)
                                                backing:NSBackingStoreBuffered
                                                  defer:NO];
    [appDelegate.window setTitle:@"gl3dWindow"];
    [appDelegate.window makeKeyAndOrderFront:nil];
}

OWindow::~OWindow()
{
	
}