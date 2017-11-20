#pragma once
#include "Command.h"
class DefendCommand :public Command
{
public:
	DefendCommand();
	~DefendCommand();
	void Action() override;
};

