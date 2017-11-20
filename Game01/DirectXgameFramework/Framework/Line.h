#ifndef LINE_BATCH
#define LINE_BATCH

#include <Windows.h>

#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <d3d11.h>
#include <SimpleMath.h>
#include <DirectXColors.h>
#include <wrl.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

// ラインクラス
class LineBatch
{
private:
	// [ADD]
	Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	// [ADD]
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;
	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// インプットレイアウト
	ID3D11InputLayout* m_pInputLayout;

	// 画面サイズ
	int m_width, m_height;

	// グリッドサイズ
	int m_size;

public:
	// コンストラクタ
	LineBatch(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, int width, int height, int size);

	// デストラクタ
	~LineBatch();

	// 描画開始
	void Begin();
	void Begin(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	// 描画終了
	void End();

	// 描画
	void Draw(float x1, float y1, float x2, float y2, DirectX::XMVECTOR color = DirectX::Colors::White);

	// 描画
	void Draw(DirectX::SimpleMath::Vector2 p1, DirectX::SimpleMath::Vector2 p2, DirectX::XMVECTOR color = DirectX::Colors::White);

	// 描画
	void DrawLine(DirectX::SimpleMath::Vector2 p1, DirectX::XMVECTOR color = DirectX::Colors::White);

	// 描画
	void DrawLine(DirectX::SimpleMath::Vector2 p1, DirectX::SimpleMath::Vector2 p2, DirectX::XMVECTOR color = DirectX::Colors::White);

	// 描画
	void Draw(DirectX::SimpleMath::Vector3 p, DirectX::XMVECTOR color = DirectX::Colors::White);

	// 描画
	void Draw(DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 p3, DirectX::XMVECTOR color = DirectX::Colors::White);
};

#endif	// LINE_BATCH
