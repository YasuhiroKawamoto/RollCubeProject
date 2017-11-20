#include "Obj3d.h"
#include "../Framework/Graphics.h"
#include "../YasuLib/Manager/ModelManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


// �ÓI�����o�ϐ���`

// �ėp�X�e�[�g�ݒ�
std::unique_ptr<CommonStates>		Obj3d::m_states;
// �J����
Camera* Obj3d::m_camera;
// �ǂݍ��ݍς݃��f���z��
std::map<std::wstring, std::unique_ptr<DirectX::Model>> s_modelarray;


void Obj3d::InitializeStatic(Camera * camera)
{
	m_camera = camera;

	auto& graphics = Graphics::Get();
	m_states = std::make_unique<CommonStates>(graphics.Device().Get());
}

// �R���X�g���N�^
Obj3d::Obj3d()
{
	// �����o�ϐ���������

	m_scale = Vector3(1.0f, 1.0f, 1.0f);
	m_pParent = nullptr;
	// �f�t�H���g�ł̓I�C���[���g�p
	m_useQquaternion = false;
}

Obj3d::Obj3d(const Obj3d& obj)
{
}

void Obj3d::LoadModel(const wstring& fileName)
{
	// cmo�t�@�C����ǂݍ���
	auto modelManager =  ModelManager::GetInstance();

	m_model = modelManager->GetModel(fileName);
}

void Obj3d::Update()
{
	// ���[���h�s��̌v�Z
	// >>�g��
	Matrix scalemat = Matrix::CreateScale(m_scale);

	// >>��]
	Matrix rotmat;

	if (m_useQquaternion)
	{
		// �N�H�[�^�j�I���ŉ�]�v�Z
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{
		// �I�C���[�ŉ�]�v�Z
		Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
		rotmat = rotmatZ * rotmatX * rotmatY;
	}

	// >>�ړ�
	Matrix transmat = Matrix::CreateTranslation(m_translation);


	// ���[���h���W�ɐe�̃��[���h���W��������
	m_world = scalemat * rotmat * transmat;


	// �e�����݂���Ƃ��e�s����|����
	if (m_pParent)
	{
		m_world *= m_pParent->GetWorldMatrix();
	}
}

void Obj3d::Draw()
{
	// ���f���̕`��
	if(m_model)
		m_model->Draw(Graphics::Get().Context().Get(), *m_states, m_world, m_camera->GetView(), m_camera->GetProj());

}

// ======================================================================================
// @>�T�@�v:Obj3d�̃I�u�W�F�N�g��e����Ɨ�������
//
// @>���@��:Obj3d*
//
// @>�߂�l:�Ȃ�
// ======================================================================================
void Obj3d::IndependenceFromParent()
{
	// ���˂���p�[�c�̃��[���h�s����擾
	Matrix worldm = this->GetWorldMatrix();

	// ���o�������(���[���h�)
	Vector3 scale;
	Quaternion rotation;
	Vector3 translation;

	// ���[���h���W����e�v�f�𒊏o
	worldm.Decompose(scale, rotation, translation);

	// �e�p�[�c����Ɨ�������
	this->SetParent(nullptr);
	this->SetScale(scale);
	this->SetRotationQ(rotation);
	this->SetTranslation(translation);

}

///**
//*	@brief �I�u�W�F�N�g�̃��C�e�B���O�𖳌��ɂ���
//*/
void Obj3d::DisableLighting()
{
	if (m_model)
	{
		// ���f�����̑S���b�V������
		ModelMesh::Collection::const_iterator it_mesh = m_model->meshes.begin();
		for (; it_mesh != m_model->meshes.end(); it_mesh++)
		{
			ModelMesh* modelmesh = it_mesh->get();
			assert(modelmesh);

			// ���b�V�����̑S���b�V���p�[�c����
			std::vector<std::unique_ptr<ModelMeshPart>>::iterator it_meshpart = modelmesh->meshParts.begin();
			for (; it_meshpart != modelmesh->meshParts.end(); it_meshpart++)
			{
				ModelMeshPart* meshpart = it_meshpart->get();
				assert(meshpart);

				// ���b�V���p�[�c�ɃZ�b�g���ꂽ�G�t�F�N�g��BasicEffect�Ƃ��Ď擾
				std::shared_ptr<IEffect> ieff = meshpart->effect;
				BasicEffect* eff = dynamic_cast<BasicEffect*>(ieff.get());
				if (eff != nullptr)
				{
					// ���Ȕ������ő�l��
					eff->SetEmissiveColor(Vector3(1, 1, 1));

					// �G�t�F�N�g�Ɋ܂ޑS�Ă̕��s�������ɂ��ď�������
					for (int i = 0; i < BasicEffect::MaxDirectionalLights; i++)
					{
						// ���C�g�𖳌��ɂ���
						eff->SetLightEnabled(i, false);
					}
				}
			}
		}
	}
}
