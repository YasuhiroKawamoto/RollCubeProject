#include "pch.h"
#include "AttackCommand.h"
#include <sstream>
#include "DebugManager.h"

AttackCommand::AttackCommand()
{
}


AttackCommand::~AttackCommand()
{
}

void AttackCommand::Action()
{
	std::wstringstream ss;
	ss << "Attack!";
	DebugManager::GetInstance()->Add("command", DirectX::SimpleMath::Vector2(0, 0), ss);
}
