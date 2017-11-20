//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @File  InputManager.cpp
//!
//! @Brief  インプットクラスのソースファイル
//!
//! @Date   2017/07/24
//!
//! @Author Y.Kawamoto
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


#include "InputManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

InputManager* InputManager::s_instance = nullptr;

// ===========================================
// @>概　要:コンストラクタ(非公開)
//
// @>引　数:なし
// ===========================================
InputManager::InputManager()
{
	// キーボードの初期化
	m_keyboard = new Keyboard();
	m_keyboardTracker = std::make_unique<Keyboard::KeyboardStateTracker>();

	// マウスの初期化
	m_mouse = std::make_unique<Mouse>();
	m_mouseTracker = std::make_unique<Mouse::ButtonStateTracker>();
}


// ===========================================
// @>概　要: インスタンスを取得
//
// @>引　数:なし
//
// @>戻り値:　InputManagerへのポインタ
// ===========================================
InputManager* InputManager::GetInstance()
{
	if (s_instance == nullptr)
		s_instance = new InputManager();
	return s_instance;
}

// ===========================================
// @>概　要:インプット情報の更新
//
// @>引　数:なし
//
// @>戻り値:なし
// ===========================================
void InputManager::Update()
{
	// マウスの情報を取得
	m_mouseState = this->m_mouse->GetState();
	this->m_mouseTracker->Update(this->m_mouseState);

	//キーボードの更新
	m_keybordState = m_keyboard->GetState();
	m_keyboardTracker->Update(m_keybordState);
}
