#ifndef __DEVICE_CONTEXT_H__
#define __DEVICE_CONTEXT_H__
#pragma once
#include <stddef.h>
#include <vector>
#include <Metal/Metal.h>
#include <MetalKit/MetalKit.h>
class VertexBuffer;

class DeviceContext
{
public:
    DeviceContext();
    void createVertexBuffer(void* list_vertices,
                            size_t size_vertex_struct,
                            size_t size_list,
                            const void* shader_byte_code,
                            size_t size_shader = 0);
    VertexBuffer* getVertexBuffer();
    
    void drawTriangleList(size_t vertex_count, size_t start_vertex_index);
    
    bool release();
    ~DeviceContext();
    
    id<MTLDevice> m_mtlDevice;
    id<MTLRenderCommandEncoder> m_renderEncoder;
    id<MTLRenderPipelineState> m_pipelineState;
    void* m_nativeApp;
private:
  
    VertexBuffer* m_vb;
};
#endif
