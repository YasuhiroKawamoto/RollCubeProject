// ジオメトリシェーダ
#include "Particle.hlsli"

// 四角形の頂点数
static const uint Vnum = 4;

// 中心点からのオフセット
static const float4 offsetArray[Vnum] =
{
	float4(-0.5f, -0.5f, 0, 0),		// 左下
	float4(+0.5f, -0.5f, 0, 0),		// 右下
	float4(-0.5f, +0.5f, 0, 0),		// 左上
	float4(+0.5f, +0.5f, 0, 0),		// 右上

};

// テクスチャuv
static const float2 uvArray[Vnum] =
{
	float2(0.0f, 1.0f),		// 左下
	float2(1.0f, 1.0f),		// 右下
	float2(0.0f, 0.0f),		// 左上
	float2(1.0f, 0.0f),		// 右上
};

[maxvertexcount(Vnum)]
void main(
	point GSInput input[1],
	inout TriangleStream< PSInput > output)
{
	// Geometry Sample Question 01
	{

		//// 問1
		//for (uint j = 0; j < 50; j++)
		//{
		//	PSInput element;
		//	element.pos = input[0].pos + float4(j*0.001f, j*(-0.001f), 0, 0);
		//	element.pos = mul(element.pos, g_WVP);
		//	element.color = input[0].color;
		//	element.uv = input[0].uv;
		//	output.Append(element);

		//	// ストリップをリスタート
		//	output.RestartStrip();
		//}
		//for (uint i = 0; i < 50; i++)
		//{
		//	PSInput element;
		//	element.pos = input[0].pos + float4(i*0.001f, i*(0.001f)-0.05f, 0, 0);
		//	element.pos = mul(element.pos, g_WVP);
		//	element.color = input[0].color;
		//	element.uv = input[0].uv;
		//	output.Append(element);

		//	// ストリップをリスタート
		//	output.RestartStrip();
		//}

		//// 問2
		//for (uint i = 0; i < 100; i++)
		//{
		//	PSInput element;
		//	element.pos = input[0].pos + float4(cos(i)*0.025f, sin(i)*0.025f, 0, 0);
		//	element.pos = mul(element.pos, g_WVP);
		//	element.color = input[0].color;
		//	element.uv = input[0].uv;
		//	output.Append(element);

		//	// ストリップをリスタート
		//	output.RestartStrip();
		//}
		// 問2
		//for (uint i = 0; i < 100; i++)
		//{
		//	PSInput element;
		//	element.pos = input[0].pos + float4((sin(i*2))*0.04f, cos(i)*0.08f, 0, 0);
		//	element.pos = mul(element.pos, g_WVP);
		//	element.color = input[0].color;
		//	element.uv = input[0].uv;
		//	output.Append(element);

		//	// ストリップをリスタート
		//	output.RestartStrip();
		//}
	}

	PSInput element;
	float4 offset;

	float scale = input[0].otherData.x;
	float rotation = input[0].otherData.y;
	// 頂点データの設定
	for (uint i = 0; i < Vnum; i++)
	{
		// 指定度回転
		offset.x = offsetArray[i].x *  cos(rotation) + offsetArray[i].y * sin(rotation);
		offset.y = offsetArray[i].x * -sin(rotation) + offsetArray[i].y * cos(rotation);
		offset.z = 0;
		offset.w = 0;

		// スケーリング
		offset = offset * scale;

		// ビルボード回転
		offset = mul(offset, g_Billboard);

		element.pos = input[0].pos + offset;

		// ワールド座標→2D座標変換(並行移動)
		element.pos = mul(element.pos, g_WVP);
		element.color = input[0].color;
		element.uv = uvArray[i];
		output.Append(element);
	}
	// ストリップをリスタート
	output.RestartStrip();

}