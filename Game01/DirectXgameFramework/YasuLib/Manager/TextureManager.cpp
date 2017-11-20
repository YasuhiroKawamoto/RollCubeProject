//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @File  TextureManager.cpp
//!
//! @Brief  TextureManagerクラスのソースファイル
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
// @>概　要:テクスチャ―データを取得
//
// @>引　数:ファイル名(wchar_t* key)
//
// @>戻り値:テクスチャ　(ComPtr<ID3D11ShaderResourceView>) 
// ======================================================================================
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TextureManager::GetTexture(wchar_t* key)
{
	// 画像が読み込まれていない場合はロードを行う
	if (m_texutures[key] == nullptr)
		CreateDDSTextureFromFile(Graphics::Get().Device().Get(),key, nullptr, m_texutures[key].ReleaseAndGetAddressOf());

	// 画像のポインタを返す
	return m_texutures[key];
}

// ======================================================================================
// @>概　要:コンストラクタ
//
// @>引　数:なし
// ======================================================================================
TextureManager::TextureManager()
{
}

// ======================================================================================
// @>概　要:テクスチャマネージャのインスタンスを取得
//
// @>引　数:なし
//
// @>戻り値:インスタンス　(TextureManager*)
// ======================================================================================
TextureManager* TextureManager::GetInstance()
{
	if (s_instance == nullptr)
		s_instance = new TextureManager();

	return s_instance;
}

