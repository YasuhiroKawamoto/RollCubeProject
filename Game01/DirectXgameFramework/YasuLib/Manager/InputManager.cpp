//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @File  InputManager.cpp
//!
//! @Brief  �C���v�b�g�N���X�̃\�[�X�t�@�C��
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
// @>�T�@�v:�R���X�g���N�^(����J)
//
// @>���@��:�Ȃ�
// ===========================================
InputManager::InputManager()
{
	// �L�[�{�[�h�̏�����
	m_keyboard = new Keyboard();
	m_keyboardTracker = std::make_unique<Keyboard::KeyboardStateTracker>();

	// �}�E�X�̏�����
	m_mouse = std::make_unique<Mouse>();
	m_mouseTracker = std::make_unique<Mouse::ButtonStateTracker>();
}


// ===========================================
// @>�T�@�v: �C���X�^���X���擾
//
// @>���@��:�Ȃ�
//
// @>�߂�l:�@InputManager�ւ̃|�C���^
// ===========================================
InputManager* InputManager::GetInstance()
{
	if (s_instance == nullptr)
		s_instance = new InputManager();
	return s_instance;
}

// ===========================================
// @>�T�@�v:�C���v�b�g���̍X�V
//
// @>���@��:�Ȃ�
//
// @>�߂�l:�Ȃ�
// ===========================================
void InputManager::Update()
{
	// �}�E�X�̏����擾
	m_mouseState = this->m_mouse->GetState();
	this->m_mouseTracker->Update(this->m_mouseState);

	//�L�[�{�[�h�̍X�V
	m_keybordState = m_keyboard->GetState();
	m_keyboardTracker->Update(m_keybordState);
}
