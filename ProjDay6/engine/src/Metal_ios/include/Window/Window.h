#pragma once
#import <UIKit/UIKit.h>

class OWindow
{
public:
	OWindow();
	~OWindow();
    void Present(bool vsync);
    UIWindow *window;
	void* m_handle;
};

