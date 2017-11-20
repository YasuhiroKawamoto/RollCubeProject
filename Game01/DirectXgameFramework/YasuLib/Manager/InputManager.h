//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @File  InputManager.h
//!
//! @Brief  インプットクラスのヘッダファイル
//!			入力関連を管理
//! @Date   2017/09/24
//!
//! @Author Y.Kawamoto
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include <Mouse.h>
#include <Keyboard.h>

class InputManager
{
private:
	// インスタンス
	static InputManager* s_instance;
	// マウスステート
	DirectX::Mouse::State m_mouseState;
	// マウス
	std::unique_ptr<DirectX::Mouse> m_mouse;
	// ボタンステートトラッカー
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseTracker;

	// マウスステート
	DirectX::Keyboard::State m_keybordState;
	// キーボード
	DirectX::Keyboard* m_keyboard;
	// キーボードトラッカー
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;



private:
	InputManager();
	~InputManager() {}
public:
	// インスタンスの取得
	static InputManager* GetInstance();
	// 更新
	void Update();

	// マウスステートを取得
	DirectX::Mouse::State GetMouseState()
	{
		return m_mouseState;
	}
	// マウストラッカーを取得
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker>& GetMouseTracker()
	{
		return move(m_mouseTracker);
	}

	// キーボードステートを取得
	DirectX::Keyboard::State GetKeybordState()
	{
		return m_keybordState;
	}

	// キーボードトラッカーを取得
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>& GetKeybordTracker()
	{
		return move(m_keyboardTracker);
	}


};
