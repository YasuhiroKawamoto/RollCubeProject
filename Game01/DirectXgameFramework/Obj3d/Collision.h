#pragma once

/// <summary>
///  �Փ˔��胉�C�u����
/// </summary>

#include <d3d11_1.h>
#include <SimpleMath.h>

// ��
class Sphere
{
public:
	// ���S���W
	DirectX::SimpleMath::Vector3 Center;
	// ���a
	float radius;

	// �R���X�g���N�^
	Sphere()
	{
		// �f�t�H���g�̔��a1m
		radius = 1.0f;
	}
};

// ����
class Segment
{
public:
	// �n�_���W
	DirectX::SimpleMath::Vector3 start;
	// �I�_���W
	DirectX::SimpleMath::Vector3 end;
};

// �O�p�`
class Triangle
{
public:
	// ���_���W
	DirectX::SimpleMath::Vector3 P0;
	DirectX::SimpleMath::Vector3 P1;
	DirectX::SimpleMath::Vector3 P2;
	// �@���x�N�g��
	DirectX::SimpleMath::Vector3 Normal;


};


bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB);

void ComputeTriangle(const DirectX::SimpleMath::Vector3 & _p0, const DirectX::SimpleMath::Vector3 & _p1,
					const DirectX::SimpleMath::Vector3 & _p2, Triangle * tri);

bool CheckSphere2Triangle(const Sphere & _sphere, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _inter);

bool CheckSegment2Triangle(const Segment & _segment, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _inter);

bool Point2Box(const DirectX::SimpleMath::Vector2& point, const DirectX::SimpleMath::Vector2& boxPos, RECT rect);
