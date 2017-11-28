#include "Enemy.h"
#include "DebugManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;


const int MOVE_WAIT = 300;

Enemy::Enemy()
	:isAdjoining(false)
{
	m_enemyModel = std::make_unique<Obj3d>();
}

Enemy::Enemy(const Enemy& enm) {
}

Enemy::~Enemy()
{
}

void Enemy::Load(wchar_t * fileName)
{
	m_enemyModel->LoadModel(fileName);
}

void Enemy::Draw()
{
	m_enemyModel->Draw();
}

void Enemy::Update()
{
	static int cnt = 0;
	cnt++;

	if (cnt >= MOVE_WAIT)
	{
		int dir = rand() % 4;

		switch (dir)
		{
		case 0:
			if (CheckOnMap(Vector2(1, 0)))
			{
				m_enemyModel->SetTranslation(m_enemyModel->GetTranslation() + Vector3(1, 0, 0));
			}
			break;
		case 1:
			if (CheckOnMap(Vector2(-1, 0)))
			{
				m_enemyModel->SetTranslation(m_enemyModel->GetTranslation() + Vector3(-1, 0, 0));
			}
			break;
		case 2:
			if (CheckOnMap(Vector2(0, 1)))
			{
				m_enemyModel->SetTranslation(m_enemyModel->GetTranslation() + Vector3(0, 0, 1));
			}
			break;
		case 3:
			if (CheckOnMap(Vector2(0, -1)))
			{
				m_enemyModel->SetTranslation(m_enemyModel->GetTranslation() + Vector3(0, 0, -1));
			}
			break;
		default:
			break;
		}

		cnt = 0;
	}

	// プレイヤーと隣接していたらダメージを食らう
	if (isAdjoining)
		TakeDamage();
	
	m_enemyModel->Update();
}

void Enemy::Move()
{
}

void Enemy::Init(Vector3 pos)
{
	m_enemyModel->SetTranslation(pos);
}

void Enemy::SetMap(int map[10][10])
{
	int checkGridY = (int)(m_enemyModel->GetTranslation().z + 5);
	int checkGridX = (int)(m_enemyModel->GetTranslation().x + 5);

	map[checkGridY][checkGridX] = 1;

	return;
}

bool Enemy::CheckPlayer(Player* pPlayer)
{
	Obj3d* player = pPlayer->m_parts["main"].get();

	wstringstream ss;
	ss << "PlayerPos::" << player->GetTranslation().x << "," << player->GetTranslation().y << "," << player->GetTranslation().z;
	DebugManager::GetInstance()->Add("player", Vector2(0, 20), ss);

	Vector3 front = player->GetTranslation() + Vector3(0.0f, -0.5f, -1.0f);
	Vector3 right = player->GetTranslation() + Vector3(1.0f, -0.5f, 0.0f);
	Vector3 left = player->GetTranslation() + Vector3(-1.0f, -0.5f, 0.0f);
	Vector3 back = player->GetTranslation() + Vector3(0.0f, -0.5f, 1.0f);

	if (m_enemyModel->GetTranslation() == front ||
		m_enemyModel->GetTranslation() == right ||
		m_enemyModel->GetTranslation() == left ||
		m_enemyModel->GetTranslation() == back )
	{
		return true;
	}
	return false;
}

void Enemy::TakeDamage()
{
	m_vec += DirectX::SimpleMath::Vector3(0.05f, 0.25f, 0.25f);
	m_enemyModel->SetTranslation(m_enemyModel->GetTranslation()+ m_vec);
}



bool Enemy::CheckOnMap(const Vector2& dir)
{
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



	int checkGridY = (int)(dir.y + m_enemyModel->GetTranslation().z + 5);
	int checkGridX = (int)(dir.x + m_enemyModel->GetTranslation().x + 5);

	if (checkGridY < 0 || checkGridY>9 || checkGridX < 0 || checkGridX > 9)
		return false;



	if (map[checkGridY][checkGridX] == 0)
		return false;

	return true;

}