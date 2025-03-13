#ifndef VertexBuffer_H
#define VertexBuffer_H

#pragma once
class DeviceContext;


#import <Metal/Metal.h>
#include <cstddef>

class VertexBuffer {
public:
    // 생성자: Metal device와 정점 데이터, 각 정점의 크기, 정점 개수를 전달
    VertexBuffer(DeviceContext* device_context, const void* vertices);
    ~VertexBuffer();
    bool load(std::size_t size_vertex, std::size_t size_list, const void* shader_byte_code = nullptr, size_t size_byte_shader = 0);

    // 생성된 Metal 버퍼 (MTLBuffer)
    id<MTLBuffer> vertexBuffer() const { return m_vertexBuffer; }
    std::size_t getSizeVertexList();
    void release();
    id<MTLBuffer> m_vertexBuffer;
private:
    size_t m_size_vertex;     // Size of a single vertex
    size_t m_size_list;       // Number of vertices
    const void* m_list_vertex;      // Vertex data (raw pointer)
    DeviceContext* m_deviceContex;
    id<MTLDevice> m_device;
  
private:
    friend class DeviceContext;
};

#endif /* VertexBuffer_H */
