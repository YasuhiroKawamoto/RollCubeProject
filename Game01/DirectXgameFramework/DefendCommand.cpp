#include "pch.h"
#include "DefendCommand.h"

#include "DebugManager.h"
#include <sstream>


DefendCommand::DefendCommand()
{
}


DefendCommand::~DefendCommand()
{
}

void DefendCommand::Action()
{
	std::wstringstream ss;
	ss << "Defend!";
	DebugManager::GetInstance()->Add("command", DirectX::SimpleMath::Vector2(0, 0), ss);
}
