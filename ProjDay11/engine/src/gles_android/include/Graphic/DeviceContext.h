#pragma once
#include <vector>
#include <EGL/egl.h>
#include <GLES3/gl3.h>

class VertexBuffer;

class DeviceContext
{
public:
    DeviceContext();
    void createVertexBuffer(void* list_vertices, EGLint size_vertex_struct, EGLint size_list, const void* shader_byte_code = nullptr, EGLint size_shader = 0);
    VertexBuffer* getVertexBuffer();

    void drawTriangleList(EGLint vertex_count, EGLint start_vertex_index);

    bool release();
    ~DeviceContext();

    void* m_nativeApp;
private:

    VertexBuffer* m_vb;
};