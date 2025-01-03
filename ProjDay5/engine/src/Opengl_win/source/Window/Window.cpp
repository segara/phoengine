﻿
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
			//OWindow* window = (OWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
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
OWindow::OWindow()
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = "gl3dWindow";
	wc.lpfnWndProc = &WndProc;
	
	auto classId = RegisterClassEx(&wc);
	assert(classId);

	RECT rc = { 0,0, 1024, 768 };
	AdjustWindowRect(&rc, WS_SYSMENU, false);
	//lpWindowName : 위의 wndclassed 에서 지정해준 lpszClassName
	m_handle = CreateWindowEx(NULL, MAKEINTATOM(classId), "text", WS_SYSMENU , CW_USEDEFAULT , CW_USEDEFAULT, rc.right, rc.bottom, NULL, NULL, NULL, NULL);
	assert(m_handle);

	//윈도우의 속성 값을 설정할 때 사용되는 함수입니다. 
	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow((HWND)m_handle, SW_SHOW);
	UpdateWindow((HWND)m_handle);	// 지정된 창에 대한 업데이트 요청을 처리합니다. 이 함수는 해당 창의 클라이언트 영역이 현재 유효하지 않은 경우, WM_PAINT 메시지를 강제로 보내어 창을 다시 그리도록 합니다.


}

OWindow::~OWindow()
{
	//DestroyWindow((HWND)m_handle);
}

void OWindow::Present(bool vsync)
{
	HDC dummyDC = GetDC((HWND)m_handle);
	//wglSwapIntervalEXT(vsync);
	wglSwapLayerBuffers(GetDC(HWND(m_handle)), WGL_SWAP_MAIN_PLANE);

}