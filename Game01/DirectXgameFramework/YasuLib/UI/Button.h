//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @File  Button.h
//!
//! @Brief  Button�N���X(UI2d���p��)�̃w�b�_�t�@�C��
//!			UI�֘A���Ǘ�
//! @Date   2017/07/24
//!
//! @Author Y.Kawamoto
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

#include <DDSTextureLoader.h>
#include <d3d11.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <wrl/client.h>

#include "UI2d.h"


class Button : public UI2d
{
private:

	// X���]�t���O
	bool m_XFliped;
	// �{�^����������Ă��邩
	bool m_isPushed;
	// �{�^���̃g���K�[����
	bool m_isTrigger;

	// �{�^����������Ă���t���[����
	int m_buttonCount;
	// �e�N�X�`���\
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
public:
	void Load(wchar_t* filename);
	bool Init() override;
	bool Init(const RECT& rect);
	void Update() override;
	void Draw(DirectX::SpriteBatch& spritebatch) override;

	// �{�^����������Ă��邩���擾
	bool GetPushed()
	{
		return m_isPushed;
	}

	// �{�^���������ꂽ�u�Ԃ����擾
	bool GetTrigger()
	{
		return m_isTrigger;
	}

	// X���]�t���O���Z�b�g
	void SetFlipX(bool flag)
	{
		m_XFliped = flag;
	}

	Button();
	~Button();
};

