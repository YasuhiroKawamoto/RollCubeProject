#include "TimeManager.h"


// 静的メンバの初期化
TimeManager* TimeManager::s_instance = nullptr;
const float TimeManager::DELTA_TIME = 0.166666f;				// ミリ秒定数

void TimeManager::Update()
{
	m_time += DELTA_TIME * m_timeScale;
}

// インスタンスの取得
TimeManager* TimeManager::GetInstance()
{
	// シングルトンインスタンスの取得
	if(s_instance == nullptr)
		s_instance = new TimeManager();
	return s_instance;
}

// コンストラクタ
TimeManager::TimeManager()
	:m_time(0.0f),
	m_timeScale(1.0f)
{
}
