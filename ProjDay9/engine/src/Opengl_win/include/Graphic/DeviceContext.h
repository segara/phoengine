#pragma once
#include <vector>
#include "glad/gl.h"
#include "glad/wgl.h"

class VertexBuffer;

class DeviceContext
{
public:
    DeviceContext();
    void createVertexBuffer(void* list_vertices, GLuint size_vertex_struct, GLuint size_list, const void* shader_byte_code = nullptr, GLuint size_shader = 0);
    VertexBuffer* getVertexBuffer();

    void drawTriangleList(GLuint vertex_count, GLuint start_vertex_index);

    bool release();
    ~DeviceContext();

private:

    VertexBuffer* m_vb;
};