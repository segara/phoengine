#include "Game.h"

#include "Window/OWindow.h"
#include "Windows.h"
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
	m_graphicsEngine->clear(Vec4(0.0f, 0.5f, 0.8f, 1.0f));
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
		MSG msg = {};
		if(PeekMessageA(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if(msg.message == WM_QUIT) //WndProc���� ���� �޼���
			{
				m_isRunning = false;
				continue;
			}
			TranslateMessage(&msg); //�ַ� WM_KEYDOWN�̳� WM_KEYUP �޽����� WM_CHAR �޽����� ��ȯ�ϴ� ������ �մϴ�.
			DispatchMessage(&msg);//�Լ��� �޽��� ť���� ���� �޽����� ���޹޾�, �ش� �޽����� ó���ؾ� �� ������ ���ν����� �޽����� �����ϴ�.

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


