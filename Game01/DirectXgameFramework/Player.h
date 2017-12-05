#pragma once

#include <map>
#include "Obj3d\Obj3d.h"
#include "Panel.h"


class Player
{

public:
	using Vector2 = DirectX::SimpleMath::Vector2;
	using Vector3 = DirectX::SimpleMath::Vector3;
public:
	enum MOVE_DIRECTION
	{
		NONE = 0,
		FRONT,
		BACK,
		LEFT,
		RIGHT
	};

public:
	std::map<string, std::unique_ptr<Obj3d>> m_parts;
	std::map<string, std::unique_ptr<Panel>> m_panels;

	Vector3 NormalVec;

	Player();
	~Player();

	bool CheckOnMap(const Vector2 & dir);

	void Init();
	void Draw();
	void Update();
	void Move();


	bool IsMoving(){ return m_isMoving;	}
	int GetState(){	return m_state;}
	void SetMap(int map[10][10]);

	MOVE_DIRECTION movingState;

private:
	//void Rotate(MOVE_DIRECTION dir, float* time);
	

private:
	std::unique_ptr<Obj3d> hoge;

	int m_state;
	DirectX::SimpleMath::Quaternion m_startAng;
	DirectX::SimpleMath::Quaternion m_endAng;

	bool m_isMoving;
	int m_map[10][10];

private:
	void RotateFront(float* time);
	void RotateBack(float* time);
	void RotateLeft(float* time);
	void RotateRight(float* time);
	//DirectX::SimpleMath::Vector3 CalcDirection();

};

