/**
* @file Emitter.h
* @brief エミッタ基底クラスのヘッダファイル
* @author Y.kawamoto
* @date 2017/11/17
*/
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include <wrl\client.h>

class Emitter
{
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Vector4 = DirectX::SimpleMath::Vector4;
public:
	Emitter();
	Emitter(Vector3 position, Vector3 velocity, float lifeFrame);
	virtual ~Emitter(){}

	virtual void Update() = 0;
	virtual void Load(std::string typeName, wchar_t* fileName);
	virtual bool GetEndFlag() { return m_isEnd;}
protected:
	// 角度
	float m_param;
	// 寿命
	int m_lifeFrame;
	// 経過時間
	int m_currentFrame;
	// 座標
	Vector3 m_position;
	// 速度
	Vector3 m_velocity;
	// 終了フラグ
	bool m_isEnd;
protected:
	Vector3 CircleMove(float spd, float scl);
	Vector3 VelocityMove();

protected:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	// テクスチャ
};

