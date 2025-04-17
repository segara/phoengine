#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct PS_out
{
    float4 out_var_SV_Target [[color(0)]];
};

fragment PS_out PS()
{
    PS_out out = {};
    out.out_var_SV_Target = float4(0.800000011920928955078125, 0.89999997615814208984375, 0.4000000059604644775390625, 1.0);
    return out;
}

