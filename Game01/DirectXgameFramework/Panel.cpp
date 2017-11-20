#include "pch.h"
#include <sstream>

#include "DebugManager.h"
#include "Panel.h"
#include "YasuLib\Utility\Utility.h"
#include "AttackCommand.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace utl;

Panel::Panel()
{
	
}

Panel::~Panel()
{
}

void Panel::Load(wstring fileName)
{
	m_model = make_unique<Obj3d>();
	m_model->LoadModel(fileName);
}

void Panel::Initialze(Obj3d* parent) 
{
	m_model->SetParent(parent);
	m_model->SetTranslation(Vector3(0.0f, 0.5f, 0.0f));
	m_normalVec = Vector3(0.0f, 1.0f, 0.0f);

	m_command = std::make_unique<AttackCommand>();

	m_state = State::DEFAULT;
}

void Panel::Update()
{
	// 更新
	m_model->Update();


	std::wstringstream ss;
	ss << "PanelVecX" << m_normalVec.x
		<< "PanelVecY" << m_normalVec.y
		<< "PanelVecZ" << m_normalVec.z;

	DebugManager::GetInstance()->Add("PanelVec", DirectX::SimpleMath::Vector2(0, 40), ss);


	// コマンド処理
	m_state = State::DEFAULT;
	if (m_normalVec == Vector3(0, -1.000000f, 0.0f))
	{
		m_state = m_state | State::ATTACK;
		m_command->Action();
	}
}

void Panel::Draw()
{
	m_model->Draw();
}

Vector3 Panel::CalcDirection(const Matrix& rotMat)
{
	Vector3::TransformNormal(m_normalVec, rotMat, m_normalVec);

	m_normalVec.x = Utility::Roundf(m_normalVec.x, 1);
	m_normalVec.y = Utility::Roundf(m_normalVec.y, 1);
	m_normalVec.z = Utility::Roundf(m_normalVec.z, 1);

	return  m_normalVec;
}
