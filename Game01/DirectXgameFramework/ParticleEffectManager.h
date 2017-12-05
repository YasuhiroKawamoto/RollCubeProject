/**
* @file ParticleEffectManager.h
* @brief パーティクルエフェクトを管理するクラスのヘッダファイル
* @author 書いた人
* @date 2017/11/07
*/
#pragma once
#include <vector>
#include <map>

#include <Windows.h>
#include <wrl/client.h>

#include <d3d11_1.h>

#include <SimpleMath.h>
#include <CommonStates.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>


#include "Framework\Camera.h"
#include "Framework\Graphics.h"
#include "ParticleEffect.h"


// パーティクルエフェクトを管理するクラスのヘッダファイル
class ParticleEffectManager
{
public:
	static ParticleEffectManager* GetInstance();
public:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Vector4 = DirectX::SimpleMath::Vector4;


	static const int POINT_NUM;
	// パーティクルの最大数
	static const int PARTICLE_NUM_MAX;
	// 入力レイアウトの作成
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	// コンスタントバッファ
	struct Constants
	{
		DirectX::SimpleMath::Matrix WVP;		// ワールド,ビュー,プロジェクションの合成行列
		DirectX::SimpleMath::Matrix Billboard;	// ビルボード行列
	};

public:
	// 初期化
	void Initialize(Camera* pCamera);
	// 更新
	void Update();				
	// 読み込み
	void AddTexture(std::string typeName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texure);
	// 描画
	void Draw();				
	// 登録
	void Entry(ParticleEffect* particleData) ;

private:
	static ParticleEffectManager* s_instance;

private:
	ParticleEffectManager();// 非公開コンストラクタ

private:
	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_Primitivebatch;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
	//頂点データ配列
	std::vector<ParticleEffect*> m_particles;


	// 汎用描画設定
	std::unique_ptr<DirectX::CommonStates> m_commonStates;
	// コンスタントバッファオブジェクト
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_ConstantBuffer;
	// テクスチャのマップコンテナ
	std::map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_Textures;
	// テクスチャサンプラー
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler;
	// カメラ
	Camera* m_Camera;

};

