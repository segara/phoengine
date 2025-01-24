#include "Graphic/GraphicEngine.h"
#include <windows.h>
#include "glad/gl.h"
#include "glad/wgl.h"
#include <assert.h>
#include <stdexcept>
GraphicEngine:: GraphicEngine(void* hwnd)
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

  
    // OpenGL 컨텍스트 생성 및 활성화
    //HGLRC는 기본적으로 Windows의 핸들 타입으로 정의된 구조체 포인터입니다.
    //HGLRC는 Windows의 디바이스 컨텍스트(HDC)와 연결됩니다.
    //wglMakeCurrent를 통해 특정 HGLRC를 활성화하고 OpenGL 호출이 해당 컨텍스트에 적용되도록 설정합니다.
    
    HGLRC temp_context = NULL;
    temp_context = wglCreateContext(dummyDC);

    if (NULL == (temp_context))
    {
        fprintf(stderr, "Failed to initialize wglCreateContext\n");
    }
    bool res = wglMakeCurrent(dummyDC, temp_context);
    assert(res);

    // wglGetProcAddress
    // Windows 플랫폼에서 OpenGL 확장 함수의 주소를 가져오는 데 사용되는 함수입니다. 
    //이는 OpenGL 라이브러리에 포함되지 않은 확장 함수나 기본 함수의 포인터를 가져오는 데 필수적입니다.
    //wglGetProcAddress("glActiveTexture"); 이런식으로 사용
   
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

    m_deviceContext = new DeviceContext();
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

void GraphicEngine::present()
{
}
