#include "pch.h"
#include "Floor.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

void Floor::SetMap(int map[][10])
{
		for (int i = 0; i<10; i++)
		{
			for (int j = 0; j<10; j++)
			{
				m_map[i][j] = map[i][j];
			}
		}
}

void Floor::Init()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (m_map[i][j] == 1)
			{
				auto& floor = make_unique<Obj3d>();
				floor->SetTranslation(Vector3(j - 5, -1.0f, i - 5));
				floor->LoadModel(L"Resources/Box2.cmo");

				m_floorPanels.push_back(move(floor));
			}
		}
	}
}

void Floor::Update()
{
	for (auto& obj : m_floorPanels)
	{
		obj->Update();
	}
}

void Floor::Draw()
{
	for (auto& obj: m_floorPanels)
	{
		obj->Draw();
	}
}



