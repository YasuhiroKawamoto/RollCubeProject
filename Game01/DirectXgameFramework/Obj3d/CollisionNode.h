/// <summary>
/// �����蔻��m�[�h
/// @>�����蔻��̌v�Z�y�щ���
/// </summary>

#pragma once
#include "Obj3d.h"
#include "Collision.h"

/// <summary>
/// �����蔻��m�[�h�N���X
/// </summary>
class CollisionNode
{
protected:
	static bool m_debugVisible;
public:
	static  bool GetDebugVisible()
	{
		return m_debugVisible;
	}
	static void SetDebugVisible(bool visibleFlag)
	{
		m_debugVisible = visibleFlag;
	}
protected:
	// �f�o�b�O�\���p�I�u�W�F�N�g
	Obj3d m_obj;
	DirectX::SimpleMath::Vector3 m_trans;
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Drwa() = 0;
	void SetParent(Obj3d* parent);
	void SetTrans(const DirectX::SimpleMath::Vector3& trans)
	{
		m_trans = trans;
	}
};

/// <summary>
/// �������蔻��m�[�h�N���X
/// </summary>
class SphereNode : public CollisionNode, public Sphere
{
protected:
	float m_radius;
public:
	SphereNode();
	void Initialize() override;
	void Update() override;
	void Drwa() override;
	void SetRadius(float radius)
	{
		m_radius = radius;
	}
};