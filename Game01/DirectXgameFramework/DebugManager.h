#pragma once
#include <SpriteFont.h>
#include <SpriteBatch.h>
#include <SimpleMath.h>
#include <sstream>
#include <SimpleMath.h>
#include <map>
#include <SpriteBatch.h>


class DebugManager
{
	struct DebugString
	{
		DirectX::SimpleMath::Vector2 pos;
		std::wstringstream stream;

		// コンストラクタ
		DebugString(std::wstringstream& _stream, DirectX::SimpleMath::Vector2 _pos)
		{
			stream = move(_stream);
			pos = _pos;
		}
	};

public:
	DebugManager();
	~DebugManager(){}
	void Draw(DirectX::SpriteBatch* pSpriteBatch);
	void Add(std::string key, const DirectX::SimpleMath::Vector2& vec, std::wstringstream& ss);
	void Add(std::string key, int x, int y, std::wstringstream & ss);
	void Reset();
	static DebugManager* GetInstance();

private:
	DirectX::SpriteFont* m_pSpriteFont;
	std::map<std::string, DebugString> m_strings;

private:
	static DebugManager* s_pInstance;
};

