#include "../../pch.h"
#include "ModelManager.h"
#include "../../Obj3d/Obj3d.h"


#include "../../Framework/Graphics.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;
using namespace std;

ModelManager* ModelManager::m_instance = nullptr;

std::unique_ptr<DirectX::Model> ModelManager::GetModel(const wstring& key)
{
	// cmoファイルを読み込み
	auto& device = Graphics::Get().Device();

	// モデルが読み込まれていない場合はロードを行う
	if (m_models[key] == nullptr)
		m_models[key] = Model::CreateFromCMO(device.Get(), key.c_str(), *m_factory);

	// モデルのポインタを返す
	return move(m_models[key]);
}

ModelManager::ModelManager()
{

	// cmoファイルを読み込み
	auto& device = Graphics::Get().Device();

	m_factory = std::make_unique<EffectFactory>(device.Get());
	m_factory->SetDirectory(L"Resources");

}

ModelManager* ModelManager::GetInstance()
{
		if (m_instance == nullptr)
		m_instance = new ModelManager();

	return m_instance;
}

