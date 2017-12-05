#pragma once
#include <SimpleMath.h>

#include "Obj3d\Obj3d.h"
#include "Command.h"
#include "Emitter.h"

class Panel
{
public:

	enum State
	{
		DEFAULT = 0, // 0b00000000
		ATTACK	= 1, // 0b00000001
		GUARD	= 2, // 0b00000010
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
	// 法線ベクトル(パネルが向いている方向ベクトル) 
	DirectX::SimpleMath::Vector3 m_normalVec;
	// パネルモデル
	std::unique_ptr<Obj3d> m_model;
	// コマンド
	std::unique_ptr<Command> m_command;
	// 状態
	int m_state;

	// エフェクトエミッタ
	std::unique_ptr<Emitter> m_emitter;
};

