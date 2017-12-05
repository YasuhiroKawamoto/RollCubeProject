#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


Camera::Camera()
	:Camera(800, 600, Vector3(0,0,15), Vector3::Zero)
{
}

Camera::Camera(int width, int height, const Vector3& eye, const Vector3& target)
{
	//�����o�ϐ��̏�����

	// ���_
	m_eyePos = eye;
	// �����_
	m_targetPos = target;
	// ������x�N�g��
	m_upVec = Vector3(0.0f, 1.0f, 0.0f);

	// ������������p
	m_fovY = XMConvertToRadians(60.0f);

	// �A�X�y�N�g��(���~�c�̉�ʔ䗦)
	m_aspect = (float)width / height;

	// �j�A�N���b�v
	m_nearClip = 0.1f;

	// �t�@�[�N���b�v
	m_farClip = 1000.0f;

	// �r���[�s�񐶐�
	m_view = Matrix::CreateLookAt(m_eyePos, m_targetPos, m_upVec);
	// �v���W�F�N�V�����s�񐶐�
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

void Camera::Update()
{
	// �r���[�s�񐶐�
	m_view = Matrix::CreateLookAt(m_eyePos, m_targetPos, m_upVec);

	// �v���W�F�N�V�����s�񐶐� 
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);

	// �r���{�[�h�s����v�Z
	CalcBillboard();
}

const DirectX::SimpleMath::Matrix& Camera::GetView()
{
	return m_view;
}

const DirectX::SimpleMath::Matrix& Camera::GetProj()
{
	return m_proj;
}

// �r���{�[�h�̌v�Z
void Camera::CalcBillboard()
{
	// ��������
	Vector3 eyeDir = m_eyePos - m_targetPos;
	// Y��
	Vector3 Y = Vector3::UnitY;
	// X��
	Vector3 X = Y.Cross(eyeDir);
	X.Normalize();
	// Z��
	Vector3 Z = X.Cross(Y);
	Z.Normalize();
	// Y������r���{�[�h�s��i�E��n�̈�Z�������]�j
	m_BillboardConstrainY = Matrix::Identity;
	m_BillboardConstrainY.m[0][0] = X.x;
	m_BillboardConstrainY.m[0][1] = X.y;
	m_BillboardConstrainY.m[0][2] = X.z;
	m_BillboardConstrainY.m[1][0] = Y.x;
	m_BillboardConstrainY.m[1][1] = Y.y;
	m_BillboardConstrainY.m[1][2] = Y.z;
	m_BillboardConstrainY.m[2][0] = -Z.x;
	m_BillboardConstrainY.m[2][1] = -Z.y;
	m_BillboardConstrainY.m[2][2] = -Z.z;

	Y = eyeDir.Cross(X);
	Y.Normalize();
	eyeDir.Normalize();
	// �r���{�[�h�s��i�E��n�̈�Z�������]�j
	m_Billboard = Matrix::Identity;
	m_Billboard.m[0][0] = X.x;
	m_Billboard.m[0][1] = X.y;
	m_Billboard.m[0][2] = X.z;
	m_Billboard.m[1][0] = Y.x;
	m_Billboard.m[1][1] = Y.y;
	m_Billboard.m[1][2] = Y.z;
	m_Billboard.m[2][0] = -eyeDir.x;
	m_Billboard.m[2][1] = -eyeDir.y;
	m_Billboard.m[2][2] = -eyeDir.z;
}