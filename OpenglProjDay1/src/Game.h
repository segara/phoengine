#pragma once
#include <memory>

#include "Window/OWindow.h"
#include "memory.h"
class Game
{
public:
	Game();
	~Game();
	void run();
private:

	void quit();
	bool m_isRunning = true;
	std::unique_ptr<OWindow> m_display;
};

