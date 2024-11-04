#include "Game.h"

#include "Window/OWindow.h"
#include "Windows.h"
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
		Sleep(1);
	}
}

void Game::quit()
{
	m_isRunning = false;
}


