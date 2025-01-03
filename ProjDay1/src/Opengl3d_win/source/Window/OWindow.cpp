
//Windows

#include "Window/OWindow.h"

#include <cassert>
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_DESTROY:
		{
			OWindow* window = (OWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onDestroy();
			break;
		}
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}
OWindow::OWindow()
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = "gl3dWindow";
	wc.lpfnWndProc = &WndProc;
	
	assert(RegisterClassEx(&wc));

	RECT rc = { 0,0, 1024, 768 };
	AdjustWindowRect(&rc, WS_SYSMENU, false);
	//lpWindowName : ���� wndclassed ���� �������� lpszClassName
	m_handle = CreateWindowEx(NULL, "gl3dWindow", "text", WS_SYSMENU , CW_USEDEFAULT , CW_USEDEFAULT, rc.right, rc.bottom, NULL, NULL, NULL, NULL);
	assert(m_handle);

	//�������� �Ӽ� ���� ������ �� ���Ǵ� �Լ��Դϴ�. 
	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow((HWND)m_handle, SW_SHOW);
	UpdateWindow((HWND)m_handle);	// ������ â�� ���� ������Ʈ ��û�� ó���մϴ�. �� �Լ��� �ش� â�� Ŭ���̾�Ʈ ������ ���� ��ȿ���� ���� ���, WM_PAINT �޽����� ������ ������ â�� �ٽ� �׸����� �մϴ�.
}

OWindow::~OWindow()
{
	DestroyWindow((HWND)m_handle);
}

void OWindow::onDestroy()
{
	m_handle = nullptr;
}

bool OWindow::isClosed()
{
	return !m_handle;
}
