#include "pch.h"
#include "BattleManager.h"
#include "DebugManager.h"
#include <sstream>

BattleManager* BattleManager::s_instance = nullptr;
BattleManager::BattleManager()
{
}

/**
* @fn
* �C���X�^���X���擾����ÓI�֐�
* @brief �C���X�^���X��nullptr�Ȃ琶�����A���݂��Ă���΂��̃C���X�^���X��Ԃ�
* @param �Ȃ�
* @return �C���X�^���X�̃|�C���^
*/
BattleManager * BattleManager::GetInstance()
{
	if (!s_instance)
	{
		s_instance = new BattleManager();
	}
	return s_instance;
}


BattleManager::~BattleManager()
{
	delete m_player;
	m_enemies.clear();
}

void BattleManager::Update()
{
	// �ړG���v���C�����A�^�b�N���
	for (auto& enemy : m_enemies)
	{
		auto flag = (m_player->GetState() & Panel::State::ATTACK);
		if (enemy->CheckPlayer(m_player) && flag)
		{
			enemy->SetFlag(true);
		}
	}


}