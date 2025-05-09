#include "Game.h"

#include "Window/Window.h"
#include <thread>
#include <chrono>
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#include <simd/simd.h>


@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (assign) Game *game; 
//컴파일러는 자동으로 _game이라는 인스턴스 변수를 생성합니다.
//언더스코어를 사용하면 인스턴스 변수와 프로퍼티 이름을 명확히 구분할 수 있습니다.
//이렇게 하면 프로퍼티 접근자 메서드(self.game ..)를 사용하지 않고도 인스턴스 변수를 직접 참조할 수 있습니다.
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
}

- (void)applicationWillTerminate:(NSNotification *)notification {
    _game->quit();
}
@end



AppDelegate *appDelegate;

Game::Game()
{
    [NSApplication sharedApplication];
    appDelegate = [[AppDelegate alloc] init];
    appDelegate.game = this;
    [NSApp setDelegate:appDelegate];//  set the delegate
	m_display = std::make_unique<Window>();
    m_graphicsEngine = std::make_unique<GraphicEngine>(m_display->m_handle);
    
   
}
Game::~Game()
{

}
void Game::onCreate()
{
}

void Game::onUpdate()
{
    simd::float4 clearColor = {0.3f, 0.5f, 0.8f, 1.0f}; // R=1.0, G=0.0, B=0.0, A=1.0

    m_graphicsEngine->clear(clearColor);
    m_display->Present(false);
}

void Game::onQuit()
{
}
void Game:: run()
{
    onCreate();
    while(m_isRunning)
    {
        NSEvent *event;
        //windows의 poll event
        //event에 대해 반복문으로 체크
        while (event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                untilDate: [NSDate distantPast]
                               inMode:NSDefaultRunLoopMode
                               dequeue:YES])
        {
            [NSApp sendEvent:event];
            [NSApp updateWindows];
        }
        
        // Sleep to reduce CPU usage
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
        onUpdate();
    }
    onQuit();
}

void Game::quit()
{
	m_isRunning = false;
}


