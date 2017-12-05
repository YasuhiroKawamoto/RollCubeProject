/**
* @file BattleManager.h
* @brief 簡単な説明
* @author Yasuhiro Kawamoto
* @date 2017/10/30
*/

#pragma once
#include <vector>

#include "Player.h"
#include "Enemy.h"

class BattleManager
{
public:
	enum TurnID
	{
		PLAYER_MOVE,
		PLAYER_ACTION,
		ENEMY_MOVE,
		ENEMY_ACTION,

		ALL_TURNS
	};
	~BattleManager();

	void Update();

	// 戦闘マネージャにプレイヤを登録
	void SetPlayer(Player* pPlayer)
	{
		m_player = pPlayer;
	}

	// 戦闘マネージャに敵を登録
	void SetEnemies(const std::vector<Enemy*>& pEnemies)
	{
		for (auto& enemy : pEnemies)
		{
			m_enemies.push_back(enemy);
		}
	}
public:
	static BattleManager* GetInstance();

private:
	static BattleManager* s_instance;
private:
	Player* m_player;
	std::vector<Enemy*> m_enemies;
	TurnID m_turnState;
private:
	BattleManager();

};
