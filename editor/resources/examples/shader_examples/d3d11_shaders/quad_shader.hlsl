cbuffer input_constant_buffer : register(b0)
{
    float4x4 model_ortho_matrix;
    float4 quad2d_color;
};

struct vertex_shader_output_t
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

vertex_shader_output_t vertex_shader_main(float3 position : POSITION, float4 color : COLOR)
{
    vertex_shader_output_t output;

    output.position = mul(float4(position, 1.0f), model_ortho_matrix);
    output.color = quad2d_color;
    
    return output;
}