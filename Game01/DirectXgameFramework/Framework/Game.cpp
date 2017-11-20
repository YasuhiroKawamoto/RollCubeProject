//
// Game.cpp
//

#include "../pch.h"
#include "Game.h"

void ExitGame();

using namespace DirectX;
using namespace DX;
using Microsoft::WRL::ComPtr;


// コンストラクタ Constructor
Game::Game(int width, int height)
	: 
	hWnd(0), width(width), height(height), featureLevel(D3D_FEATURE_LEVEL_9_1) 
{
	// スタートアップ情報
	STARTUPINFO si{};
	// インスタンスハンドルを取得する
	this->hInstance = ::GetModuleHandle(NULL);

	::GetStartupInfo(&si);
	this->nCmdShow = si.dwFlags & STARTF_USESHOWWINDOW ? si.wShowWindow : SW_SHOWDEFAULT;
	// windowオブジェクトを生成
	this->window = make_unique<Window>(this->hInstance, this->nCmdShow);
}

// 実行に必要となるDirect3Dリソースを初期化する
// Initialize the Direct3D resources required to run.
void Game::Initialize()
{
	// Windowオブジェクトを初期化する
	this->window->Initialize(this->width, this->height);

	// Windowオブジェクトの生成後にウィンドウハンドルを取得する
	this->hWnd = this->window->HWnd();
	
	// シングルトンのインスタンスを取得
	auto& graphics = Graphics::Get();

	graphics.HWnd(this->hWnd);
	graphics.Width(this->width);
	graphics.Height(this->height);

	// デバイスを生成する Create Device
	graphics.CreateDevice();
	// リソースを生成する Create Resources
	graphics.CreateResources();

    // TODO: デフォルト変数timestepモード以外のものが必要な場合タイマー設定を変更する
	// 例えば 60 FPS固定タイムステップ更新ロジックに対しては以下を呼び出す
	// Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    
    // this->timer.SetFixedTimeStep(true);
    // this->timer.SetTargetElapsedSeconds(1.0 / 60);


	// SpriteBatchオブジェクトを生成する Create SpriteBatch object
	this->spriteBatch = std::make_unique<SpriteBatch>(graphics.Context().Get());
	// GridFloorオブジェクトを生成する Create GridFloor object
	this->gridFloor = std::make_unique<GridFloor>(graphics.Device(), graphics.Context(), 20.0f, 20);
	// Fontオブジェクトを生成する Create Font object
	this->font = std::make_unique<SpriteFont>(graphics.Device().Get(), L"Font/myfile.spritefont");
	// Effectオブジェクトを生成する
	this->m_effect = std::make_unique<BasicEffect>(graphics.Device().Get());

	//エフェクトの設定
	m_effect->SetProjection(XMMatrixOrthographicOffCenterRH(0,
		width, height, 0, 0, 1));
	m_effect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);


	graphics.Device()->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.GetAddressOf());

	// CommonStatesを生成する Create CommonState object
	this->commonStates = std::make_unique<CommonStates>(graphics.Device().Get());


	// EffectFactoryオブジェクトを生成する
	this->fxFactory = std::make_unique<EffectFactory>(graphics.Device().Get());

	// 
}

// 終了処理をおこなう
void Game::Finalize() {
	// SpriteBatchオブジェクトを破棄する
	this->spriteBatch.reset();
	// Fontオブジェクトを破棄する
	this->font.reset();
	// コモンステートを破棄する
	this->commonStates.reset();
	// Graphicsオブジェクトを破棄する
	Graphics::Dispose();
	// Windowオブジェクトを破棄する
	this->window.reset();
}

// 基本ゲームループを実行する Executes the basic game loop.
MSG Game::Update() {
	// メインメッセージループ Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// ゲームを更新する Update game
			this->timer.Tick([&]() { Update(this->timer); });
			// シーンを描画する Draw scene
			this->timer.Tick([&]() { Render(this->timer); });
		}
	}
	return msg;
}

// ワールドを更新する Updates the world
void Game::Update(StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: ゲームロジックを追加する Add your game logic here
	
}

// シーンを描画する Draws the scene
void Game::Render(StepTimer const & timer)
{
    
}

// FPSを描画する Draw FPS
void Game::DrawFPS() {
	// FPS文字列を生成する Create FPS string
	wstring fpsString = L"fps = " + std::to_wstring((unsigned int)this->timer.GetFramesPerSecond());
	// FPSを描画する Draw FPS
	this->font->DrawString(spriteBatch.get(), fpsString.c_str(), SimpleMath::Vector2(0, 0), Colors::White);
}

// バックバッファをクリアするためのヘルパー関数 Helper method to clear the back buffers
void Game::Clear()
{
    // Graphicsクラスのインスタンスを取得する
	auto& graphics = Graphics::Get();
	// レンダーターゲットをクリアする Clear Render target view
	graphics.Context()->ClearRenderTargetView(graphics.RenderTargetView().Get(), Colors::Black);
	// デプスステンシルビューを設定する Set depth stencil view
	graphics.Context()->ClearDepthStencilView(graphics.DepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	// レンダータッゲートを設定する Set render target
	graphics.Context()->OMSetRenderTargets(1, graphics.RenderTargetView().GetAddressOf(), graphics.DepthStencilView().Get());
    // ビューポートを設定する Set viewport
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(this->width), static_cast<float>(this->height));
	graphics.Context()->RSSetViewports(1, &viewport);
}

// バックバッファの内容をスクリーンに送る Presents the back buffer contents to the screen
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.

	// Graphicsクラスのインスタンスを取得する
	auto& graphics = Graphics::Get();
	HRESULT hr = graphics.SwapChain()->Present(1, 0);

    // デバイスがリセットされた場合レンダラを再初期化する必要がある 
	// If the device was reset we must completely reinitialize the renderer
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
		graphics.OnDeviceLost();
    }
    else {
        ThrowIfFailed(hr);
    }
}

// メッセージハンドラ Message handlers
void Game::OnActivated()
{
    // TODO: ゲームがアクティブなウィンドウになる Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: ゲームがバックグラウンドウィンドウになる Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: ゲームがパワーサスペンデッドになる Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
	this->timer.ResetElapsedTime();

    // TODO: ゲームがパワーレジュームになる Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    this->width = std::max(width, 1);
    this->height = std::max(height, 1);
	
	Graphics::Get().CreateResources();
    // TODO: ゲームウィンドウのサイズが再変更される Game window is being resized.
}

// プロパティ Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: 任意のデフォルトウィンドウサイズに変更する(最小サイズは320x200) 
	// Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}

// Exitヘルパー関数 Exit helper
void ExitGame() {
	PostQuitMessage(0);
}
