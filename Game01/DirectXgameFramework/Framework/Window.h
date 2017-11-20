#pragma once
#ifndef  WINDOW_IMPL
#define  WINDOW_IMPL

#include <windows.h>
#include <mouse.h>
#include <keyboard.h>

#include "Game.h"

class Window {
public:
	// Constructor
	Window(HINSTANCE hInstance, int nCmdShow) : hInstance(hInstance), nCmdShow(nCmdShow) {
	}
	// クラスを登録しウィンドウを生成する Register class and create window
	int Initialize(int width, int height) {
		// クラスを登録する Register class
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, L"IDI_ICON");
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = L"DirectXgameFrameworkWindowClass";
		wcex.hIconSm = LoadIcon(wcex.hInstance, L"IDI_ICON");
		// クラスを登録する
		if (!RegisterClassEx(&wcex))
			return 1;

		// ウィンドウを生成する Create window
		RECT rc;
		rc.top = 0;
		rc.left = 0;
		rc.right = static_cast<LONG>(width);
		rc.bottom = static_cast<LONG>(height);

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		// ウィンドウを生成する Create window
		HWND hWnd = CreateWindowEx(0, L"DirectXgameFrameworkWindowClass", L"Roll Playing Game", WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

		// TODO: CreateWindowEx(WS_EX_TOPMOST, L"DirectXgameFrameworkWindowClass", L"DirectXgameFramework", WS_POPUP,...)
		// にして規定でフルスクリーンに変更する
		// Change to CreateWindowEx(WS_EX_TOPMOST, L"DirectXgameFrameworkWindowClass", L"DirectXgameFramework", WS_POPUP,
		// to default to fullscreen.

		if (!hWnd)
			return 1;

		ShowWindow(hWnd, nCmdShow);
		// TODO: nCmdShowにSW_SHOWMAXIMIZEDをセットして規定でフルスクリーンに変更する
		// Change nCmdShow to SW_SHOWMAXIMIZED to default to fullscreen.
		// SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(g_game.get()));

		// GetClientRect(hwnd, &rc);
		// Initialize window
		// g_game->Initialize(hwnd, rc.right - rc.left, rc.bottom - rc.top);
		this->hWnd = hWnd;
		return 0;
	}

	HWND HWnd() { return this->hWnd; }
	// ウィンドウプロシージャ
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND hWnd;
	HINSTANCE hInstance;
	int nCmdShow;
};

#endif	// WINDOW_IMPL
