//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @File  MyGame.h
//!
//! @Brief  MyGame�N���X(Game���p��)�̃w�b�_�t�@�C��
//!
//! @Date   2017/08/08
//!
//! @Author Y.Kawamoto
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once
#include <vector>

#include "Framework\Game.h"
#include "Obj3d\Obj3d.h"
#include "Player.h"
#include "Floor.h"
#include "Enemy.h"
#include "TimeManager.h"

class MyGame : public Game
{
private:
	// �J����
	std::unique_ptr<Camera> m_camera;

	
	std::unique_ptr<Player> m_player;	// �v���C���[

	std::vector<Enemy*> m_enemy;		// �G�l�~�[


	std::unique_ptr<Floor> m_floor;

	TimeManager* m_timeMan;
	
public:
	// �R���X�g���N�^ 
	MyGame(int width, int height);
	// �Q�[�����X�V���� 
	void Update(DX::StepTimer const& timer) override;
	// �V�[����`�悷�� 
	void Render(DX::StepTimer const & timer) override;
	// ������
	void Initialize() override;
	// �I������
	void Finalize() override;
};