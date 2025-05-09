#pragma once

class Window
{
public:
	Window();
	~Window();
    void Present(bool vsync);

	void* m_handle = nullptr;
};

