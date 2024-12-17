#pragma once

class OWindow
{
public:
	OWindow();
	~OWindow();
    void Present(bool vsync);

	void* m_handle = nullptr;
};

