#include "Game.h"

#include "Window/OWindow.h"
#import <Cocoa/Cocoa.h>



Game::Game()
{
	m_display = std::make_unique<OWindow>();
}
Game::~Game()
{

}
void Game:: run()
{
	
	while(m_isRunning)
    {
        NSEvent *event;
        while ((event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                           untilDate:nil
                                              inMode:NSDefaultRunLoopMode
                                             dequeue:YES]))
        {
            if ([event type] == NSEventTypeApplicationDefined) {
                m_isRunning = false;
            }
            [NSApp sendEvent:event];
            [NSApp updateWindows];
        }

        // Sleep to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Game::quit()
{
	m_isRunning = false;
	[NSApp terminate:nil];
}


