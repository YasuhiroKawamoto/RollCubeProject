#include "Emitter.h"
#include "ParticleEffectManager.h"

#include <WICTextureLoader.h>

#include "Framework\Graphics.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

Emitter::Emitter()
{
}

Emitter::Emitter(Vector3 position, Vector3 velocity, float lifeFrame)
	:m_param(0.0f),
	m_lifeFrame(lifeFrame),
	m_currentFrame(0),

	m_position(position),
	m_velocity(velocity)
{
}

void Emitter::Load(std::string typeName, wchar_t * fileName)
{
	ID3D11Device* device = Graphics::Get().Device().Get();

	if (FAILED(CreateWICTextureFromFile(device, fileName, nullptr, m_texture.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateWICTextureFromFile Failed", NULL, MB_OK);
		return;
	}

	ParticleEffectManager::GetInstance()->AddTexture(typeName, m_texture);
}

Vector3 Emitter::CircleMove(float spd, float scl)
{
	// ‰~‰^“®
	m_param += spd;

	static Vector3 pos;
	pos.x = cosf(m_param) * scl;
	pos.y = 0.0f;
	pos.z = sinf(m_param) * scl;

	return pos;
}

Vector3 Emitter::VelocityMove()
{
	// ‘¬“x‚É‚æ‚éˆÚ“®
	return m_position + m_velocity;
}


