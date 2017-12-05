/**
* @file ParticleEffect.h
* @brief ParticleEffectクラスのヘッダ
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

// パーティクル1つのデータを管理するクラス
class ParticleEffect
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Vector4 = DirectX::SimpleMath::Vector4;
public:
	static const float deltaTime;		// ミリ秒
public:
	// デフォルトコンストラクタ
	ParticleEffect();

	// コピーコンストラクタ
	ParticleEffect(const ParticleEffect& pe);
	// 引数ありコンストラクタ
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
	float m_lifeTime;		// 消滅までの時間(秒)
	float m_currentTime;	// 発生してからの時間(秒)
	bool m_isEnd;			// 終了フラグ
	float m_startRotation;	// 最初の角度
	float m_endRotation;	// 最後の角度
	float m_startScale;		// 最初のスケール
	float m_endScale;		// 最後のスケール
	Vector4 m_startColor;	// 最初の色
	Vector4 m_endColor;		// 最後の色
	Vector3 m_position;		// 座標
	Vector3 m_velocity;		// 移動量
	Vector3 m_accel;		// 加速度

	std::string m_type;		// エフェクトの種類
	std::unique_ptr<DirectX::VertexPositionColorTexture> m_vertexData;	// 頂点データ

};

