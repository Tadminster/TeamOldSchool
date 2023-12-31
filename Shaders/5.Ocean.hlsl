#include "Common.hlsl"

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : UV0;
    float3 Normal : NORMAL0;
    float4 Weights : WEIGHTS0;
    float4 Color : COLOR0;
};
struct PixelInput
{
    float4 Position : SV_POSITION;
    float2 Uv : UV0;
    float4 wPosition : POSITION0;
    float3 Normal : NORMAL0;
    float4 Weights : WEIGHTS0;
    float4 Color : COLOR0;
};

PixelInput VS(VertexInput input)
{
   
    PixelInput output;
    output.Uv = input.Uv;
    //  o           =  i X W
    output.Position = mul(input.Position, World);
    output.wPosition = output.Position;
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Proj);
    output.Normal = mul(input.Normal, (float3x3) World);
    output.Weights = input.Weights;
    output.Color = input.Color;
    return output;
}



float4 PS(PixelInput input) : SV_TARGET
{
    float4 BaseColor = input.Color;
	//float4 BaseColor = 0;
    BaseColor.a = 1.0f;
	  [flatten]
    if (Ka.a)
        BaseColor.rgb += TextureN.Sample(SamplerN, input.Uv).rgb * input.Weights.x;
	  [flatten]
    if (Kd.a)
        BaseColor.rgb += TextureD.Sample(SamplerD, input.Uv).rgb * input.Weights.y;
      [flatten]
    if (Ks.a)
        BaseColor.rgb += TextureS.Sample(SamplerS, input.Uv).rgb * input.Weights.z;
      [flatten]
    if (Ke.a)
        BaseColor.rgb += TextureE.Sample(SamplerE, input.Uv).rgb * input.Weights.w;
	
	//BaseColor = float4(input.Weights.w, input.Weights.w, input.Weights.w, 1);
	//
	
    float3 SpecularMap = float3(1, 1, 1);
	
    BaseColor = float4(DirLighting(BaseColor.rgb, SpecularMap,
    normalize(input.Normal), input.wPosition.xyz),
    BaseColor.a);
    
    BaseColor = Lighting(DiffuseMapping(input.Uv), input.Uv, input.Normal, input.wPosition.xyz);
 
    BaseColor = AddShadow(BaseColor, input.wPosition);
    
    return BaseColor;
}