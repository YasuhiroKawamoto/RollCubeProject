// デバッグ用カメラクラス
#include "DebugCamera.h"
#include "mouse.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float DebugCamera::DEFAULT_CAMERA_DISTANCE = 8.0f;


// コンストラクタ
DebugCamera::DebugCamera(int width, int height)
	: m_yAngle(0.0f), m_yTmp(0.0f), m_xAngle(0.0f), m_xTmp(0.0f), m_x(0), m_y(0), m_scrollWheelValue(0)
{
	// 画面サイズに対する相対的なスケールに調整する
	this->m_sx = 1.0f / (float)width;
	this->m_sy = 1.0f / (float)height;
	this->m_view = DirectX::SimpleMath::Matrix::Identity;

	// マウスを初期化する
	this->m_mouse = std::make_unique<Mouse>();
	this->m_mouseTracker = std::make_unique<Mouse::ButtonStateTracker>();
}

// 更新する
void DebugCamera::Update()
{
	// マウス情報を取得する
	this->m_mouseState = this->m_mouse->GetState();
	this->m_mouseTracker->Update(this->m_mouseState);

	// マウスの左ボタンが押された
	if (this->m_mouseTracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED) {
		// マウスの座標を取得する
		this->m_x = this->m_mouseState.x;
		this->m_y = this->m_mouseState.y;
	}
	// マウスの左ボタンが離された
	else if (this->m_mouseTracker->leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED) {
		// 現在の回転を保存する
		this->m_xAngle = this->m_xTmp;
		this->m_yAngle = this->m_yTmp;
	}
	// マウスのボタンが押されていたらカメラを移動させる
	if (this->m_mouseState.leftButton) {
		Motion(this->m_mouseState.x, this->m_mouseState.y);
	}

	// マウス ホイール値を取得する
	this->m_scrollWheelValue = this->m_mouseState.scrollWheelValue;
	if (this->m_scrollWheelValue > 0) {
		// スクロールホイール値を初期化する
		this->m_scrollWheelValue = 0;
		// マウスのスクロールホイール値をリセットする
		this->m_mouse->ResetScrollWheelValue();
	}

	// y軸を回転軸として頂点のセットを回転させるために使用できる行列を返す
	Matrix rotateY = Matrix::CreateRotationY(m_yTmp);
	// x軸を回転軸として頂点のセットを回転させるために使用できる行列を返す
	Matrix rotateX = Matrix::CreateRotationX(m_xTmp);

	Matrix rotate = rotateY * rotateX;

	Vector3 eye(0.0f, 0.0f, 1.0f);
	Vector3 target(0.0f, 0.0f, 0.0f);
	Vector3 up(0.0f, 1.0f, 0.0f);

	// 指定された行列を使用して3Dベクトルをトランスフォームする
	eye = Vector3::Transform(eye, rotate.Invert());

	eye = eye * (DEFAULT_CAMERA_DISTANCE - this->m_scrollWheelValue / 100);
	// 指定された行列を使用して 3D ベクトルをトランスフォームする
	up = Vector3::Transform(up, rotate.Invert());
	// ビュー行列を生成する
	this->m_view = Matrix::CreateLookAt(eye, target, up);
}

// 行列を生成する
void DebugCamera::Motion(int x, int y)
{
	// マウスポインタの位置のドラッグ開始位置からの変位 (相対値)
	float dx = (x - m_x) * this->m_sx;
	float dy = (y - m_y) * this->m_sy;

	if (dx != 0.0f || dy != 0.0f) {
		// Ｙ軸の回転
		float yAngle = dx * XM_PI;
		// Ｘ軸の回転
		float xAngle = dy * XM_PI;

		this->m_xTmp = this->m_xAngle + xAngle;
		this->m_yTmp = this->m_yAngle + yAngle;
	}
}
