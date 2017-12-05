// 頂点シェーダ

#include "Particle.hlsli"

GSInput main( float4 pos : POSITION, float4 color : COLOR, float2 otherData : TEXCOORD )
{
	GSInput Out;

	Out.pos = pos;
	Out.color = color;
	Out.otherData = otherData;

	return Out;
}