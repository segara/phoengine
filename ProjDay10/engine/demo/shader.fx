struct VS_INPUT
{
    float4 position : POSITION; // 버텍스 위치

};

struct VS_OUTPUT
{
    float4 position : SV_POSITION; // 클립 공간 좌표

};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = input.position; // 입력 위치를 그대로 출력

    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    return float4(0.8f,0.9f, 0.4f, 1.0f );   
}
