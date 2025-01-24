#include "Graphic/VertexBuffer.h"
#include "Graphic/GraphicEngine.h"
#include <windows.h>
#include <assert.h>
#include <stdexcept>
// Include necessary DirectX headers
#include <d3d11.h>
#include <dxgi.h>

VertexBuffer::VertexBuffer(DeviceContext* device_context, void* list_vertices) : deviceContext(device_context),m_listVertex(list_vertices), m_layout(0), m_buffer(0)
{

}

bool VertexBuffer::load(UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader)
{
	if (m_buffer)m_buffer->Release();
	if (m_layout)m_layout->Release();

	//D3D11_BUFFER_DESC : DirectX 11에서 버퍼(예: 버텍스 버퍼, 인덱스 버퍼, 상수 버퍼 등)의 속성을 정의하는 데 사용

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	//D3D11_SUBRESOURCE_DATA는 버퍼를 생성할 때 초기 데이터를 설정하는 데 사용
	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = m_listVertex;

	m_size_vertex = size_vertex;
	m_size_list = size_list;

	if (FAILED(deviceContext->getDevice()->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		return false;
	}

	//이 코드는 DirectX 11에서 **입력 레이아웃(Input Layout)**을 생성하는 과정을 보여줍니다.
	//입력 레이아웃은 쉐이더가 입력 데이터를 해석하는 방식을 정의합니다.
	//주로 버텍스 버퍼(Vertex Buffer)의 구조를 설명하는 역할
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA ,0}
	};

	UINT size_layout = ARRAYSIZE(layout);

	if (FAILED(deviceContext->getDevice()->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout)))
	{
		return false;
	}

	return true;
}

UINT VertexBuffer::getSizeVertexList()
{
	return this->m_size_list;
}

bool VertexBuffer::release()
{
	m_layout->Release();
	m_buffer->Release();
	delete this;
	return true;
}


VertexBuffer::~VertexBuffer()
{
}
