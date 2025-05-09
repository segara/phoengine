
//Windows

#include "Window/Window.h"
#include "glad/gl.h"
#include "glad/wgl.h"
#include <Windows.h>
#include <iostream>
#include <cassert>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_DESTROY:
		{
			//Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			break;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
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
	
	auto classId = RegisterClassEx(&wc);
	assert(classId);

	RECT rc = { 0,0, 1024, 768 };
	AdjustWindowRect(&rc, WS_SYSMENU, false);
	//lpWindowName : ���� wndclassed ���� �������� lpszClassName
	m_handle = CreateWindowEx(NULL, MAKEINTATOM(classId), "text", WS_SYSMENU , CW_USEDEFAULT , CW_USEDEFAULT, rc.right, rc.bottom, NULL, NULL, NULL, NULL);
	assert(m_handle);

	//�������� �Ӽ� ���� ������ �� ���Ǵ� �Լ��Դϴ�. 
	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow((HWND)m_handle, SW_SHOW);
	UpdateWindow((HWND)m_handle);	// ������ â�� ���� ������Ʈ ��û�� ó���մϴ�. �� �Լ��� �ش� â�� Ŭ���̾�Ʈ ������ ���� ��ȿ���� ���� ���, WM_PAINT �޽����� ������ ������ â�� �ٽ� �׸����� �մϴ�.


}

Window::~Window()
{
	//DestroyWindow((HWND)m_handle);
}

void Window::Present(bool vsync)
{
	HDC dummyDC = GetDC((HWND)m_handle);
	//wglSwapIntervalEXT(vsync);
	wglSwapLayerBuffers(GetDC(HWND(m_handle)), WGL_SWAP_MAIN_PLANE);

}