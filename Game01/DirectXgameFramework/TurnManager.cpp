#include "pch.h"
#include "TurnManager.h"

TurnManager* TurnManager::s_instance = nullptr;

// �V���O���g���̎擾
TurnManager* TurnManager::GetInstance()
{
	if (s_instance == nullptr)
		s_instance = new TurnManager();
	return s_instance;
}

TurnManager::TurnManager()
{
}
