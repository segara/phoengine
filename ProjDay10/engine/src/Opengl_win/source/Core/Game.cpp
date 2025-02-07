#include "Game.h"

#include "Window/Window.h"
#include "Windows.h"
Game::Game()
{
	m_display = std::make_unique<OWindow>();
	m_graphicsEngine = std::make_unique<GraphicEngine>(m_display->m_handle);

	triangleDemo = new TriangleDemo(m_graphicsEngine);
}
Game::~Game()
{

}
void Game::onCreate()
{
	triangleDemo->onCreate();
}

void Game::onUpdate()
{
	m_graphicsEngine->clear(Vec4(0.0f, 0.5f, 0.8f, 1.0f));

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
	while(m_isRunning)
	{
		MSG msg = {};
		if(PeekMessageA(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if(msg.message == WM_QUIT) //WndProc에서 보낸 메세지
			{
				m_isRunning = false;
				continue;
			}
			TranslateMessage(&msg); //주로 WM_KEYDOWN이나 WM_KEYUP 메시지를 WM_CHAR 메시지로 변환하는 역할을 합니다.
			DispatchMessage(&msg);//함수는 메시지 큐에서 꺼낸 메시지를 전달받아, 해당 메시지를 처리해야 할 윈도우 프로시저로 메시지를 보냅니다.

		}
		//Sleep(1);
		onUpdate();
	}
	onQuit();

}

void Game::quit()
{
	m_isRunning = false;
}


