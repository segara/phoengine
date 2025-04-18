#pragma once
#include <memory>
#include <android_native_app_glue.h>

#include "Window/OWindow.h"
#include "Graphic/GraphicEngine.h"

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

	std::unique_ptr<GraphicEngine> m_graphicsEngine;
	std::unique_ptr<OWindow> m_window;
    bool m_isInit = false;
private:
	bool m_isRunning = true;
};
