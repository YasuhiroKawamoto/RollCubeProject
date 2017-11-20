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
	// cmo�t�@�C����ǂݍ���
	auto& device = Graphics::Get().Device();

	// ���f�����ǂݍ��܂�Ă��Ȃ��ꍇ�̓��[�h���s��
	if (m_models[key] == nullptr)
		m_models[key] = Model::CreateFromCMO(device.Get(), key.c_str(), *m_factory);

	// ���f���̃|�C���^��Ԃ�
	return move(m_models[key]);
}

ModelManager::ModelManager()
{

	// cmo�t�@�C����ǂݍ���
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

