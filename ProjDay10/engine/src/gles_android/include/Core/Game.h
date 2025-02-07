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

    void init(void* app);
	void run();
    void quit();

    std::shared_ptr<GraphicEngine> m_graphicsEngine;
    std::unique_ptr<OWindow> m_display;

    bool m_isInit = false;

	TriangleDemo* triangleDemo;
private:

	bool m_isRunning = true;

};

