#pragma once
#include "Emitter.h"
class EnergyEmitter :public Emitter
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Vector4 = DirectX::SimpleMath::Vector4;
public:
	EnergyEmitter(Vector3 position, Vector3 velocity, float lifeTime);
	~EnergyEmitter() {}
	void Update() override;

};

