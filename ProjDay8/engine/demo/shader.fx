float4 vsmain( float4 pos : POSITION ) : SV_POSITION  // 입력 레이아웃에서 POSITION 의미와 매핑
    {
        return pos;
    }

 float4 psmain( float4 pos : SV_POSITION ) : SV_Target
 {
        return float4(0.8f,0.9f, 0.4f, 1.0f );   
 }
