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
    void quit();
private:

	
	bool m_isRunning = true;
	std::unique_ptr<OWindow> m_display;
};

