//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @File  TextureManager.h
//!
//! @Brief  TextureManagerクラスのヘッダファイル
//!			
//! @Date   2017/07/26
//!
//! @Author Y.Kawamoto
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

#include <map>

#include <wrl/client.h>
#include <d3d11_1.h>
#include <DDSTextureLoader.h>

class TextureManager
{
private:
	static TextureManager* s_instance;

	std::map<wchar_t*, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>  m_texutures;
public:
	~TextureManager(){}
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture(wchar_t* key);

private:
	TextureManager();
public:
	static TextureManager* GetInstance();

};
