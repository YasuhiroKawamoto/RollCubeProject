/// <summary>
/// �Ǐ]�J�����N���X�̒�`
/// </summary>
#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �ÓI�����o�ϐ��̏�����
const float FollowCamera::CAMERA_DISTANCE = 5.0f;
const float EYE_DELAY = 0.05f;
const float REF_DELAY = 0.2f;


FollowCamera::FollowCamera(int width, int height)
	:Camera(width, height, Vector3(0,1,0), Vector3::Zero)
{
	m_targetPos = Vector3::Zero;
	m_targetAngle = 0.0f;
	m_mode = 2;
	//m_player = nullptr;
}

void FollowCamera::Update()
{
	// �J�������_���W�A�Q�Ɠ_���W
	Vector3 eyepos, refpos;

	//FPS �J��������
	if (m_mode == FPS)
	{
		Vector3 eyePoint;
		// �n�_���W���v�Z
		eyePoint = m_targetPos + Vector3(0.0f, 1.3f, 0.0f);
		// ���@����J�������W�ւ̍���
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);
		// ���@�̌��ɉ�荞�ވׂ̉�]�s��
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		// �J�����ւ̃x�N�g������]
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		// �J�������W�𒲐� 
		eyepos = eyePoint + cameraV*0.1f;

		// ���_���W���v�Z
		refpos = eyePoint + cameraV;
	}

	
	//TPS �J��������
	if(m_mode == TPS)
	{
		// �Q�Ɠ_���W���v�Z
		refpos = m_targetPos + Vector3(0.0f, 2, 0.0f);
		// ���@����J�������W�ւ̍���
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);
		// ���@�̌��ɉ�荞�ވׂ̉�]�s��
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		// �J�����ւ̃x�N�g������]
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		// �J�������W���v�Z
		eyepos = refpos + cameraV;

	

		// ���_����
		eyepos = m_eyePos + (eyepos - m_eyePos)*EYE_DELAY;
		// �����_����
		refpos = m_targetPos + (refpos - m_targetPos)*REF_DELAY;
	}
		
	// �J�����X�V
	//if (m_player)
	//{
	//	SetTargetAngle(m_player->GetParts()[0].GetRotation().y);
	//	SetTargetPos(m_player->GetParts()[0].GetTranslation());
	//}



	SetEyePos(eyepos);
	SetRefPos(refpos);

	// ���N���X�̍X�V
	Camera::Update();
}

// �Ǐ]�Ώۂ̍��W���Z�b�g
void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetpos)
{
	m_targetPos = targetpos;
}

// �Ǐ]�Ώۂ̉�]�p���Z�b�g
void FollowCamera::SetTargetAngle(float targetangle)
{
	m_targetAngle = targetangle;
}
