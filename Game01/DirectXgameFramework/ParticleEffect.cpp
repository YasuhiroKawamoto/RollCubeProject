#include "ParticleEffect.h"

#include "YasuLib\Utility\Utility.h"

using namespace utl;

const float ParticleEffect::deltaTime = 16 / 1000.0f;

ParticleEffect::ParticleEffect()
{
	
}

ParticleEffect::ParticleEffect(const ParticleEffect & pe)
{
	m_vertexData = std::make_unique<DirectX::VertexPositionColorTexture>();

	this->m_currentTime = 0.0f;
	this->m_isEnd = false;

	this->m_type = pe.m_type;


	this->m_startScale= pe.m_startScale;
	this->m_endScale = pe.m_endScale;

	this->m_startRotation = pe.m_startRotation;
	this->m_endRotation = pe.m_endRotation;

	this->m_startColor = pe.m_startColor;
	this->m_endColor = pe.m_endColor;

	this->m_lifeTime = pe.m_lifeTime;
	this->m_velocity = pe.m_velocity;
	this->m_accel = pe.m_accel;
	this->m_position = pe.m_position;

	this->m_vertexData->color = pe.m_vertexData->color;
	this->m_vertexData->position = pe.m_vertexData->position;
	this->m_vertexData->textureCoordinate = pe.m_vertexData->textureCoordinate;


}

/**
* @fn ParticleEffect()
* @brief パーティクルエフェクトのコンストラクタ
* @param (Vector3& pos) パーティクルの座標
* @param (Vector4& col) パーティクルの色
* @param (float sca) パーティクルの大きさ
* @param (float rot) パーティクルの回転
* @param (float lif) パーティクルの寿命
*/
ParticleEffect::ParticleEffect(const Vector3 & pos, const Vector4 & col, const float sca, const float rot, const float lif, const Vector3 & vel)
	: m_lifeTime(lif),
	m_currentTime(0.0f),
	m_isEnd(false),
	m_velocity(vel)

{
	m_vertexData = std::make_unique<DirectX::VertexPositionColorTexture>();

	m_vertexData->position = pos;
	m_vertexData->color = col;
	m_vertexData->textureCoordinate.x = sca;
	m_vertexData->textureCoordinate.y = rot;

}


ParticleEffect::~ParticleEffect()
{
}

void ParticleEffect::Update()
{
	m_currentTime += deltaTime;

	// 現在の補間位置を取得
	float learpTime = m_currentTime / m_lifeTime;

	// 色変化
	m_vertexData->color = Vector4::Lerp(m_startColor, m_endColor, learpTime);

	// スケール変化
	m_vertexData->textureCoordinate.x = Utility::Lerp(m_startScale, m_endScale, learpTime);

	// 回転変化
	m_vertexData->textureCoordinate.y = Utility::Lerp(m_startRotation, m_endRotation, learpTime);


	// 移動
	DirectX::XMFLOAT3 pos = m_vertexData->position;
	pos = pos + m_velocity;
	m_velocity += m_accel;

	m_vertexData->position  = pos;

	// 消滅時
	if (m_currentTime > m_lifeTime)
		m_isEnd = true;
}

void ParticleEffect::SetVertexData()
{
	m_vertexData = std::make_unique<DirectX::VertexPositionColorTexture>();

	m_vertexData->position = m_position;
	m_vertexData->color = m_startColor;
	m_vertexData->textureCoordinate.x = m_startScale;
	m_vertexData->textureCoordinate.y = m_startRotation;
}
