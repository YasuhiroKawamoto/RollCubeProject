// Game.h

#pragma once
#ifndef GAME
#define GAME

#include <windows.h>
#include <iostream>
#include <string>
#include <iomanip>

#include <d3d11.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Model.h>
#include <Keyboard.h>
#include <GeometricPrimitive.h>
#include <WICTextureLoader.h>
#include <Effects.h>

#include "..\StepTimer.h"

#include "Window.h"
#include "Graphics.h"
#include "DebugCamera.h"
#include "Grid.h"

class Window;

// D3D11デバイスを生成し、ゲームループを提供する基本ゲーム実装
// A basic game implementation that creates a D3D11 device and provides a game loop.
class Game
{
public:
	// コンストラクタ Constructor
    Game(int width, int height);
    // 初期化と管理 Initialization and management
	virtual void Initialize();
	// 終了処理をおこなう Finalize game
	virtual void Finalize();
    // 基本ゲームループ Basic game loop
	MSG Update();

    // メッセージ Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);
    // プロパティ Properties
    void GetDefaultSize(int& width, int& height) const;

protected:
	// ゲームを更新する Update game
    virtual void Update(DX::StepTimer const& timer);
    // シーンを描画する Render scene
	virtual void Render(DX::StepTimer const & timer);
	// 画面をクリアする Clear screen
	virtual void Clear();
	virtual void Present();
	// FPSを描画する Draw FPS
	void DrawFPS();

protected:

	// インスタンスハンドル
	HINSTANCE hInstance;
	// 実行時のウィンドウの大きさ
	int nCmdShow;
	// デバイスリソース Device resources
	HWND hWnd;
	// 出力幅 window width
	int width;
	// 出力高 window height
	int height;

	// ウィンドウデータ
	std::unique_ptr<Window> window;
	// グラフィックス Graphics
	std::unique_ptr<Graphics> graphics;
	// 機能レベル Feature level
    D3D_FEATURE_LEVEL featureLevel;
    // ループタイマーを描画する Rendering loop timer
    DX::StepTimer timer;

	// キーボード Keyboard
	std::unique_ptr<Keyboard> keyboard;
	// スプライトバッチ SpriteBatch
	std::unique_ptr<SpriteBatch>	spriteBatch;

	// グリッドフロア GridFloor
	std::unique_ptr<GridFloor> gridFloor;
	// フォント Font
	std::unique_ptr<SpriteFont> font;
	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	//入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// エフェクトファクトリインターフェース IEffectFactory
	std::unique_ptr<IEffectFactory> fxFactory;
	// コモンステート CommonStates
	std::unique_ptr<CommonStates> commonStates;

	// ワールド world
	DirectX::SimpleMath::Matrix world;
	// スケール scale
	float scale;


	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// プロジェクション行列
	DirectX::SimpleMath::Matrix m_proj;
};


#endif	// GAME
