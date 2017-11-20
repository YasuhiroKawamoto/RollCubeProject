#pragma once
#include <vector>
#include "Obj3d\Obj3d.h"


class Floor
{
private:
	// �}�b�v�R���e�i
	int m_map[10][10];
	// ���I�u�W�F�N�g�̃R���e�i
	std::vector<std::unique_ptr<Obj3d>> m_floorPanels;

public:
	void SetMap(int map[][10]);


	void Init();
	void Update();
	void Draw();


};