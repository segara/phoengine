#include "VertexBuffer.h"
#include "DeviceContext.h"

VertexBuffer::VertexBuffer(DeviceContext* device_context, void* list_vertices)
    : m_vbo(0), m_vao(0), m_size_vertex(0), m_size_list(0), m_list_vertex(list_vertices), deviceContext(device_context)
{
    // Generate a VAO for managing vertex attributes
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Generate a VBO to store vertex data
    glGenBuffers(1, &m_vbo);
}

VertexBuffer::~VertexBuffer()
{
    release();
}

bool VertexBuffer::load(GLuint size_vertex, GLuint size_list, const void* shader_byte_code, size_t size_byte_shader)
{
    m_size_vertex = size_vertex;
    m_size_list = size_list;

    // Bind the VBO and upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, size_vertex * size_list, m_list_vertex, GL_STATIC_DRAW);

    // Bind the VAO and configure vertex attributes
    glBindVertexArray(m_vao);

    // Example: Bind a single vertex attribute
    // Assuming shader_byte_code describes attributes (e.g., positions as 3 floats)
    // Layout 0 for position: Replace with your actual layout definition
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size_vertex, (void*)0);
    glEnableVertexAttribArray(0);

    return true;
}

GLuint VertexBuffer::getSizeVertexList()
{
    return m_size_list;
}

bool VertexBuffer::release()
{
    if (m_vbo != 0)
    {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
    }

    if (m_vao != 0)
    {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }

    return true;
}