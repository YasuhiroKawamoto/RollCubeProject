// デバッグ用カメラクラス
#ifndef DEBUG_CAMERA
#define DEBUG_CAMERA

#include <d3d11.h>
#include <SimpleMath.h>
#include <Mouse.h>

#include "Camera.h"

// デバッグ用カメラクラス
class DebugCamera : public Camera
{
private:
	// カメラの距離
	static const float DEFAULT_CAMERA_DISTANCE;

	// マウスステート
	DirectX::Mouse::State m_mouseState;
	// マウス
	std::unique_ptr<DirectX::Mouse> m_mouse;
	// ボタンステートトラッカー
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseTracker;

	// 横回転
	float m_yAngle, m_yTmp;
	// 縦回転
	float m_xAngle, m_xTmp;

	// ドラッグされた座標
	int m_x, m_y;
	float m_sx, m_sy;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// スクロールホイール値
	int m_scrollWheelValue;

private:

	void Motion(int x, int y);

public:
	// コンストラクタ
	DebugCamera(int width, int height);

	// 更新する
	void Update();
	// カメラ行列を生成する
	DirectX::SimpleMath::Matrix GetCameraMatrix() {
		return m_view;
	}
};

#endif	// DEBUG_CAMERA
