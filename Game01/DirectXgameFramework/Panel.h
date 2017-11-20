#pragma once
#include <SimpleMath.h>

#include "Obj3d\Obj3d.h"
#include "Command.h"


class Panel
{
public:

	enum State
	{
		DEFAULT = 0b000000,
		ATTACK	= 0b000001,
		GUARD	= 0b000010,

	};
	enum Points
	{
		ORIGIN,
		P1,
		P2,
		POINT_NUM
	};
public:
	Panel();
	~Panel();

	void Initialze(Obj3d* parent);
	void Load(wstring fileName);
	void Update();
	void Draw();

	int GetState()
	{
		return m_state;
	}
	DirectX::SimpleMath::Vector3 GetNormal()
	{
		return m_normalVec;
	}

	DirectX::SimpleMath::Vector3 CalcDirection(const DirectX::SimpleMath::Matrix& rotMat);

private:
	// �@���x�N�g��(�p�l���������Ă�������x�N�g��) 
	DirectX::SimpleMath::Vector3 m_normalVec;
	// �p�l�����f��
	std::unique_ptr<Obj3d> m_model;
	// �R�}���h
	std::unique_ptr<Command> m_command;

	int m_state;

private:

};

