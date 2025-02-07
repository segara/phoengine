#pragma once
#include <memory>
#import <UIKit/UIKit.h>

#include "Window/Window.h"
#include "Graphic/GraphicEngine.h"
#include "memory.h"
#include "DisplayLink.h"
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
    
    std::unique_ptr<GraphicEngine> m_graphicsEngine;
    std::unique_ptr<OWindow> m_display;
private:
	bool m_isRunning = true;
    DisplayLink* displayLink;
};

