#include "Graphic/DeviceContext.h"
#include "Graphic/VertexBuffer.h"
#include <Windows.h>
#include <assert.h>
#include <stdexcept>

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>


DeviceContext::DeviceContext(ID3D11Device* d3d_device, ID3D11DeviceContext* device_context) : m_d3d_device(d3d_device), m_device_context(device_context)
{
}
DeviceContext::~DeviceContext()
{
}
ID3D11Device* DeviceContext::getDevice()
{
	return m_d3d_device;
}

ID3D11DeviceContext* DeviceContext::getDeviceContext()
{
	return m_device_context;
}

bool DeviceContext::release()
{
	return true;
}

void DeviceContext::createVertexBuffer(void* list_vertices, UINT size_vertex_struct, UINT size_list, void* shader_byte_code, UINT size_shader)
{
	m_vb = new VertexBuffer(this, list_vertices);
	m_vb->load(size_vertex_struct, size_list, shader_byte_code, size_shader);

	UINT stride = m_vb->m_size_vertex;
	UINT offset = 0;
	m_device_context->IASetVertexBuffers(0, 1, &m_vb->m_buffer, &stride, &offset);
	m_device_context->IASetInputLayout(m_vb->m_layout);
}

VertexBuffer* DeviceContext::getVertexBuffer()
{
	return m_vb;
}


void DeviceContext::drawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->Draw(vertex_count, start_vertex_index);
}

