#include "TimeManager.h"


// �ÓI�����o�̏�����
TimeManager* TimeManager::s_instance = nullptr;
const float TimeManager::DELTA_TIME = 0.166666f;				// �~���b�萔

void TimeManager::Update()
{
	m_time += DELTA_TIME * m_timeScale;
}

// �C���X�^���X�̎擾
TimeManager* TimeManager::GetInstance()
{
	// �V���O���g���C���X�^���X�̎擾
	if(s_instance == nullptr)
		s_instance = new TimeManager();
	return s_instance;
}

// �R���X�g���N�^
TimeManager::TimeManager()
	:m_time(0.0f),
	m_timeScale(1.0f)
{
}
