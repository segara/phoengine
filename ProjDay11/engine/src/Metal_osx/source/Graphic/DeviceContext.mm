#include "Graphic/DeviceContext.h"
#include "Graphic/VertexBuffer.h"

#include <assert.h>
#include <stdexcept>

DeviceContext::DeviceContext()
{
    // Get the default Metal device
     m_vb = nullptr;
}

DeviceContext::~DeviceContext()
{
	release();
}

void DeviceContext::createVertexBuffer(void* list_vertices,
                          size_t size_vertex_struct,
                          size_t size_list,
                          const void* shader_byte_code,
                          size_t size_shader) 
{
    m_vb = new VertexBuffer(this, list_vertices);
    m_vb->m_device = m_mtlDevice;
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


void DeviceContext::drawTriangleList(size_t vertex_count, size_t start_vertex_index)
{
    //set vertex position buffer to index 0 in the buffer argument table starting at offset 0 in the buffer
    
    // Ensure that you have a valid MTLRenderCommandEncoder
    if (m_renderEncoder && m_pipelineState) {

        // 렌더 인코더에 파이프라인 상태 설정
        [m_renderEncoder setRenderPipelineState:m_pipelineState];
        [m_renderEncoder setVertexBuffer:m_vb->m_vertexBuffer offset:0 atIndex:0];
        [m_renderEncoder setFrontFacingWinding:MTLWindingClockwise]; //gl과 통일

        // Metal equivalent of glDrawArrays(GL_TRIANGLES, start_vertex_index, vertex_count)
        [m_renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle
                              vertexStart:start_vertex_index
                              vertexCount:vertex_count];
    }
}

