/**
* @file ファイル名.h
* @brief 簡単な説明
* @author 書いた人
* @date 2017/11/07
*/

#include "ParticleEffectManager.h"
#include <WICTextureLoader.h> 

#include "Framework\Graphics.h"
#include "BinaryFile.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

using Microsoft::WRL::ComPtr;

// インスタンスを定義
ParticleEffectManager* ParticleEffectManager::s_instance = nullptr;

// パーティクルの最大数
const int ParticleEffectManager::PARTICLE_NUM_MAX = 30000;
const int ParticleEffectManager::POINT_NUM = 200;

// 入力レイアウトの定義
const std::vector<D3D11_INPUT_ELEMENT_DESC>  ParticleEffectManager::INPUT_LAYOUT =
{
	{ "POSITION",	0,	 DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0,	 DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0,   DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Vector3) + sizeof(Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },


};

// シングルトンインスタンスの取得
ParticleEffectManager* ParticleEffectManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new ParticleEffectManager();
	}
	return s_instance;
}

ParticleEffectManager::ParticleEffectManager()
	:m_Camera(nullptr)
{
}

void ParticleEffectManager::Initialize(Camera* pCamera)
{
	// コンパイルされたシェーダファイルの読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");

	// デバイス、デバイスコンテキストの取得
	ID3D11Device* device = Graphics::Get().Device().Get();
	ID3D11DeviceContext * context = Graphics::Get().Context().Get();

	// 頂点シェーダを作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_VertexShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateVertexShader Failed", NULL, MB_OK);
	}

	// ジオメトリシェーダを作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_GeometryShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateGeometryShader Failed", NULL, MB_OK);
	}

	// ピクセルシェーダを作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_PixelShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreatePixelShader Failed", NULL, MB_OK);
	}

	m_Primitivebatch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context, 1, PARTICLE_NUM_MAX);

	// 入力レイアウトの作成
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		INPUT_LAYOUT.size(),
		VSData.GetData(), VSData.GetSize(),
		m_InputLayout.GetAddressOf());

	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(Constants);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(device->CreateBuffer(&cb, nullptr, m_ConstantBuffer.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateBuffer Failed", NULL, MB_OK);
		return;

	}

	// カメラをセット
	m_Camera = pCamera;


	// 汎用描画設定を初期化
	m_commonStates = make_unique<CommonStates>(device);



	// テクスチャサンプラーの設定
	D3D11_SAMPLER_DESC sam;
	ZeroMemory(&sam, sizeof(sam));		// 初期化(デフォルト値)
	sam.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sam.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sam.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sam.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	// 設定を基にテクスチャサンプラを作成
	if (FAILED(device->CreateSamplerState(&sam, m_Sampler.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateSamplerState Failed", NULL, MB_OK);
		return;
	}
}

void ParticleEffectManager::Update()
{
// 各データの更新
	vector<ParticleEffect*>::iterator itr = m_particles.begin();
	while (itr != m_particles.end()) {
		(*itr)->Update();

		// 終了したパーティクルデータを削除
		if ((*itr)->GetEndFlag())
		{
			itr = m_particles.erase(itr);
		}
		else itr++;
	}


}

void ParticleEffectManager::AddTexture(std::string typeName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texure)
{
	m_Textures[typeName] = texure;
}

void ParticleEffectManager::Draw()
{
	// 点がなければ描画しない
	if (m_particles.size() == 0) return;


	// デバイス、デバイスコンテキストの取得
	ID3D11Device* device = Graphics::Get().Device().Get();
	ID3D11DeviceContext * context = Graphics::Get().Context().Get();

	// 設定したバッファを実際にシェーダに適用
	context->VSSetConstantBuffers(0, 0, nullptr);
	context->GSSetConstantBuffers(0, 1, m_ConstantBuffer.GetAddressOf());
	context->PSSetConstantBuffers(0, 0, nullptr);

	// デバイスコンテキストにシェーダをセット
	context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_GeometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_PixelShader.Get(), nullptr, 0);

	Matrix world = Matrix::Identity;
	Matrix view = m_Camera->GetView();
	Matrix proj = m_Camera->GetProj();

	world = Matrix::CreateScale(1.0f);
	Matrix wvp = world * view * proj;

	// シェーダのコンスタントバッファに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(context->Map(m_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		Constants constants;
		constants.WVP = wvp;
		constants.Billboard = m_Camera->GetBillboard();

		// constants = = = >  pData.pData
		memcpy_s(pData.pData, pData.RowPitch, &constants, sizeof(Constants));
		// マップ終わり
		context->Unmap(m_ConstantBuffer.Get(), 0);
	}
	// デバイスコンテキストに入力レイアウトをセット
	context->IASetInputLayout(m_InputLayout.Get());
	// 陰面消去の設定
	context->RSSetState(m_commonStates->CullNone());


	ID3D11BlendState* blendStateSubtract;
	// 減算描画用のブレンドステートを作成
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	device->CreateBlendState(&desc, &blendStateSubtract);

	// アルファブレンドの設定
	//context->OMSetBlendState(m_commonStates->NonPremultiplied(), nullptr, 0xffffffff);
	// 加算描画
	context->OMSetBlendState(m_commonStates->Additive(), nullptr, 0xffffffff);
	// 減算描画
	//context->OMSetBlendState(blendStateSubtract, nullptr, 0xffffffff);

	// 深度テストの設定
	context->OMSetDepthStencilState(m_commonStates->DepthNone(), 0);
	// テクスチャサンプラーを設定
	context->PSSetSamplers(0, 1, m_Sampler.GetAddressOf());


	for (auto& particle : m_particles)
	{
		// テクスチャをシェーダに渡す
		auto texture = particle->GetType();
		context->PSSetShaderResources(0, 1, m_Textures[texture].GetAddressOf());

		m_Primitivebatch->Begin();
		m_Primitivebatch->Draw(D3D_PRIMITIVE_TOPOLOGY_POINTLIST, particle->GetVertexData(), 1);
		m_Primitivebatch->End();
	}
	
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

void ParticleEffectManager::Entry(ParticleEffect* particleData)  
{
	ParticleEffect* particle = new ParticleEffect(*particleData);

	// コンテナに格納
	m_particles.push_back(particle);
}
