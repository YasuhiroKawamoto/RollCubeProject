//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @File  Button.h
//!
//! @Brief  Buttonクラス(UI2dを継承)のヘッダファイル
//!			UI関連を管理
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

	// X反転フラグ
	bool m_XFliped;
	// ボタンが押されているか
	bool m_isPushed;
	// ボタンのトリガー判定
	bool m_isTrigger;

	// ボタンが押されているフレーム数
	int m_buttonCount;
	// テクスチャ―
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
public:
	void Load(wchar_t* filename);
	bool Init() override;
	bool Init(const RECT& rect);
	void Update() override;
	void Draw(DirectX::SpriteBatch& spritebatch) override;

	// ボタンが押されているかを取得
	bool GetPushed()
	{
		return m_isPushed;
	}

	// ボタンが押された瞬間かを取得
	bool GetTrigger()
	{
		return m_isTrigger;
	}

	// X反転フラグをセット
	void SetFlipX(bool flag)
	{
		m_XFliped = flag;
	}

	Button();
	~Button();
};

