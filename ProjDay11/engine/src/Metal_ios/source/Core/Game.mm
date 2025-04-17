#include "Game.h"

#include "Window/Window.h"
#include <thread>
#include <chrono>

#import <Foundation/Foundation.h>
#include <simd/simd.h>



Game::Game()
{
    
    m_display = std::make_unique<OWindow>();
    m_graphicsEngine = std::make_unique<GraphicEngine>(m_display->m_handle);
    triangleDemo = new TriangleDemo(this->m_graphicsEngine);
    triangleDemo->onCreate();

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
    triangleDemo->onUpdate();
    m_display->Present(false);
    m_graphicsEngine->present();
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
    onQuit();
}

void Game::quit()
{
	m_isRunning = false;
}


