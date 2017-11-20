/**
* @file Player.cpp
* @brief �ȒP�Ȑ���
* @author �������l
* @date ���t�i�J�n���H�j
*/



#include "pch.h"
#include "Player.h"
#include "YasuLib\Utility\Utility.h"
#include "YasuLib\Manager\InputManager.h"
#include "DebugManager.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace utl;

const Vector3 DOWN_DIRECTION = Vector3(0.00f, -1.0f, 0.0f);


Player::Player()
	:m_isMoving(false)
{

}


void Player::Init()
{
	// ���C������
	m_parts["main"] = make_unique<Obj3d>();
	m_parts["main"]->LoadModel(L"Resources/Box.cmo");
	m_parts["main"]->SetTranslation(Vector3(0.0f, 0.5f, 0.0f));

	// �p�l��(�㕔)
	m_panels["top"] = make_unique<Panel>();
	m_panels["top"]->Load(L"Resources/Panel1.cmo");
	m_panels["top"]->Initialze(m_parts["main"].get());
	

	// ���C�������̒��S�_
	m_parts["pivot"] = make_unique<Obj3d>();
	m_parts["pivot"]->SetParent(m_parts["main"].get());

	// ���������̐ݒ�
	NormalVec = Vector3(0, 1, 0);

	m_state = Panel::State::DEFAULT;

}

void Player::Update()
{
	float time = 0;
	if(m_isMoving)
		time += 1 / 60.0f * 1.5f;

	// �e���f�����X�V
	for (auto& part : m_parts)
	{
		part.second->Update();
	}

	// ��Ԃ��X�V
	m_state = m_panels["top"]->GetState();

	// �e�p�l�����X�V
	for (auto& part : m_panels)
	{
		part.second->Update();
	}




	int a = 0;
	if (!m_isMoving)
	{
		if (InputManager::GetInstance()->GetKeybordTracker()->IsKeyPressed(Keyboard::Keys::Up))
			movingState = MOVE_DIRECTION::FRONT;
		if (InputManager::GetInstance()->GetKeybordTracker()->IsKeyPressed(Keyboard::Keys::Down))
			movingState = MOVE_DIRECTION::BACK;
		if (InputManager::GetInstance()->GetKeybordTracker()->IsKeyPressed(Keyboard::Keys::Left))
			movingState = MOVE_DIRECTION::LEFT;
		if (InputManager::GetInstance()->GetKeybordTracker()->IsKeyPressed(Keyboard::Keys::Right))
			movingState = MOVE_DIRECTION::RIGHT;

		if (InputManager::GetInstance()->GetKeybordTracker()->IsKeyPressed(Keyboard::Keys::Space))
		{
			m_parts["main"]->SetTranslation(Vector3(0.0f, 0.5f, 0.0f));
			m_parts["main"]->SetRotationQ(Quaternion::Identity);
			m_parts["pivot"]->SetTranslation(Vector3(0.0f, 0.5f, 0.0f));
		}
	}

	switch (movingState)
	{
	case Player::FRONT:
		RotateFront(&time);
		break;
	case Player::BACK:
		RotateBack(&time);
		break;
	case Player::LEFT:
		RotateLeft(&time);
		break;
	case Player::RIGHT:
		RotateRight(&time);
		break;
	default:
		break;
	}
}

void Player::SetMap(int map[10][10])
{
	for (int i = 0; i<10; i++)
	{
		for (int j = 0; j<10; j++)
		{
			m_map[i][j] = map[i][j];
		}
	}
}

/**
* @fn
*	�v���C���[�̉�]���s���֐�
* @brief �v�����
* @param time �Q�[��������(�~���b)
* @return �Ȃ�
*/
void Player::RotateFront(float* time)
{
	if (!m_isMoving)
	{
		m_isMoving = CheckOnMap(Vector2(0, -1));
		m_startAng = m_parts["main"]->GetRotationQ();
		Quaternion q = Quaternion::CreateFromRotationMatrix(Matrix::CreateRotationX(-XMConvertToRadians(90)));
		m_endAng = m_parts["main"]->GetRotationQ() * q;
	}
	// �p�x�ƍ��W���Ԉړ�
	*time = Utility::Clamp(*time, 0.0f, 1.0f);
	m_parts["main"]->SetRotationQ(Quaternion::Lerp(m_startAng, m_endAng, *time));
	float theta = Utility::Lerp(XMConvertToRadians(45.0f), XMConvertToRadians(135.0f), *time);
	m_parts["main"]->SetTranslation(m_parts["pivot"]->GetTranslation() + Vector3(0, sinf(theta)* 1.41421356f *0.5f, cosf(theta)* 1.41421356f *0.5f - 0.5f));

	if (*time >= 1.0f && m_isMoving)
	{
		*time = 0.0f;

		// ��]�␳
		m_parts["pivot"]->SetTranslation(m_parts["pivot"]->GetTranslation() + Vector3(0, 0, -1));
		Vector3 modPos;
		modPos.x = Utility::Roundf(m_parts["main"]->GetTranslation().x, 1);
		modPos.y = Utility::Roundf(m_parts["main"]->GetTranslation().y, 2);
		modPos.z = Utility::Roundf(m_parts["main"]->GetTranslation().z, 1);
		m_parts["main"]->SetTranslation(modPos);

		NormalVec = Vector3::TransformNormal(NormalVec, m_parts["main"]->GetWorldMatrix());
		NormalVec.x = Utility::Roundf(NormalVec.x, 1);
		NormalVec.y = Utility::Roundf(NormalVec.y, 1);
		NormalVec.z = Utility::Roundf(NormalVec.z, 1);

		m_panels["top"]->CalcDirection(Matrix::CreateRotationX(-XMConvertToRadians(90)));

		movingState = NONE;
		m_isMoving = false;
	}
}

void Player::RotateBack(float* time)
{
	if (!m_isMoving)
	{
		m_isMoving = CheckOnMap(Vector2(0, 1));
		m_startAng = m_parts["main"]->GetRotationQ();
		Quaternion q = Quaternion::CreateFromRotationMatrix(Matrix::CreateRotationX(XMConvertToRadians(90)));
		m_endAng = m_parts["main"]->GetRotationQ() * q;
	}

	// �p�x�ƍ��W���Ԉړ�
	*time = Utility::Clamp(*time, 0.0f, 1.0f);
	m_parts["main"]->SetRotationQ(Quaternion::Lerp(m_startAng, m_endAng, *time));
	float theta = Utility::Lerp(XMConvertToRadians(135.0f), XMConvertToRadians(45.0f), *time);
	m_parts["main"]->SetTranslation(m_parts["pivot"]->GetTranslation() + Vector3(0, sinf(theta)* 1.41421356f *0.5f, cosf(theta)* 1.41421356f *0.5f + 0.5f));

	if (*time >= 1.0f && m_isMoving)
	{
		*time = 0.0f;

		// ��]�␳
		m_parts["pivot"]->SetTranslation(m_parts["pivot"]->GetTranslation() + Vector3(0, 0, 1));
		Vector3 modPos;
		modPos.x = Utility::Roundf(m_parts["main"]->GetTranslation().x, 1);
		modPos.y = Utility::Roundf(m_parts["main"]->GetTranslation().y, 2);
		modPos.z = Utility::Roundf(m_parts["main"]->GetTranslation().z, 1);
		m_parts["main"]->SetTranslation(modPos);

		NormalVec = Vector3::TransformNormal(NormalVec, m_parts["main"]->GetWorldMatrix());
		NormalVec.x = Utility::Roundf(NormalVec.x, 1);
		NormalVec.y = Utility::Roundf(NormalVec.y, 1);
		NormalVec.z = Utility::Roundf(NormalVec.z, 1);

		m_panels["top"]->CalcDirection(Matrix::CreateRotationX(XMConvertToRadians(90)));

		movingState = NONE;
		m_isMoving = false;
	}

}

void Player::RotateLeft(float* time)
{
	if (!m_isMoving)
	{
		m_isMoving = CheckOnMap(Vector2(-1, 0));
		m_startAng = m_parts["main"]->GetRotationQ();
		Quaternion q = Quaternion::CreateFromRotationMatrix(Matrix::CreateRotationZ(XMConvertToRadians(90)));
		m_endAng = m_parts["main"]->GetRotationQ() * q;
	}
	// �p�x�ƍ��W���Ԉړ�
	*time = Utility::Clamp(*time, 0.0f, 1.0f);
	m_parts["main"]->SetRotationQ(Quaternion::Slerp(m_startAng, m_endAng, *time));
	float theta = Utility::Lerp(XMConvertToRadians(45.0f), XMConvertToRadians(135.0f), *time);
	m_parts["main"]->SetTranslation(m_parts["pivot"]->GetTranslation() + Vector3(cosf(theta)* 1.41421356f *0.5f - 0.5f, sinf(theta)* 1.41421356f *0.5f, 0));

	if (*time >= 1.0f && m_isMoving)
	{
		*time = 0.0f;

		// ��]�␳
		m_parts["pivot"]->SetTranslation(m_parts["pivot"]->GetTranslation() + Vector3(-1, 0, 0));
		Vector3 modPos;
		modPos.x = Utility::Roundf(m_parts["main"]->GetTranslation().x, 1);
		modPos.y = Utility::Roundf(m_parts["main"]->GetTranslation().y, 2);
		modPos.z = Utility::Roundf(m_parts["main"]->GetTranslation().z, 1);
		m_parts["main"]->SetTranslation(modPos);

		NormalVec = Vector3::TransformNormal(NormalVec, m_parts["main"]->GetWorldMatrix());
		NormalVec.x = Utility::Roundf(NormalVec.x, 1);
		NormalVec.y = Utility::Roundf(NormalVec.y, 1);
		NormalVec.z = Utility::Roundf(NormalVec.z, 1);		
		
		m_panels["top"]->CalcDirection(Matrix::CreateRotationZ(XMConvertToRadians(90)));

	//if (dir == DOWN_DIRECTION)
	//{
	//	// �U��(��)
	//	return;
	//}
		movingState = NONE;
		m_isMoving = false;
	}

}

void Player::RotateRight(float* time)
{
	static float axis = 0.5f;

	if (!m_isMoving)
	{
		m_isMoving = CheckOnMap(Vector2(1, 0));
		m_startAng = m_parts["main"]->GetRotationQ();
		Quaternion q = Quaternion::CreateFromRotationMatrix(Matrix::CreateRotationZ(-XMConvertToRadians(90)));
		m_endAng = m_parts["main"]->GetRotationQ() * q;
	}

	// �p�x�ƍ��W���Ԉړ�
	*time = Utility::Clamp(*time, 0.0f, 1.0f);
	m_parts["main"]->SetRotationQ(Quaternion::Lerp(m_startAng, m_endAng, *time));
	float theta = Utility::Lerp(XMConvertToRadians(135), XMConvertToRadians(45), *time);
	m_parts["main"]->SetTranslation(m_parts["pivot"]->GetTranslation() + Vector3(cosf(theta)* sqrt(2) *0.5f + 0.5f, sinf(theta)* sqrt(2) *0.5f, 0));

	if (*time >= 1.0f && m_isMoving)
	{
		*time = 0.0f;
		
		// ��]�␳
		m_parts["pivot"]->SetTranslation(m_parts["pivot"]->GetTranslation() + Vector3(1, 0, 0));
		Vector3 modPos;
		modPos.x = Utility::Roundf(m_parts["main"]->GetTranslation().x, 1);
		modPos.y = Utility::Roundf(m_parts["main"]->GetTranslation().y, 2);
		modPos.z = Utility::Roundf(m_parts["main"]->GetTranslation().z, 1);
		m_parts["main"]->SetTranslation(modPos);

		NormalVec = Vector3::TransformNormal(NormalVec, m_parts["main"]->GetWorldMatrix());
		NormalVec.x = Utility::Roundf(NormalVec.x, 1);
		NormalVec.y = Utility::Roundf(NormalVec.y, 1);
		NormalVec.z = Utility::Roundf(NormalVec.z, 1);

		m_panels["top"]->CalcDirection(Matrix::CreateRotationZ(-XMConvertToRadians(90)));


		// �ړ���Ԃ̃��Z�b�g
		movingState = NONE;
		m_isMoving = false;
	}

}


//void Player::Rotate(MOVE_DIRECTION dir, float* time)
//{
//	if (!m_isMoving)
//	{
//		m_isMoving = CheckOnMap(/**/);
//		m_startAng = m_parts["main"]->GetRotationQ();
//		Quaternion q = Quaternion::CreateFromRotationMatrix(/*Matrix::CreateRotationZ(-XMConvertToRadians(90))*/);
//		m_endAng = m_parts["main"]->GetRotationQ() * q;
//	}
//
//	// �p�x�ƍ��W���Ԉړ�
//	*time = Utility::Clamp(*time, 0.0f, 1.0f);
//	m_parts["main"]->SetRotationQ(Quaternion::Lerp(m_startAng, m_endAng, *time));
//	float theta = Utility::Lerp(/*XMConvertToRadians(135), XMConvertToRadians(45)*/, *time);
//	m_parts["main"]->SetTranslation(m_parts["pivot"]->GetTranslation() + Vector3(/*cosf(theta)* sqrt(2) *0.5f + 0.5f, sinf(theta)* sqrt(2) *0.5f, 0)*/);
//
//	if (*time >= 1.0f && m_isMoving)
//	{
//		*time = 0.0f;
//
//		// ��]�␳
//		m_parts["pivot"]->SetTranslation(m_parts["pivot"]->GetTranslation() + Vector3(/*1, 0, 0*/));
//		Vector3 modPos;
//		modPos.x = Utility::Roundf(m_parts["main"]->GetTranslation().x, 1);
//		modPos.y = Utility::Roundf(m_parts["main"]->GetTranslation().y, 2);
//		modPos.z = Utility::Roundf(m_parts["main"]->GetTranslation().z, 1);
//		m_parts["main"]->SetTranslation(modPos);
//
//		NormalVec = Vector3::TransformNormal(NormalVec, m_parts["main"]->GetWorldMatrix());
//		NormalVec.x = Utility::Roundf(NormalVec.x, 1);
//		NormalVec.y = Utility::Roundf(NormalVec.y, 1);
//		NormalVec.z = Utility::Roundf(NormalVec.z, 1);
//
//		m_panels["top"]->CalcDirection(Matrix::CreateRotationZ(/*-XMConvertToRadians(90)*/));
//
//
//		// �ړ���Ԃ̃��Z�b�g
//		movingState = NONE;
//		m_isMoving = false;
//	}
//}

void Player::Draw()
{
	for (auto& part : m_parts)
	{
		// �e���f����`��
		 part.second->Draw();
	}

	for (auto& part : m_panels)
	{
		// �e�p�l�����X�V
		part.second->Draw();
	}
}

Player::~Player()
{
}


bool Player::CheckOnMap(const Vector2& dir)
{

	int checkGridY = (int)(dir.y + m_parts["main"]->GetTranslation().z  +5);
	int checkGridX = (int)(dir.x + m_parts["main"]->GetTranslation().x  +5);

	if (checkGridY < 0 || checkGridY>9 || checkGridX < 0 || checkGridX > 9)
		return false;

	if (m_map[checkGridY][checkGridX] == 0)
		return false;
	
	return true;

}





