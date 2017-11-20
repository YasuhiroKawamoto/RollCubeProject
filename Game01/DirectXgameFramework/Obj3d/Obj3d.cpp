#include "Obj3d.h"
#include "../Framework/Graphics.h"
#include "../YasuLib/Manager/ModelManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


// 静的メンバ変数定義

// 汎用ステート設定
std::unique_ptr<CommonStates>		Obj3d::m_states;
// カメラ
Camera* Obj3d::m_camera;
// 読み込み済みモデル配列
std::map<std::wstring, std::unique_ptr<DirectX::Model>> s_modelarray;


void Obj3d::InitializeStatic(Camera * camera)
{
	m_camera = camera;

	auto& graphics = Graphics::Get();
	m_states = std::make_unique<CommonStates>(graphics.Device().Get());
}

// コンストラクタ
Obj3d::Obj3d()
{
	// メンバ変数を初期化

	m_scale = Vector3(1.0f, 1.0f, 1.0f);
	m_pParent = nullptr;
	// デフォルトではオイラーを使用
	m_useQquaternion = false;
}

Obj3d::Obj3d(const Obj3d& obj)
{
}

void Obj3d::LoadModel(const wstring& fileName)
{
	// cmoファイルを読み込み
	auto modelManager =  ModelManager::GetInstance();

	m_model = modelManager->GetModel(fileName);
}

void Obj3d::Update()
{
	// ワールド行列の計算
	// >>拡大
	Matrix scalemat = Matrix::CreateScale(m_scale);

	// >>回転
	Matrix rotmat;

	if (m_useQquaternion)
	{
		// クォータニオンで回転計算
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{
		// オイラーで回転計算
		Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
		rotmat = rotmatZ * rotmatX * rotmatY;
	}

	// >>移動
	Matrix transmat = Matrix::CreateTranslation(m_translation);


	// ワールド座標に親のワールド座標をかける
	m_world = scalemat * rotmat * transmat;


	// 親が存在するとき親行列を掛ける
	if (m_pParent)
	{
		m_world *= m_pParent->GetWorldMatrix();
	}
}

void Obj3d::Draw()
{
	// モデルの描画
	if(m_model)
		m_model->Draw(Graphics::Get().Context().Get(), *m_states, m_world, m_camera->GetView(), m_camera->GetProj());

}

// ======================================================================================
// @>概　要:Obj3dのオブジェクトを親から独立させる
//
// @>引　数:Obj3d*
//
// @>戻り値:なし
// ======================================================================================
void Obj3d::IndependenceFromParent()
{
	// 発射するパーツのワールド行列を取得
	Matrix worldm = this->GetWorldMatrix();

	// 抽出した情報(ワールド基準)
	Vector3 scale;
	Quaternion rotation;
	Vector3 translation;

	// ワールド座標から各要素を抽出
	worldm.Decompose(scale, rotation, translation);

	// 親パーツから独立させる
	this->SetParent(nullptr);
	this->SetScale(scale);
	this->SetRotationQ(rotation);
	this->SetTranslation(translation);

}

///**
//*	@brief オブジェクトのライティングを無効にする
//*/
void Obj3d::DisableLighting()
{
	if (m_model)
	{
		// モデル内の全メッシュ分回す
		ModelMesh::Collection::const_iterator it_mesh = m_model->meshes.begin();
		for (; it_mesh != m_model->meshes.end(); it_mesh++)
		{
			ModelMesh* modelmesh = it_mesh->get();
			assert(modelmesh);

			// メッシュ内の全メッシュパーツ分回す
			std::vector<std::unique_ptr<ModelMeshPart>>::iterator it_meshpart = modelmesh->meshParts.begin();
			for (; it_meshpart != modelmesh->meshParts.end(); it_meshpart++)
			{
				ModelMeshPart* meshpart = it_meshpart->get();
				assert(meshpart);

				// メッシュパーツにセットされたエフェクトをBasicEffectとして取得
				std::shared_ptr<IEffect> ieff = meshpart->effect;
				BasicEffect* eff = dynamic_cast<BasicEffect*>(ieff.get());
				if (eff != nullptr)
				{
					// 自己発光を最大値に
					eff->SetEmissiveColor(Vector3(1, 1, 1));

					// エフェクトに含む全ての平行光源分について処理する
					for (int i = 0; i < BasicEffect::MaxDirectionalLights; i++)
					{
						// ライトを無効にする
						eff->SetLightEnabled(i, false);
					}
				}
			}
		}
	}
}
