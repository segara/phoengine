#pragma once

#include <EGL/egl.h>
#include <GLES3/gl3.h>

class DeviceContext;

class VertexBuffer
{
public:
    VertexBuffer(DeviceContext* device_context, void* list_vertices);
    ~VertexBuffer();

    bool load(GLuint size_vertex, GLuint size_list, const void* shader_byte_code = nullptr, size_t size_byte_shader = 0);
    GLuint getSizeVertexList();
    bool release();

private:
    GLuint m_vbo;             // OpenGL Vertex Buffer Object
    GLuint m_vao;             // OpenGL Vertex Array Object
    GLuint m_size_vertex;     // Size of a single vertex
    GLuint m_size_list;       // Number of vertices
    void* m_list_vertex;      // Vertex data (raw pointer)
    DeviceContext* deviceContext; // Associated device context

private:
    friend class DeviceContext;
};
