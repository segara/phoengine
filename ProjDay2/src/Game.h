#pragma once
#include <memory>

#include "Window/Window.h"
class Game
{
public:
	Game();
	~Game();
	void run();
    void quit();
private:
	bool m_isRunning = true;
	std::unique_ptr<Window> m_display;
};

