#pragma once

/// <summary>
///  衝突判定ライブラリ
/// </summary>

#include <d3d11_1.h>
#include <SimpleMath.h>

// 球
class Sphere
{
public:
	// 中心座標
	DirectX::SimpleMath::Vector3 Center;
	// 半径
	float radius;

	// コンストラクタ
	Sphere()
	{
		// デフォルトの半径1m
		radius = 1.0f;
	}
};

// 線分
class Segment
{
public:
	// 始点座標
	DirectX::SimpleMath::Vector3 start;
	// 終点座標
	DirectX::SimpleMath::Vector3 end;
};

// 三角形
class Triangle
{
public:
	// 頂点座標
	DirectX::SimpleMath::Vector3 P0;
	DirectX::SimpleMath::Vector3 P1;
	DirectX::SimpleMath::Vector3 P2;
	// 法線ベクトル
	DirectX::SimpleMath::Vector3 Normal;


};


bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB);

void ComputeTriangle(const DirectX::SimpleMath::Vector3 & _p0, const DirectX::SimpleMath::Vector3 & _p1,
					const DirectX::SimpleMath::Vector3 & _p2, Triangle * tri);

bool CheckSphere2Triangle(const Sphere & _sphere, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _inter);

bool CheckSegment2Triangle(const Segment & _segment, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _inter);

bool Point2Box(const DirectX::SimpleMath::Vector2& point, const DirectX::SimpleMath::Vector2& boxPos, RECT rect);
