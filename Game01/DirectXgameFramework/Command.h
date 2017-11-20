#pragma once
class Command
{
public:
	Command();
	virtual ~Command(){}
	virtual void Action() = 0;
};

