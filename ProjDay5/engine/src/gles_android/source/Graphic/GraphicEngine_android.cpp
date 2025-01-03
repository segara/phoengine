#include "Graphic/GraphicEngine.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <assert.h>
#include <stdexcept>
GraphicEngine::GraphicEngine(void* window)
{
    // Step 1: Get the default display
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    assert(display != EGL_NO_DISPLAY);

    // Step 2: Initialize EGL
    EGLint major,  minor= 0;

    EGLBoolean result = eglInitialize(display, &major,&minor);
    assert(result);

    // Step 3: Choose an EGL config
    const EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, // request OpenGL ES 2.0
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_NONE
    };

    EGLConfig config;
    EGLint numConfigs;
    result = eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    assert(result && numConfigs > 0);

    // Step 4: Create an EGL surface
    assert(window != nullptr);
    surface = eglCreateWindowSurface(display, config, static_cast<ANativeWindow*>(window), nullptr);
    assert(surface != EGL_NO_SURFACE);

    // Step 5: Create an EGL context
    EGLint contextAttribs[] = {
            EGL_CONTEXT_CLIENT_VERSION, 3,
            EGL_NONE
    };

    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
    assert(context != EGL_NO_CONTEXT);

    // Step 6: Make the context current
    result = eglMakeCurrent(display, surface, surface, context);
    assert(result);

    // EGL and OpenGL ES are now initialized and ready for use.
    //printf("EGL initialized: version %d.%d\n", major, minor);
}
GraphicEngine::~GraphicEngine()
{
    if (display != EGL_NO_DISPLAY) {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        if (context != EGL_NO_CONTEXT) {
            eglDestroyContext(display, context);
        }

        if (surface != EGL_NO_SURFACE) {
            eglDestroySurface(display, surface);
        }

        eglTerminate(display);
    }

    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
    surface = EGL_NO_SURFACE;
}
void GraphicEngine::clear(const Vec4& color)
{
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    eglSwapBuffers(display, surface);
}
