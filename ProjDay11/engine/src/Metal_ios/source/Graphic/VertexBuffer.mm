#include "VertexBuffer.h"
#include "DeviceContext.h"

VertexBuffer::VertexBuffer(DeviceContext* device_context, const void* vertices)
:m_size_vertex(0), m_size_list(0), m_list_vertex(vertices),m_deviceContex(device_context)
{
    
}

VertexBuffer::~VertexBuffer()
{
    // ARC 환경에서는 별도 해제가 필요하지 않습니다.
}

bool VertexBuffer::load(std::size_t size_vertex, std::size_t size_list, const void* shader_byte_code, size_t size_byte_shader)
{
    m_size_vertex = size_vertex;
    m_size_list = size_list;
    std::size_t bufferSize = m_size_vertex * m_size_list;

    // Metal 버퍼 생성: 공유 메모리 옵션 사용
    //newBufferWithBytes:length:options: 또는 newBufferWithLength:options: 를 사용할 때, Metal은 16바이트 단위로 정렬된 메모리를 요구합니다.
    m_vertexBuffer = [m_device newBufferWithBytes:m_list_vertex
                                           length:bufferSize
                                          options:MTLResourceStorageModeShared];
    
    return true;
}
size_t VertexBuffer::getSizeVertexList()
{
    return m_size_list;
}
void VertexBuffer::release()
{
  
}
