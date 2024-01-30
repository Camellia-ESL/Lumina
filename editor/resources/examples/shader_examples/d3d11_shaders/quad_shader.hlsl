float4 v_shader(float3 pos : POSITION) : SV_Position
{
    return float4(pos, 1.0f);
}

float4 p_shader(float4 pos : SV_Position) : SV_Target
{
    return float4(1.0f, 1.0f, 0.0f, 1.0f); 
}