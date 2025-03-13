#include <metal_stdlib>
using namespace metal;

// 정점 출력 구조체: 클립 공간 좌표와 색상 데이터를 저장합니다.
struct VertexOut {
    float4 position [[position]]; // 클립 공간 좌표
};

// 정점 셰이더:
// - vertexId: 현재 처리 중인 정점 인덱스
// - positions: 버퍼(인덱스 0)에 저장된 float3 타입의 정점 위치 배열

vertex VertexOut vertexMain(const device float3* positions [[buffer(0)]],
                           uint vertexID [[vertex_id]])
{
    VertexOut out;
    out.position = float4(positions[vertexID], 1.0);
    // Other vertex processing
    return out;
}
// 프래그먼트 셰이더:
// - vertex shader에서 보간된 VertexOut 데이터를 받아 최종 색상을 반환합니다.
fragment float4 fragmentMain(VertexOut in [[stage_in]])
{
    return (1,1,1,1);
}
