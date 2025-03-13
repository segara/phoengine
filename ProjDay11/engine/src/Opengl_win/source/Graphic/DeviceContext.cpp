#include "Graphic/DeviceContext.h"
#include "Graphic/VertexBuffer.h"
#include <Windows.h>
#include <assert.h>
#include <stdexcept>

DeviceContext::DeviceContext()
{

}

DeviceContext::~DeviceContext()
{
	release();
}

void DeviceContext::createVertexBuffer(void* list_vertices, GLuint size_vertex_struct, GLuint size_list, const void* shader_byte_code, GLuint size_shader)
{
	m_vb = new VertexBuffer(this, list_vertices);
	m_vb->load(size_vertex_struct, size_list, shader_byte_code, size_shader);
}

bool DeviceContext::release()
{
	
	return true;
}

VertexBuffer* DeviceContext::getVertexBuffer()
{
	return m_vb;
}


void DeviceContext::drawTriangleList(UINT vertex_count, UINT start_vertex_index)
{

	glDrawArrays(GL_TRIANGLES, start_vertex_index, vertex_count);
}

