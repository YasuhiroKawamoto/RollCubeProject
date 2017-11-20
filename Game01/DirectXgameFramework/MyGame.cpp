//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @File  MyGame.cpp
//!
//! @Brief  MyGameクラスのソースファイル
//!
//! @Date   2017/07/13
//!
//! @Author Y.Kawamot
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


#include "MyGame.h"
#include "YasuLib\Manager\InputManager.h"
#include "YasuLib\Manager\TextureManager.h"
#include "DebugManager.h"
#include "BattleManager.h"
#include "TimeManager.h"
#include <sstream>

using namespace DX;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;


// コンストラクタ
MyGame::MyGame(int width, int height)
	// 基底コンストラクタ呼び出し
	:Game(width, height)
{
}

void MyGame::Initialize()
{
	//　基底クラスの初期化
	Game::Initialize();


	// ＝＝＝初期化をここに追加
	auto& graphics = Graphics::Get();

	// カメラ作成＆初期化
	m_camera = make_unique<Camera>(this->width, this->height, Vector3(0, 6, 8), Vector3(0, 0, 0));

	Obj3d::InitializeStatic(m_camera.get());

	// プレイヤー初期化
	m_player = make_unique<Player>();

	// エネミー初期化
	for (int i = 0; i < 1; i++)
	{
		Enemy* enm = new Enemy();
		enm->Load(L"Resources/Enemy01.cmo");
		enm->Init(Vector3(2+i-3, 0, 0));
		m_enemy.push_back(enm);
	}

	m_player->Init();

	m_floor = make_unique<Floor>();

	int map[10][10]
	{
		{ 0,1,1,1,1,1,0,0,1,1 },
		{ 0,0,0,1,1,0,1,0,0,1 },
		{ 0,0,0,1,1,1,1,0,0,0 },
		{ 1,0,0,1,1,1,1,1,0,1 },
		{ 1,0,0,1,1,1,0,0,0,0 },
		{ 1,1,1,1,1,1,1,0,1,1 },
		{ 1,1,1,1,0,1,1,1,1,0 },
		{ 1,0,0,0,0,0,1,1,0,1 },
		{ 1,1,0,0,0,1,1,0,0,1 },
		{ 1,1,0,1,1,1,0,0,0,0 },
	};


	m_floor->SetMap(map);
	m_floor->Init();

	m_player->SetMap(map);

	for (auto enemy : m_enemy)
	{
		enemy->Update();
	}

	BattleManager::GetInstance()->SetPlayer(m_player.get());

	BattleManager::GetInstance()->SetEnemies(m_enemy);
	m_timeMan = TimeManager::GetInstance();

}

void MyGame::Update(StepTimer const & timer)
{
	// ＝＝＝ゲームの更新処理をここに追加

	// 入力マネージャの更新
	InputManager::GetInstance()->Update();
	// デバッグマネージャの更新
	DebugManager::GetInstance()->Reset();

	m_timeMan->Update();

	m_camera->Update();

	m_floor->Update();
	m_player->Update();

	for (auto& enm : m_enemy)
	{
		enm->Update();
	}

	BattleManager::GetInstance()->Update();
}

void MyGame::Render(StepTimer const & timer)
{
	// 最初の更新の前は何も描画しないようにする
	// Don't try to render anything before the first Update.
	if (timer.GetFrameCount() == 0) {
		return;
	}

	Clear();

	// カリング設定?
	Graphics::Get().Context()->RSSetState(commonStates->CullNone());


	// ビュー行列とプロジェクション行列をセット
	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);

	m_effect->Apply(Graphics::Get().Context().Get());
	Graphics::Get().Context()->IASetInputLayout(m_inputLayout.Get());
	// ＝＝＝ゲームの描画処理をここに追加

	// プレイヤーの描画
	m_player->Draw();

	for (auto& enm : m_enemy)
	{
		enm->Draw();
	}

	// 床描画
	m_floor->Draw();

	// スプライト描画
	this->spriteBatch->Begin();
	
	// スプライトの描画をここに追加

	//デバッグ文字の描画
	DebugManager::GetInstance()->Draw(spriteBatch.get());
	
	this->spriteBatch->End();

	Present();
}

void MyGame::Finalize()
{
	// ＝＝＝終了処理をここに追加
	delete m_timeMan;
	
	// 基底クラスの終了処理
	Game::Finalize();
}
