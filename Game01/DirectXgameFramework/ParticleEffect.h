/**
* @file ParticleEffect.h
* @brief ParticleEffect�N���X�̃w�b�_
* @author Yasuhiro Kawamoto
* @date 2017/11/08
*/
#pragma once

#include <vector>
#include <memory>
#include <string>

#include <d3d11_1.h>

#include <SimpleMath.h>
#include <VertexTypes.h>

// �p�[�e�B�N��1�̃f�[�^���Ǘ�����N���X
class ParticleEffect
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Vector4 = DirectX::SimpleMath::Vector4;
public:
	static const float deltaTime;		// �~���b
public:
	// �f�t�H���g�R���X�g���N�^
	ParticleEffect();

	// �R�s�[�R���X�g���N�^
	ParticleEffect(const ParticleEffect& pe);
	// ��������R���X�g���N�^
	ParticleEffect(const Vector3 & pos, const Vector4 & col, const float sca, const float rot, const float lif, const Vector3 & vel);

	~ParticleEffect();


	void Update();
	void SetVertexData();

	void SetPosition(const Vector3 & pos = Vector3::Zero)
	{
		m_position = pos;
	}

	void SetColor(const Vector4 & startCol = Vector4(1, 1, 1, 1), const Vector4 & endCol = Vector4(1, 1, 1, 1))
	{
		m_startColor = startCol;
		m_endColor = endCol;
	}

	void SetRotation(float startRot = 0.0f, float endRot = 0.0f)
	{
		m_startRotation = startRot;
		m_endRotation = endRot;
	}

	void SetScale(float startSca = 1.0f, float endSca = 1.0f)
	{
		m_startScale = startSca;
		m_endScale = endSca;
	}

	void SetVelocity(Vector3 vel = Vector3::Zero, Vector3 acc = Vector3::Zero)
	{
		m_velocity = vel;
		m_accel = acc;
	}

	void SetLifeTime(float time)
	{
		m_lifeTime = time;
	}

	bool GetEndFlag()
	{
		return m_isEnd;
	}

	DirectX::VertexPositionColorTexture* GetVertexData()
	{
		return m_vertexData.get();
	}


	void SetType(std::string type)
	{
		m_type = type;
	}

	std::string GetType()
	{
		return m_type;
	}


private:
	float m_lifeTime;		// ���ł܂ł̎���(�b)
	float m_currentTime;	// �������Ă���̎���(�b)
	bool m_isEnd;			// �I���t���O
	float m_startRotation;	// �ŏ��̊p�x
	float m_endRotation;	// �Ō�̊p�x
	float m_startScale;		// �ŏ��̃X�P�[��
	float m_endScale;		// �Ō�̃X�P�[��
	Vector4 m_startColor;	// �ŏ��̐F
	Vector4 m_endColor;		// �Ō�̐F
	Vector3 m_position;		// ���W
	Vector3 m_velocity;		// �ړ���
	Vector3 m_accel;		// �����x

	std::string m_type;		// �G�t�F�N�g�̎��
	std::unique_ptr<DirectX::VertexPositionColorTexture> m_vertexData;	// ���_�f�[�^

};

