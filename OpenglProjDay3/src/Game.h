#pragma once
#include <memory>

#include "Window/OWindow.h"
#include "Graphic/GraphicEngine.h"
#include "memory.h"
class Game
{
public:
	Game();
	~Game();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onQuit();

	void run();
    void quit();
private:

	
	bool m_isRunning = true;
	std::unique_ptr<GraphicEngine> m_graphicsEngine;
	std::unique_ptr<OWindow> m_display;
};
