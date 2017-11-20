#include "CollisionNode.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


bool CollisionNode::m_debugVisible = false;

//=======================================================
// *******CollisionNode�N���X�̃����o�֐�******************
//=======================================================
void CollisionNode::SetParent(Obj3d* parent)
{
	m_obj.SetParent(parent);
}

//=======================================================
// **********SphereNode�N���X�̃����o�֐�*****************
//=======================================================

// �R���X�g���N�^
SphereNode::SphereNode()
	:m_radius(1.0f)
{
}

void SphereNode::Initialize()
{
	// �f�o�b�O�\���p���f���̂̓ǂݍ���
	m_obj.LoadModel(L"Resources\\SphereNode.cmo");
}

void SphereNode::Update()
{
	m_obj.SetTranslation(m_trans);
	m_obj.SetScale(Vector3(m_radius));
	m_obj.Update();

	{// ���苅�̗v�f���v�Z
		const Matrix& worldm = m_obj.GetWorldMatrix();

		// ���f���ł̒��S�_���W
		Vector3 center(0, 0, 0);
		// ���f���ł̉E�[���W
		Vector3 right(1, 0, 0);


		// ���[���h���W�n�ɕϊ�
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		// ���苉�̗v�f����
		Sphere::Center = center;
		Sphere::radius = Vector3::Distance(center, right);

	
	
	}
}

void SphereNode::Drwa()
{
	m_obj.Draw();
}


