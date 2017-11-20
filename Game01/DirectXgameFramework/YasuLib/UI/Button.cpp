#include "Button.h"

#include "Graphics.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;


bool Button::Init()
{
	return true;
}


bool Button::Init(const RECT& rect)
{
	m_rect = rect;
	this->SetOrigin(Vector2(0.5f, 0.5f));
	
	return true;
}

void Button::Load(wchar_t* filename)
{
	auto textureLoder = TextureManager::GetInstance();
	m_texture = textureLoder->GetTexture(filename);
	
}


void Button::Update()
{
	// 親座標に依存させる
	if (m_parent != nullptr)
		m_drawPos = m_pos + m_parent->GetDrawPos();


	// ==== マウスとの当たり判定
	

	// ==マウスステートを取得
	auto& mouseState = InputManager::GetInstance()->GetMouseState();
	Vector2 mousePos = Vector2(mouseState.x, mouseState.y);
	m_isTrigger = m_isPushed = false;


	if (mouseState.leftButton)
		m_buttonCount++;
	else
		m_buttonCount = 0;

	// 矩形と点の当たり判定
	if (Point2Box(mousePos, m_drawPos, m_rect))
	{
		// 1フレーム以上押されたとき
		if (m_buttonCount >= 1)
			m_isPushed = true;

		// 1フレームだけ押されたとき
		if (m_buttonCount == 1)
			m_isTrigger = true;
	}

	
}

void Button::Draw(DirectX::SpriteBatch& spritebatch)
{
	float angle = 0.0f;
	// 反転
	if(m_XFliped)
	{
		angle = XMConvertToRadians(180.0f);
	}


	spritebatch.Draw(m_texture.Get(), m_drawPos, &m_rect, Colors::White,angle, m_origin);

}

Button::Button()
	:m_XFliped(false),
	m_isPushed(false),
	m_isTrigger(false),
	m_buttonCount(0)
{
}


Button::~Button()
{
}
