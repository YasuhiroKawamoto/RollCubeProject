// シェーダのヘッダファイル

// ============================
// コンスタントバッファ
// ============================
cbuffer global
{
	// ワールドから射影までの変換行列
	row_major matrix g_WVP;			// (row_major --> 列優先)
	row_major matrix g_Billboard;	// ビルボード
};

// ============================
// テクスチャ, サンプラ
// ============================
Texture2D g_texture: register (t0);
SamplerState g_sampler: register(s0);


// ============================
// ジオメトリシェーダへの入力
// ============================

struct GSInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 otherData : TEXCOORD;
};

// ============================
// ピクセルシェーダへの入力
// ============================
struct PSInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};
