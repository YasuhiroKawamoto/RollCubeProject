#include "CollisionNode.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


bool CollisionNode::m_debugVisible = false;

//=======================================================
// *******CollisionNodeクラスのメンバ関数******************
//=======================================================
void CollisionNode::SetParent(Obj3d* parent)
{
	m_obj.SetParent(parent);
}

//=======================================================
// **********SphereNodeクラスのメンバ関数*****************
//=======================================================

// コンストラクタ
SphereNode::SphereNode()
	:m_radius(1.0f)
{
}

void SphereNode::Initialize()
{
	// デバッグ表示用モデルのの読み込み
	m_obj.LoadModel(L"Resources\\SphereNode.cmo");
}

void SphereNode::Update()
{
	m_obj.SetTranslation(m_trans);
	m_obj.SetScale(Vector3(m_radius));
	m_obj.Update();

	{// 判定球の要素を計算
		const Matrix& worldm = m_obj.GetWorldMatrix();

		// モデルでの中心点座標
		Vector3 center(0, 0, 0);
		// モデルでの右端座標
		Vector3 right(1, 0, 0);


		// ワールド座標系に変換
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		// 判定級の要素を代入
		Sphere::Center = center;
		Sphere::radius = Vector3::Distance(center, right);

	
	
	}
}

void SphereNode::Drwa()
{
	m_obj.Draw();
}


