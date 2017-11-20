#pragma once
#include <vector>
#include "Obj3d\Obj3d.h"


class Floor
{
private:
	// マップコンテナ
	int m_map[10][10];
	// 床オブジェクトのコンテナ
	std::vector<std::unique_ptr<Obj3d>> m_floorPanels;

public:
	void SetMap(int map[][10]);


	void Init();
	void Update();
	void Draw();


};