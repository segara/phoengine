
//Windows

#include "Window/Window.h" 
#include <cassert>
#include <Windows.h>


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_DESTROY:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onDestroy();
			break;
		}
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}
Window::Window()
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = "gl3dWindow";
	wc.lpfnWndProc = &WndProc;
	
	assert(RegisterClassEx(&wc));

	RECT rc = { 0,0, 1024, 768 };
	AdjustWindowRect(&rc, WS_SYSMENU, false);
	//lpWindowName : 위의 wndclassed 에서 지정해준 lpszClassName
	m_handle = CreateWindowEx(NULL, "gl3dWindow", "text", WS_SYSMENU , CW_USEDEFAULT , CW_USEDEFAULT, rc.right, rc.bottom, NULL, NULL, NULL, NULL);
	assert(m_handle);

	//윈도우의 속성 값을 설정할 때 사용되는 함수입니다. 
	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow((HWND)m_handle, SW_SHOW);
	UpdateWindow((HWND)m_handle);	// 지정된 창에 대한 업데이트 요청을 처리합니다. 이 함수는 해당 창의 클라이언트 영역이 현재 유효하지 않은 경우, WM_PAINT 메시지를 강제로 보내어 창을 다시 그리도록 합니다.
}

Window::~Window()
{
	DestroyWindow((HWND)m_handle);
}

void Window::onDestroy()
{
	m_handle = nullptr;
}

bool Window::isClosed()
{
	return !m_handle;
}
