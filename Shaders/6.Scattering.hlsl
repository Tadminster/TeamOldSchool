#include "Common.hlsl"

struct VertexPT
{
    float4 pos : POSITION;
    float2 uv : UV;
};
struct PixelInput
{
    float4 pos : SV_Position;
    float2 uv : UV;
    float3 oPosition : Position;
};

PixelInput VS(VertexPT input)
{
    PixelInput output;
    
    output.pos.xyz = mul(input.pos.xyz, (float3x3) View);
    output.pos.w = 1.0f;
    
    output.pos = mul(output.pos, Proj);
    
    output.oPosition = -input.pos.xyz;
    output.uv = input.uv;
    
    return output;
}

static const float g = -0.980f;
static const float g2 = g * g;
static const float Exposure = -1.5f;

Texture2D rayleighMap : register(t10);
Texture2D mieMap : register(t11);

float GetRayleighPhase(float c)
{
    return 0.75f * (1.0f + c);
}

//태양의 크기를 결정
float GetMiePhase(float c, float c2)
{
    float3 result = 0;
    result.x = 1.5f * ((1.0f - g2) / (2.0f + g2));
    result.y = 1.0f + g2;
    result.z = 2.0f * g;
 
    return (result.x * (1.0f + c2) / pow(result.y - result.z * c, 1.5f)) * 0.005f;
}

//float3 HDR(float3 LDR)
//{
//    return 1.0f - exp(Exposure * LDR);
//}

float4 PS(PixelInput input) : SV_Target
{
    float3 sunDirection = -normalize(DirLight.xyz);
    
    float temp = dot(sunDirection, input.oPosition) / length(input.oPosition);
    float temp2 = temp * temp;
    
    float3 rSamples = rayleighMap.Sample(SamplerDefault, input.uv);
    float3 mSamples = mieMap.Sample(SamplerDefault, input.uv);
    
    float3 color = (0, 0, 0);
    
    float sun = GetMiePhase(temp, temp2);
    // 인공태양
    //color = GetRayleighPhase(temp2) * rSamples + float3(sun, sun, sun);
    color = GetRayleighPhase(temp2) * rSamples + sun * mSamples;
    //color = HDR(color);
    
    color += max(0, (1 - color.rgb)) * float3(0.05f, 0.05f, 0.1f);
    
    float intensity = saturate(DirLight.y);
    
    return float4(color, 1) + TextureD.Sample(SamplerDefault, input.uv) * intensity;
    
}