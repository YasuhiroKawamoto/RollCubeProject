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
* @brief �p�[�e�B�N���G�t�F�N�g�̃R���X�g���N�^
* @param (Vector3& pos) �p�[�e�B�N���̍��W
* @param (Vector4& col) �p�[�e�B�N���̐F
* @param (float sca) �p�[�e�B�N���̑傫��
* @param (float rot) �p�[�e�B�N���̉�]
* @param (float lif) �p�[�e�B�N���̎���
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

	// ���݂̕�Ԉʒu���擾
	float learpTime = m_currentTime / m_lifeTime;

	// �F�ω�
	m_vertexData->color = Vector4::Lerp(m_startColor, m_endColor, learpTime);

	// �X�P�[���ω�
	m_vertexData->textureCoordinate.x = Utility::Lerp(m_startScale, m_endScale, learpTime);

	// ��]�ω�
	m_vertexData->textureCoordinate.y = Utility::Lerp(m_startRotation, m_endRotation, learpTime);


	// �ړ�
	DirectX::XMFLOAT3 pos = m_vertexData->position;
	pos = pos + m_velocity;
	m_velocity += m_accel;

	m_vertexData->position  = pos;

	// ���Ŏ�
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
