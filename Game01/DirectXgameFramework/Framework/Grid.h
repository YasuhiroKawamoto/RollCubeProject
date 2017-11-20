
#ifndef GRID
#define GRID

#include <Windows.h>

#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <d3d11.h>
#include <SimpleMath.h>
#include <wrl.h>
#include <CommonStates.h>
#include <algorithm>
#include <DirectXColors.h>

using namespace Microsoft;
using namespace Microsoft::WRL;
using namespace DirectX;
using namespace std;

class Grid
{
	// [ADD]
	ComPtr<ID3D11Device> m_d3dDevice;
	// [ADD]
	ComPtr<ID3D11DeviceContext>	m_d3dContext;
	// [ADD]
	unique_ptr<CommonStates> m_commonStates;

	// エフェクト
	unique_ptr<BasicEffect>	m_basicEffect;

	// プリミティブバッチ
	unique_ptr<PrimitiveBatch<VertexPositionColor>> m_primitiveBatch;

	// インプットレイアウト
	ID3D11InputLayout* m_pInputLayout;

	// グリッド描画エリアの幅,高さ,格子のサイズ
	int m_width, m_height, m_size;

	// オフセット
	int m_offsetX, m_offsetY;

public:
	// コンストラクタ
	Grid(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, int width, int height, int size);

	// デストラクタ
	~Grid();

	// 描画
	void Render();

	// グリッドのサイズを設定する
	void SetGripInfo(int width, int height, int size) {
		this->m_width = width;
		this->m_height = height;
		this->m_size = size;
	}

	// オフセットを設定する
	void SetOffset(int offsetX, int offsetY) {
		this->m_offsetX = offsetX;
		this->m_offsetY = offsetY;
	}
};


//　グリッド状の床描画クラス
class GridFloor
{
private:
	// [ADD]
	Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	// [ADD]
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;
	// [ADD]
	std::unique_ptr<DirectX::CommonStates> m_commonStates;
	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
	// インプットレイアウト
	ID3D11InputLayout* m_pInputLayout;

	// 床の一辺のサイズ
	float m_size;

	// 分割数
	int m_divides;

public:
	// コンストラクタ（床の一辺のサイズ、一辺の分割数）
	GridFloor(ComPtr<ID3D11Device> d3dDevice, ComPtr<ID3D11DeviceContext> d3dContext, float size, int divides);

	// デストラクタ
	~GridFloor();

	// 描画（ビュー行列、射影行列）
	void Render(SimpleMath::Matrix view, SimpleMath::Matrix proj, DirectX::GXMVECTOR color = DirectX::Colors::Gray);
};

#endif	// GRID
