//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @File  MyGame.cpp
//!
//! @Brief  MyGame�N���X�̃\�[�X�t�@�C��
//!
//! @Date   2017/07/13
//!
//! @Author Y.Kawamot
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


#include "MyGame.h"
#include "YasuLib\Manager\InputManager.h"
#include "YasuLib\Manager\TextureManager.h"
#include "DebugManager.h"
#include "BattleManager.h"
#include "TimeManager.h"
#include <sstream>

using namespace DX;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;


// �R���X�g���N�^
MyGame::MyGame(int width, int height)
	// ���R���X�g���N�^�Ăяo��
	:Game(width, height)
{
}

void MyGame::Initialize()
{
	//�@���N���X�̏�����
	Game::Initialize();


	// �������������������ɒǉ�
	auto& graphics = Graphics::Get();

	// �J�����쐬��������
	m_camera = make_unique<Camera>(this->width, this->height, Vector3(0, 6, 8), Vector3(0, 0, 0));

	Obj3d::InitializeStatic(m_camera.get());

	// �v���C���[������
	m_player = make_unique<Player>();

	// �G�l�~�[������
	for (int i = 0; i < 1; i++)
	{
		Enemy* enm = new Enemy();
		enm->Load(L"Resources/Enemy01.cmo");
		enm->Init(Vector3(2+i-3, 0, 0));
		m_enemy.push_back(enm);
	}

	m_player->Init();

	m_floor = make_unique<Floor>();

	int map[10][10]
	{
		{ 0,1,1,1,1,1,0,0,1,1 },
		{ 0,0,0,1,1,0,1,0,0,1 },
		{ 0,0,0,1,1,1,1,0,0,0 },
		{ 1,0,0,1,1,1,1,1,0,1 },
		{ 1,0,0,1,1,1,0,0,0,0 },
		{ 1,1,1,1,1,1,1,0,1,1 },
		{ 1,1,1,1,0,1,1,1,1,0 },
		{ 1,0,0,0,0,0,1,1,0,1 },
		{ 1,1,0,0,0,1,1,0,0,1 },
		{ 1,1,0,1,1,1,0,0,0,0 },
	};


	m_floor->SetMap(map);
	m_floor->Init();

	m_player->SetMap(map);

	for (auto enemy : m_enemy)
	{
		enemy->Update();
	}

	BattleManager::GetInstance()->SetPlayer(m_player.get());

	BattleManager::GetInstance()->SetEnemies(m_enemy);
	m_timeMan = TimeManager::GetInstance();

}

void MyGame::Update(StepTimer const & timer)
{
	// �������Q�[���̍X�V�����������ɒǉ�

	// ���̓}�l�[�W���̍X�V
	InputManager::GetInstance()->Update();
	// �f�o�b�O�}�l�[�W���̍X�V
	DebugManager::GetInstance()->Reset();

	m_timeMan->Update();

	m_camera->Update();

	m_floor->Update();
	m_player->Update();

	for (auto& enm : m_enemy)
	{
		enm->Update();
	}

	BattleManager::GetInstance()->Update();
}

void MyGame::Render(StepTimer const & timer)
{
	// �ŏ��̍X�V�̑O�͉����`�悵�Ȃ��悤�ɂ���
	// Don't try to render anything before the first Update.
	if (timer.GetFrameCount() == 0) {
		return;
	}

	Clear();

	// �J�����O�ݒ�?
	Graphics::Get().Context()->RSSetState(commonStates->CullNone());


	// �r���[�s��ƃv���W�F�N�V�����s����Z�b�g
	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);

	m_effect->Apply(Graphics::Get().Context().Get());
	Graphics::Get().Context()->IASetInputLayout(m_inputLayout.Get());
	// �������Q�[���̕`�揈���������ɒǉ�

	// �v���C���[�̕`��
	m_player->Draw();

	for (auto& enm : m_enemy)
	{
		enm->Draw();
	}

	// ���`��
	m_floor->Draw();

	// �X�v���C�g�`��
	this->spriteBatch->Begin();
	
	// �X�v���C�g�̕`��������ɒǉ�

	//�f�o�b�O�����̕`��
	DebugManager::GetInstance()->Draw(spriteBatch.get());
	
	this->spriteBatch->End();

	Present();
}

void MyGame::Finalize()
{
	// �������I�������������ɒǉ�
	delete m_timeMan;
	
	// ���N���X�̏I������
	Game::Finalize();
}
