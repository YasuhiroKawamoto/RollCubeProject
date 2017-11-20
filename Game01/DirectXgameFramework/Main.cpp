// DirectX Game Framework 0.9 
// 2017/05/05　Added Japanese comment
// 2017/05/08  Added Graphics singleton class
// 2017/05/13  Added Window class
// 2017/05/20  Functioning WinMain function

#include "pch.h"
#include "MyGame.h"
#include "Framework\Window.h"

using namespace DirectX;
using namespace std;

unique_ptr<Game> g_game;
unique_ptr<Window> g_window;


// エントリポイント Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (!XMVerifyCPUSupport())
        return 1;
	// COMライブラリを初期化する
    HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
    if (FAILED(hr))
        return 1;

	int width = 640;
	int height = 480;

	// Gameオブジェクトを生成する
	g_game = std::make_unique<MyGame>(width, height);
	//// Windowオブジェクトを生成する
	//g_window = std::make_unique<Window>(hInstance, nCmdShow);
	//// Windowオブジェクトを初期化する
	//g_window->Initialize(width, height);
	// Gameオブジェクトを初期化する
	g_game->Initialize();

	

	// ゲームを更新する
	MSG msg = g_game->Update();

	//// Windowオブジェクトを破棄する
	//g_window.reset();
    // Gameオブジェクトを破棄する
	g_game.reset();

    CoUninitialize();
    return (int) msg.wParam;
}


