#pragma once
#include "Obj3d\Obj3d.h"
#include <memory>

#include "Player.h"

class Enemy
{
public:
	Enemy();
	Enemy(const Enemy& enm);
	~Enemy();

	void Load(wchar_t* fileName);
	void Draw();
	void Update();
	void Move();
	void Init(DirectX::SimpleMath::Vector3 pos);
	void SetMap(int map[10][10]);
	bool CheckPlayer(Player* pPlayer);
	void TakeDamage();

	bool CheckOnMap(const DirectX::SimpleMath::Vector2& dir);
	void SetFlag(bool _isAdjoining)
	{
		isAdjoining = _isAdjoining;
	}
public: 
	bool isAdjoining;
private:
	std::unique_ptr<Obj3d> m_enemyModel;
	DirectX::SimpleMath::Vector3 m_vec;


};
