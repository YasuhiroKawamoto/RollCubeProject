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
	// �e���W�Ɉˑ�������
	if (m_parent != nullptr)
		m_drawPos = m_pos + m_parent->GetDrawPos();


	// ==== �}�E�X�Ƃ̓����蔻��
	

	// ==�}�E�X�X�e�[�g���擾
	auto& mouseState = InputManager::GetInstance()->GetMouseState();
	Vector2 mousePos = Vector2(mouseState.x, mouseState.y);
	m_isTrigger = m_isPushed = false;


	if (mouseState.leftButton)
		m_buttonCount++;
	else
		m_buttonCount = 0;

	// ��`�Ɠ_�̓����蔻��
	if (Point2Box(mousePos, m_drawPos, m_rect))
	{
		// 1�t���[���ȏ㉟���ꂽ�Ƃ�
		if (m_buttonCount >= 1)
			m_isPushed = true;

		// 1�t���[�����������ꂽ�Ƃ�
		if (m_buttonCount == 1)
			m_isTrigger = true;
	}

	
}

void Button::Draw(DirectX::SpriteBatch& spritebatch)
{
	float angle = 0.0f;
	// ���]
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
