#include "Graphic/GraphicEngine.h"
#include <windows.h>
#include "glad/gl.h"
#include "glad/wgl.h"
#include <assert.h>
#include <stdexcept>
GraphicEngine::GraphicEngine(void* hwnd)
{

    HDC dummyDC = GetDC((HWND)hwnd);

    PIXELFORMATDESCRIPTOR pfd = { };
    pfd.nSize = sizeof(pfd);
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);  // Set the size of the PFD to the size of the class
    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;   // Enable double buffering, opengl support and drawing to a window
    pfd.iPixelType = PFD_TYPE_RGBA; // Set our application to use RGBA pixels
    pfd.cColorBits = 32;        // Give us 32 bits of color information (the higher, the more colors)
    pfd.cDepthBits = 32;        // Give us 32 bits of depth information (the higher, the more depth levels)
    pfd.iLayerType = PFD_MAIN_PLANE;    // Set the layer of the PFD
    int format = ChoosePixelFormat(dummyDC, &pfd);
    if (format == 0 || SetPixelFormat(dummyDC, format, &pfd) == FALSE) {
        fprintf(stderr, "Failed to SetPixelFormat GLAD\n");
    }

  
    // OpenGL ���ؽ�Ʈ ���� �� Ȱ��ȭ
    //HGLRC�� �⺻������ Windows�� �ڵ� Ÿ������ ���ǵ� ����ü �������Դϴ�.
    //HGLRC�� Windows�� ����̽� ���ؽ�Ʈ(HDC)�� ����˴ϴ�.
    //wglMakeCurrent�� ���� Ư�� HGLRC�� Ȱ��ȭ�ϰ� OpenGL ȣ���� �ش� ���ؽ�Ʈ�� ����ǵ��� �����մϴ�.
    
    HGLRC temp_context = NULL;
    temp_context = wglCreateContext(dummyDC);

    if (NULL == (temp_context))
    {
        fprintf(stderr, "Failed to initialize wglCreateContext\n");
    }
    bool res = wglMakeCurrent(dummyDC, temp_context);
    assert(res);

    // wglGetProcAddress
    // Windows �÷������� OpenGL Ȯ�� �Լ��� �ּҸ� �������� �� ���Ǵ� �Լ��Դϴ�. 
    //�̴� OpenGL ���̺귯���� ���Ե��� ���� Ȯ�� �Լ��� �⺻ �Լ��� �����͸� �������� �� �ʼ����Դϴ�.
    //wglGetProcAddress("glActiveTexture"); �̷������� ���
   
    if (!gladLoadWGL(dummyDC, (GLADloadfunc)wglGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
    }
 
    // Glad Loader!
    if (!gladLoaderLoadGL()) {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(temp_context);
        ReleaseDC((HWND)hwnd, dummyDC);
        DestroyWindow((HWND)hwnd);
    }
}
GraphicEngine::~GraphicEngine()
{
    // Clean-up:
    //if (opengl_context)
    //    wglDeleteContext(opengl_context);
    //if (hdc)
    //    ReleaseDC(hWnd, hdc);
    //if (hWnd)
    //    DestroyWindow(hWnd);
}
void GraphicEngine::clear(const Vec4& color)
{
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}
