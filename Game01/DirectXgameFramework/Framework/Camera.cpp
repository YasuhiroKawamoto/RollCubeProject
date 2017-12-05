#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


Camera::Camera()
	:Camera(800, 600, Vector3(0,0,15), Vector3::Zero)
{
}

Camera::Camera(int width, int height, const Vector3& eye, const Vector3& target)
{
	//メンバ変数の初期化

	// 視点
	m_eyePos = eye;
	// 注視点
	m_targetPos = target;
	// 上方向ベクトル
	m_upVec = Vector3(0.0f, 1.0f, 0.0f);

	// 垂直方向視野角
	m_fovY = XMConvertToRadians(60.0f);

	// アスペクト比(横×縦の画面比率)
	m_aspect = (float)width / height;

	// ニアクリップ
	m_nearClip = 0.1f;

	// ファークリップ
	m_farClip = 1000.0f;

	// ビュー行列生成
	m_view = Matrix::CreateLookAt(m_eyePos, m_targetPos, m_upVec);
	// プロジェクション行列生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

void Camera::Update()
{
	// ビュー行列生成
	m_view = Matrix::CreateLookAt(m_eyePos, m_targetPos, m_upVec);

	// プロジェクション行列生成 
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);

	// ビルボード行列を計算
	CalcBillboard();
}

const DirectX::SimpleMath::Matrix& Camera::GetView()
{
	return m_view;
}

const DirectX::SimpleMath::Matrix& Camera::GetProj()
{
	return m_proj;
}

// ビルボードの計算
void Camera::CalcBillboard()
{
	// 視線方向
	Vector3 eyeDir = m_eyePos - m_targetPos;
	// Y軸
	Vector3 Y = Vector3::UnitY;
	// X軸
	Vector3 X = Y.Cross(eyeDir);
	X.Normalize();
	// Z軸
	Vector3 Z = X.Cross(Y);
	Z.Normalize();
	// Y軸周りビルボード行列（右手系の為Z方向反転）
	m_BillboardConstrainY = Matrix::Identity;
	m_BillboardConstrainY.m[0][0] = X.x;
	m_BillboardConstrainY.m[0][1] = X.y;
	m_BillboardConstrainY.m[0][2] = X.z;
	m_BillboardConstrainY.m[1][0] = Y.x;
	m_BillboardConstrainY.m[1][1] = Y.y;
	m_BillboardConstrainY.m[1][2] = Y.z;
	m_BillboardConstrainY.m[2][0] = -Z.x;
	m_BillboardConstrainY.m[2][1] = -Z.y;
	m_BillboardConstrainY.m[2][2] = -Z.z;

	Y = eyeDir.Cross(X);
	Y.Normalize();
	eyeDir.Normalize();
	// ビルボード行列（右手系の為Z方向反転）
	m_Billboard = Matrix::Identity;
	m_Billboard.m[0][0] = X.x;
	m_Billboard.m[0][1] = X.y;
	m_Billboard.m[0][2] = X.z;
	m_Billboard.m[1][0] = Y.x;
	m_Billboard.m[1][1] = Y.y;
	m_Billboard.m[1][2] = Y.z;
	m_Billboard.m[2][0] = -eyeDir.x;
	m_Billboard.m[2][1] = -eyeDir.y;
	m_Billboard.m[2][2] = -eyeDir.z;
}