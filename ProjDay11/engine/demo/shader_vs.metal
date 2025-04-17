#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct VS_out
{
    float4 gl_Position [[position]];
};

struct VS_in
{
    float4 in_var_POSITION [[attribute(0)]];
};

vertex VS_out VS(VS_in in [[stage_in]])
{
    VS_out out = {};
    out.gl_Position = in.in_var_POSITION;
    return out;
}

