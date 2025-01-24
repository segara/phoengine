#pragma once
#include <memory>


#include "Window/Window.h"
#include "Graphic/GraphicEngine.h"
#include "Triangle.h"
#include "memory.h"
class Game
{
public:
	Game();
	~Game();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onQuit();

	void init();
	void run();
    void quit();
private:

	
	bool m_isRunning = true;
	std::shared_ptr<GraphicEngine> m_graphicsEngine;
	std::unique_ptr<OWindow> m_display;

	TriangleDemo* triangleDemo;
};

