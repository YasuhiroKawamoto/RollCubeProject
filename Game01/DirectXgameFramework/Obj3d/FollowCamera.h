/// <summary>
/// ���@�ɒǏ]����J�����̃N���X
/// </summary>
#pragma once		
#include "../Framework/Camera.h"
//#include "Player.h"



class FollowCamera : public Camera
{
private:
	enum MODE
	{
		FPS = 1,
		TPS
	};
	// �Ώۂ̍��W
	DirectX::SimpleMath::Vector3 m_targetPos;

	// �Ώۂ̉�]�p
	float m_targetAngle;

	// �J�������[�h
	int m_mode;

	// �v���C���[
	//Player* m_player;
public:
	static const float CAMERA_DISTANCE;

	// �R���X�g���N�^
	FollowCamera(int width, int height);

	// �X�V
	void Update() override;

	// �Ǐ]�Ώۂ̍��W���Z�b�g
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos);
	// �Ǐ]�Ώۂ̉�]�p���Z�b�g
	void SetTargetAngle(float targetangle);

	void SetMode(int mode)
	{
		m_mode = mode;
	}

	int GetMode()
	{
		return m_mode;
	}

	//void SetPlayer(Player* player)
	//{
	//	m_player = player;
	//}

};