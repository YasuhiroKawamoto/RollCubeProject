// ピクセルシェーダ

#include "Particle.hlsli"

float4 main(PSInput In) : SV_TARGET
{
	float4 color = g_texture.Sample(g_sampler, In.uv) * In.color;
	
	//In.color;

	//// 色調反転
	//float4 white = float4(1,1,1,1);
	//color = white - In.color;

	//color.w = In.color.w;

	//color = float4(1, 1, 1, 1);

	return color;
}