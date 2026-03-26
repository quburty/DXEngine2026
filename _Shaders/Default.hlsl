struct VertexInput
{
    float3 Position : Position;
    float4 Color : Color;
};

struct VertexOutput
{
    float4 Position : SV_Position;
    float4 Color : Color;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = float4(input.Position, 1.0f);
    output.Color = input.Color;
    
    return output;
}

float4 PS(VertexOutput output) : SV_Target
{
    return output.Color;
}