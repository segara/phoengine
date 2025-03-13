#include "Graphic/DeviceContext.h"
#include "Graphic/VertexBuffer.h"

#include <assert.h>
#include <stdexcept>

DeviceContext::DeviceContext()
{

}

DeviceContext::~DeviceContext()
{
	release();
}

void DeviceContext::createVertexBuffer(void* list_vertices, EGLint size_vertex_struct, EGLint size_list, const void* shader_byte_code, EGLint size_shader)
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


void DeviceContext::drawTriangleList(EGLint vertex_count, EGLint start_vertex_index)
{

	glDrawArrays(GL_TRIANGLES, start_vertex_index, vertex_count);
}

