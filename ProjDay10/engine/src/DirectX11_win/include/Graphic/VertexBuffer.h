#pragma once
#include <Windows.h>
#include <Vec4.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>

class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer(DeviceContext* device_context, void* list_vertices);
	~VertexBuffer();
	bool load( UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader);
	UINT getSizeVertexList();
	bool release();

private:
	UINT m_size_vertex;
	UINT m_size_list;
private:
	DeviceContext* deviceContext;
	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
	void* m_listVertex = nullptr;
private:
	friend class DeviceContext;
};

