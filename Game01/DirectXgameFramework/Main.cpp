// DirectX Game Framework 0.9 
// 2017/05/05�@Added Japanese comment
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


// �G���g���|�C���g Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (!XMVerifyCPUSupport())
        return 1;
	// COM���C�u����������������
    HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
    if (FAILED(hr))
        return 1;

	int width = 640;
	int height = 480;

	// Game�I�u�W�F�N�g�𐶐�����
	g_game = std::make_unique<MyGame>(width, height);
	//// Window�I�u�W�F�N�g�𐶐�����
	//g_window = std::make_unique<Window>(hInstance, nCmdShow);
	//// Window�I�u�W�F�N�g������������
	//g_window->Initialize(width, height);
	// Game�I�u�W�F�N�g������������
	g_game->Initialize();

	

	// �Q�[�����X�V����
	MSG msg = g_game->Update();

	//// Window�I�u�W�F�N�g��j������
	//g_window.reset();
    // Game�I�u�W�F�N�g��j������
	g_game.reset();

    CoUninitialize();
    return (int) msg.wParam;
}


