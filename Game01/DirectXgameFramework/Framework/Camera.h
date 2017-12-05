/// <summary>
/// �J�����𐧌䂷��N���X
/// </summary>
#pragma once		

#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
protected:
	// ==�r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// ���_
	DirectX::SimpleMath::Vector3 m_eyePos;
	// �����_
	DirectX::SimpleMath::Vector3 m_targetPos;
	// ������x�N�g��
	DirectX::SimpleMath::Vector3 m_upVec;

	
	// ==�v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_proj;
	// ������������p
	float m_fovY;
	// �A�X�y�N�g��
	float m_aspect;
	// �j�A�N���b�v
	float m_nearClip;
	// �t�@�[�N���b�v
	float m_farClip;

	// �r���{�[�h�s��
	DirectX::SimpleMath::Matrix m_Billboard;
	// �r���{�[�h�s��(Y���������j
	DirectX::SimpleMath::Matrix m_BillboardConstrainY;

public:
	Camera();
	Camera(int width, int height, const DirectX::SimpleMath::Vector3& eye, const DirectX::SimpleMath::Vector3& target);

	virtual ~Camera() {}

	// �X�V
	virtual void Update();

	// �r���[�s��擾
	const DirectX::SimpleMath::Matrix& GetView();

	// �v���W�F�N�V�����s��擾
	const DirectX::SimpleMath::Matrix& GetProj();

	// ���_���W�ݒ�
	void SetEyePos(const DirectX::SimpleMath::Vector3& eyePos){ m_eyePos = eyePos; }

	// �����_���W�ݒ�
	void SetRefPos(const DirectX::SimpleMath::Vector3& targetPos){m_targetPos = targetPos;}

	// ��x�N�g�����W�ݒ�
	void SetUpVec(const DirectX::SimpleMath::Vector3& upVec)
	{
		m_upVec = upVec;
		m_upVec.Normalize();
	}


	void SetFovY(float fovY){ m_fovY = fovY;	}
	void SetAspect(float aspect){m_aspect = aspect;}
	void SetNearClip(float nearclip){m_nearClip = nearclip;}
	void SetFarClip(float farclip){m_farClip = farclip;}

	const DirectX::SimpleMath::Matrix& GetBillboard() const { return m_Billboard; }
	const DirectX::SimpleMath::Matrix& GetBillboardConstrainY() const { return m_BillboardConstrainY; }

	// �r���{�[�h���v�Z
	void CalcBillboard();
};