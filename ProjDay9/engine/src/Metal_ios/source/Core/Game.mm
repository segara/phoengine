#include "Game.h"

#include <thread>
#include <chrono>
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#include <simd/simd.h>



Game::Game()
{
    
    m_display = std::make_unique<OWindow>();
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
    simd::float4 clearColor = {0.0f, 0.5f, 1.0f, 1.0f}; 

    m_graphicsEngine->clear(clearColor);
    m_display->Present(false);
}

void Game::onQuit()
{
}

void Game::init()
{
}

void Game:: run()
{
    
    onCreate();
    displayLink = [[DisplayLink alloc]init];
    [displayLink start:[&]() { onUpdate(); }];
}

void Game::quit()
{
	m_isRunning = false;
}


