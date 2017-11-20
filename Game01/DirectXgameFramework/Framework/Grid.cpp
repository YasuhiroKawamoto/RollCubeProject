
#include "Grid.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// コンストラクタ
Grid::Grid(ComPtr<ID3D11Device> d3dDevice, ComPtr<ID3D11DeviceContext> d3dContext,int width, int height, int size)
	: m_d3dDevice(d3dDevice), 
	m_d3dContext(d3dContext),
	m_pInputLayout(nullptr), 
	m_width(width), 
	m_height(height), 
	m_size(size), 
	m_offsetX(0), 
	m_offsetY(0)
{

	// [MODIFY]エフェクトオブジェクトを生成する
	this->m_basicEffect = make_unique<BasicEffect>(this->m_d3dDevice.Get());
	// 頂点カラーを有効にする
	this->m_basicEffect->SetVertexColorEnabled(true);
	// [MODIFY]プリミティブオブジェクトを生成する
	this->m_primitiveBatch = make_unique<PrimitiveBatch<VertexPositionColor>>(this->m_d3dContext.Get());
	// [ADD] コモンステートを生成する
	this->m_commonStates = make_unique<CommonStates>(this->m_d3dDevice.Get());

	// インプットレイアウトを生成する
	void const* shaderByteCode;
	size_t byteCodeLength;
	this->m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	this->m_d3dDevice.Get()->CreateInputLayout(VertexPositionColor::InputElements,
										   VertexPositionColor::InputElementCount,
										   shaderByteCode, byteCodeLength,
										   &this->m_pInputLayout);
}

// デストラクタ
Grid::~Grid()
{
	// 入力レイアウトを解放する
	if (this->m_pInputLayout) 
		this->m_pInputLayout->Release();
}

void Grid::Render()
{
	Matrix world, view, proj;

	// 2D用行列を作成してエフェクトへセット
	world = Matrix::Identity;
	view = Matrix::Identity;
	proj = Matrix::CreateTranslation(0.5f, 0.5f, 0.0f) * Matrix::CreateOrthographicOffCenter(0.0f, (float)this->m_width, (float)this->m_height, 0.0f, 0.0f, 100.0f);
	this->m_basicEffect->SetWorld(world);
	this->m_basicEffect->SetView(view);
	this->m_basicEffect->SetProjection(proj);

	this->m_basicEffect->Apply(m_d3dContext.Get());
	this->m_d3dContext.Get()->IASetInputLayout(this->m_pInputLayout);

	this->m_primitiveBatch->Begin();

	// 縦線を描画
	for (int i=0; i < m_width/m_size+1; i++) {
		VertexPositionColor v1(Vector3(static_cast<float>(this->m_size * i) + this->m_offsetX, 0.0f, 0.0f), Colors::DarkGreen);
		VertexPositionColor v2(Vector3(static_cast<float>(this->m_size * i) + this->m_offsetX, static_cast<float>(this->m_height), 0.0f), Colors::DarkGreen);
		m_primitiveBatch->DrawLine(v1, v2);
	}
	// 横線を描画
	for (int i=0; i < m_height/m_size+1; i++) {
		VertexPositionColor v1(Vector3(0.0f, static_cast<float>(this->m_size * i) + this->m_offsetY, 0.0f), Colors::DarkGreen);
		VertexPositionColor v2(Vector3(static_cast<float>(this->m_width), static_cast<float>(this->m_size * i) + this->m_offsetY, 0.0f), Colors::DarkGreen);
		this->m_primitiveBatch->DrawLine(v1, v2);
	}
	this->m_primitiveBatch->End();
}


GridFloor::GridFloor(ComPtr<ID3D11Device> d3dDevice, ComPtr<ID3D11DeviceContext> d3dContext, float size, int divides) : m_d3dDevice(d3dDevice), m_d3dContext(d3dContext), m_pInputLayout(nullptr), m_size(size), m_divides(divides)
{
	// エフェクトオブジェクトを生成する
	this->m_basicEffect = make_unique<BasicEffect>(this->m_d3dDevice.Get());
	// 頂点カラーを有効にする
	this->m_basicEffect->SetVertexColorEnabled(true);

	// プリミティブオブジェクトを生成する
	this->m_primitiveBatch = make_unique<PrimitiveBatch<VertexPositionColor>>(this->m_d3dContext.Get());
	// [ADD] コモンステートを生成する
	this->m_commonStates = make_unique<CommonStates>(m_d3dDevice.Get());

	// インプットレイアウト生成
	void const* shaderByteCode;
	size_t byteCodeLength;
	this->m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	this->m_d3dDevice.Get()->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		&this->m_pInputLayout);
}

GridFloor::~GridFloor()
{
	// 入力レイアウトを解放する
	if (this->m_pInputLayout != nullptr) 
		this->m_pInputLayout->Release();
}

void GridFloor::Render(Matrix view, Matrix proj, GXMVECTOR color)
{
	Matrix world = Matrix::Identity;

	this->m_d3dContext->OMSetDepthStencilState(this->m_commonStates->DepthDefault(), 0);

	this->m_basicEffect->SetWorld(world);
	this->m_basicEffect->SetView(view);
	this->m_basicEffect->SetProjection(proj);

	this->m_basicEffect->Apply(m_d3dContext.Get());
	this->m_d3dContext.Get()->IASetInputLayout(this->m_pInputLayout);

	this->m_primitiveBatch->Begin();

	const XMVECTORF32 xAxis = { m_size, 0.f, 0.f };
	const XMVECTORF32 yAxis = { 0.f, 0.f, m_size };

	size_t divides = std::max<size_t>(1, m_divides);
	FXMVECTOR origin = g_XMZero;
	for (size_t i=0; i<= divides; ++i){
		float fPercent = float(i) / float(divides);
		fPercent = (fPercent * 1.0f) - 0.5f;
		XMVECTOR vScale = XMVectorScale(xAxis, fPercent);
		vScale = XMVectorAdd(vScale, origin);

		VertexPositionColor v1(XMVectorSubtract(vScale, yAxis * 0.5f), color);
		VertexPositionColor v2(XMVectorAdd(vScale, yAxis * 0.5f), color);
		this->m_primitiveBatch->DrawLine(v1, v2);
	}

	for (size_t i=0; i<=divides; i++) {
		FLOAT fPercent = float(i) / float(divides);
		fPercent = (fPercent * 1.0f) - 0.5f;
		XMVECTOR vScale = XMVectorScale(yAxis, fPercent);
		vScale = XMVectorAdd(vScale, origin);

		VertexPositionColor v1(XMVectorSubtract(vScale, xAxis * 0.5f), color);
		VertexPositionColor v2(XMVectorAdd(vScale, xAxis * 0.5f), color);
		this->m_primitiveBatch->DrawLine(v1, v2);
	}

	this->m_primitiveBatch->End();
}

