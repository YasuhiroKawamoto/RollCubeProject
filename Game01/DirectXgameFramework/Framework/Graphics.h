#pragma once
#ifndef GRAPHICS
#define GRAPHICS

#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>
#include <SimpleMath.h>
#include <wrl.h>

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

// Uncopyableクラス
class Uncopyable {
protected:
	Uncopyable() = default;
	~Uncopyable() = default;
private:
	Uncopyable(const Uncopyable&) = delete;
	Uncopyable& operator =(const Uncopyable&) = delete;
};

// Graphicsクラス
class Graphics : private Uncopyable {
private:
	// コンストラクタ Constructor
	Graphics() {}

public:
	// Graphicsクラスのインスタンスを取得する Get instance of Graphics class
	static Graphics& Get() {
		if (graphics.get() == nullptr) {
			graphics.reset(new Graphics());
		}
		return *graphics.get();
	}
	// ウィンドウハンドルを取得する Get hWnd
	HWND HWnd() {
		return hWnd;
	}
	// ウィンドウハンドルを設定する Set hWnd
	void HWnd(HWND hWnd) {
		this->hWnd = hWnd;
	}
	// ウィンドウ幅を取得する Get width
	int Width() {
		return width;
	}
	// ウィンドウ幅を設定する Set width
	void Width(int width) {
		this->width = width;
	}
	// ウィンドウ高を取得する Get height
	int Height() {
		return height;
	}
	// ウィンドウ高を設定する Set height
	void Height(int height) {
		this->height = height;
	}
	// デバイスを取得する Get device object
	ComPtr<ID3D11Device> Device() { 
		return this->device; 
	}
	// デバイスを設定する Set device object
	void Device(ComPtr<ID3D11Device> device) {
		this->device = device;
	}
	// デバイスコンテキストを取得する Get device context object
	ComPtr<ID3D11DeviceContext> Context() {
		return this->context;
	}
	// デバイスコンテキストを設定する Set device context object
	void Context(ComPtr<ID3D11DeviceContext> context) {
		this->context = context;
	}

	// スワップチェインを取得する Get SwapChain
	ComPtr<IDXGISwapChain> SwapChain() {
		return swapChain;
	}
	// スワップチェインを設定する Set SwapChain
	void SwapChain(ComPtr<IDXGISwapChain> swapChain) {
		this->swapChain = swapChain;
	}
	// レンダーターゲットビューを取得するGet RenderTargetView
	ComPtr<ID3D11RenderTargetView> RenderTargetView() {
		return renderTargetView;
	}
	// レンダーターゲットビューを設定する Set RenderTargetView
	void RenderTargetView(ComPtr<ID3D11RenderTargetView> renderTargetView) {
		this->renderTargetView = renderTargetView;
	}

	// デプスステンシルビューを取得する Get DepthStencilView
	ComPtr<ID3D11DepthStencilView> DepthStencilView() {
		return depthStencilView;
	}
	// デプスステンシルビューを設定する Set DepthStencilView
	void DepthStencilView(ComPtr<ID3D11DepthStencilView> depthStencilView) {
		this->depthStencilView = depthStencilView;
	}

	// デバイスを生成する Create device
	void CreateDevice();

	// リソースを生成する Create Resource
	void CreateResources();

	// デバイスロストが発生した場合 OnDeviceLost
	void OnDeviceLost();
	
	// Throw exception of error
	void ThrowIfFailed(HRESULT hr) {
		if (FAILED(hr)) {
			// Set a breakpoint on this line to catch DirectX API errors
			throw std::exception();
		}
	}
	// Graphicsオブジェクトを破棄する Dispose Graphics object
	static void Dispose() {
		graphics.reset();
	}

private:
	static std::unique_ptr<Graphics> graphics;

	HWND hWnd;
	int  width;
	int  height;
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11Device1> device1;
	ComPtr<ID3D11DeviceContext>	context;
	ComPtr<ID3D11DeviceContext1> context1;
	D3D_FEATURE_LEVEL  featureLevel;

	ComPtr<IDXGISwapChain> swapChain;
	ComPtr<IDXGISwapChain1> swapChain1;
	ComPtr<ID3D11RenderTargetView> renderTargetView;
	ComPtr<ID3D11DepthStencilView> depthStencilView;
};

#endif	// GRAPHICS

