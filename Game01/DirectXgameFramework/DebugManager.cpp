#include "pch.h"
#include "DebugManager.h"
#include "Framework\Graphics.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

DebugManager* DebugManager::s_pInstance = nullptr;

DebugManager::DebugManager()
{
	m_pSpriteFont = new SpriteFont(Graphics::Get().Device().Get(), L"Resources/myfile.spritefont");
}

void DebugManager::Draw(SpriteBatch* pSpriteBatch)
{
	for (auto& str : m_strings)
	{
		m_pSpriteFont->DrawString(pSpriteBatch, str.second.stream.str().c_str(), str.second.pos);
	}
}


void DebugManager::Add(std::string key, const DirectX::SimpleMath::Vector2 & vec, std::wstringstream & ss)
{
	m_strings.insert(make_pair(key, DebugString(ss, vec)));
}

void DebugManager::Add(std::string key, int x, int y, std::wstringstream & ss)
{
	DirectX::SimpleMath::Vector2 & vec = DirectX::SimpleMath::Vector2(x, y);
	m_strings.insert(make_pair(key, DebugString(ss, vec)));
}


void DebugManager::Reset()
{
	m_strings.clear();
}


DebugManager* DebugManager::GetInstance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = new DebugManager();
	}
	return s_pInstance;
}

