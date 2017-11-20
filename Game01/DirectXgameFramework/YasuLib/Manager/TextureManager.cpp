//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @File  TextureManager.cpp
//!
//! @Brief  TextureManager�N���X�̃\�[�X�t�@�C��
//!			
//! @Date   2017/07/26
//!
//! @Author Y.Kawamoto
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


#include "../../pch.h"
#include "TextureManager.h"


#include "../../Framework/Graphics.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;
using namespace std;

TextureManager* TextureManager::s_instance = nullptr;

// ======================================================================================
// @>�T�@�v:�e�N�X�`���\�f�[�^���擾
//
// @>���@��:�t�@�C����(wchar_t* key)
//
// @>�߂�l:�e�N�X�`���@(ComPtr<ID3D11ShaderResourceView>) 
// ======================================================================================
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TextureManager::GetTexture(wchar_t* key)
{
	// �摜���ǂݍ��܂�Ă��Ȃ��ꍇ�̓��[�h���s��
	if (m_texutures[key] == nullptr)
		CreateDDSTextureFromFile(Graphics::Get().Device().Get(),key, nullptr, m_texutures[key].ReleaseAndGetAddressOf());

	// �摜�̃|�C���^��Ԃ�
	return m_texutures[key];
}

// ======================================================================================
// @>�T�@�v:�R���X�g���N�^
//
// @>���@��:�Ȃ�
// ======================================================================================
TextureManager::TextureManager()
{
}

// ======================================================================================
// @>�T�@�v:�e�N�X�`���}�l�[�W���̃C���X�^���X���擾
//
// @>���@��:�Ȃ�
//
// @>�߂�l:�C���X�^���X�@(TextureManager*)
// ======================================================================================
TextureManager* TextureManager::GetInstance()
{
	if (s_instance == nullptr)
		s_instance = new TextureManager();

	return s_instance;
}

