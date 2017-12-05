//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @File  MyGame.h
//!
//! @Brief  MyGameクラス(Gameを継承)のヘッダファイル
//!
//! @Date   2017/08/08
//!
//! @Author Y.Kawamoto
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once
#include <vector>

#include "Framework\Game.h"
#include "Obj3d\Obj3d.h"
#include "Player.h"
#include "Floor.h"
#include "Enemy.h"
#include "TimeManager.h"

class MyGame : public Game
{
private:
	// カメラ
	std::unique_ptr<Camera> m_camera;

	
	std::unique_ptr<Player> m_player;	// プレイヤー

	std::vector<Enemy*> m_enemy;		// エネミー


	std::unique_ptr<Floor> m_floor;

	TimeManager* m_timeMan;
	
public:
	// コンストラクタ 
	MyGame(int width, int height);
	// ゲームを更新する 
	void Update(DX::StepTimer const& timer) override;
	// シーンを描画する 
	void Render(DX::StepTimer const & timer) override;
	// 初期化
	void Initialize() override;
	// 終了処理
	void Finalize() override;
};