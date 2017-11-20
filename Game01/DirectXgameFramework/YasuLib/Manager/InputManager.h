//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @File  InputManager.h
//!
//! @Brief  �C���v�b�g�N���X�̃w�b�_�t�@�C��
//!			���͊֘A���Ǘ�
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
	// �C���X�^���X
	static InputManager* s_instance;
	// �}�E�X�X�e�[�g
	DirectX::Mouse::State m_mouseState;
	// �}�E�X
	std::unique_ptr<DirectX::Mouse> m_mouse;
	// �{�^���X�e�[�g�g���b�J�[
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseTracker;

	// �}�E�X�X�e�[�g
	DirectX::Keyboard::State m_keybordState;
	// �L�[�{�[�h
	DirectX::Keyboard* m_keyboard;
	// �L�[�{�[�h�g���b�J�[
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;



private:
	InputManager();
	~InputManager() {}
public:
	// �C���X�^���X�̎擾
	static InputManager* GetInstance();
	// �X�V
	void Update();

	// �}�E�X�X�e�[�g���擾
	DirectX::Mouse::State GetMouseState()
	{
		return m_mouseState;
	}
	// �}�E�X�g���b�J�[���擾
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker>& GetMouseTracker()
	{
		return move(m_mouseTracker);
	}

	// �L�[�{�[�h�X�e�[�g���擾
	DirectX::Keyboard::State GetKeybordState()
	{
		return m_keybordState;
	}

	// �L�[�{�[�h�g���b�J�[���擾
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>& GetKeybordTracker()
	{
		return move(m_keyboardTracker);
	}


};
