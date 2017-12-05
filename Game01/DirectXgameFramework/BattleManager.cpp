#include "pch.h"
#include "BattleManager.h"
#include "DebugManager.h"
#include <sstream>

BattleManager* BattleManager::s_instance = nullptr;
BattleManager::BattleManager()
	:m_turnState(TurnID::PLAYER_MOVE)
{
}

/**
* @fn
* インスタンスを取得する静的関数
* @brief インスタンスがnullptrなら生成し、存在していればそのインスタンスを返す
* @param なし
* @return インスタンスのポインタ
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
	switch (m_turnState)
	{
	case BattleManager::PLAYER_MOVE:
		m_player->Move();
		if (m_player->IsMoving())
		{
			//m_turnState = BattleManager::PLAYER_ACTION;
		}

		// 接敵かつプレイヤがアタック状態
		for (auto& enemy : m_enemies)
		{
			int flag = (m_player->GetState() & Panel::State::ATTACK);
			if (enemy->CheckPlayer(m_player) && flag)
			{
				enemy->SetFlag(true);
			}
		}
		break;
	case BattleManager::PLAYER_ACTION:


		break;
	case BattleManager::ENEMY_MOVE:
		break;
	case BattleManager::ENEMY_ACTION:
		break;
	default:
		break;
	}





}
