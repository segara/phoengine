#include "Game.h"

#include "Window/OWindow.h"
#include "Windows.h"
Game::Game()
{
	m_display = std::unique_ptr<OWindow>(new OWindow());
}
Game::~Game()
{

}
void Game:: run()
{
	MSG msg;
	while(m_isRunning && !m_display->isClosed())
	{
			if(PeekMessageA(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
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


