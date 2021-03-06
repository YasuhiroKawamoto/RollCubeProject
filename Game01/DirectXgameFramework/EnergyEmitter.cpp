#include "EnergyEmitter.h"

#include "YasuLib\Utility\Utility.h"
#include "ParticleEffectManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace utl;

EnergyEmitter::EnergyEmitter(Vector3 position, Vector3 velocity, float lifeTime)
{
	m_param = 0;
	m_currentFrame = 0;
	m_position = position;
	m_velocity = velocity;
	m_lifeFrame = lifeTime;
	m_isEnd = false;
}

void EnergyEmitter::Update()
{
	// 寿命が過ぎていたら更新しない
	if (m_currentFrame >= m_lifeFrame) 
		m_isEnd = true;

	m_currentFrame++;

	float startAngle = Utility::RandomRange(0, 360);

	ParticleEffect particleData;
	// 玉の部分
	particleData.SetType("energy");
	particleData.SetLifeTime(0.5f);
	particleData.SetPosition(m_position);
	particleData.SetColor(Vector4(1, 0, 0, 0.15f), Vector4(1, 0, 0, 0.0f));
	particleData.SetRotation(XMConvertToRadians(startAngle), XMConvertToRadians(Utility::RandomRange(startAngle, startAngle + 90)));
	particleData.SetScale(6.0f, 0.0f);
	particleData.SetVelocity(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
	particleData.SetVertexData();

	ParticleEffectManager::GetInstance()->Entry(&particleData);
}

