
#include "Line.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

LineBatch::LineBatch(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext,int width, int height, int size) : m_width(width), m_height(height), m_size(size)
{
	// エフェクトオブジェクトを生成する
	this->m_basicEffect = std::make_unique<BasicEffect>(m_d3dDevice.Get());
	// 頂点カラー(有効)
	this->m_basicEffect->SetVertexColorEnabled(true);
	// プリミティブオブジェクト生成
	this->m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(this->m_d3dContext.Get());

	// インプットレイアウトを生成する
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	m_d3dDevice.Get()->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		&m_pInputLayout);
}

LineBatch::~LineBatch()
{
	// 入力レイアウトを解放する
	if (this->m_pInputLayout) 
		this->m_pInputLayout->Release();
}

void LineBatch::Begin()
{
	Matrix world, view, projection;

	// 2D用行列を作成してエフェクトへセット
	world = Matrix::Identity;
	view = Matrix::Identity;
	projection = Matrix::CreateTranslation(0.5f, 0.5f, 0.0f) * Matrix::CreateOrthographicOffCenter(0.0f, (float)this->m_width, (float)this->m_height, 0.0f, 0.0f, 100.0f);

	this->m_basicEffect->SetWorld(world);
	this->m_basicEffect->SetView(view);
	this->m_basicEffect->SetProjection(projection);

	this->m_basicEffect->Apply(this->m_d3dContext.Get());
	this->m_d3dContext.Get()->IASetInputLayout(this->m_pInputLayout);

	this->m_primitiveBatch->Begin();
}

void LineBatch::Begin(Matrix view, Matrix projection)
{
	Matrix world;

	world = Matrix::Identity;

	this->m_basicEffect->SetWorld(world);
	this->m_basicEffect->SetView(view);
	this->m_basicEffect->SetProjection(projection);

	this->m_basicEffect->Apply(this->m_d3dContext.Get());
	this->m_d3dContext.Get()->IASetInputLayout(this->m_pInputLayout);

	this->m_primitiveBatch->Begin();
}

void LineBatch::End()
{
	this->m_primitiveBatch->End();
}

void LineBatch::Draw(float x1, float y1, float x2, float y2, XMVECTOR color)
{
	Draw(Vector2(x1, y1), Vector2(x2, y2), color);
}

void LineBatch::Draw(Vector2 p1, Vector2 p2, XMVECTOR color)
{
	VertexPositionColor v1(p1, color);
	VertexPositionColor v2(p2, color);
	this->m_primitiveBatch->DrawLine(v1, v2);
}

void LineBatch::DrawLine(Vector2 p1, XMVECTOR color)
{
	VertexPositionColor v1((Vector2(p1.x * (float)this->m_size, -p1.y * (float)this->m_size) + Vector2(this->m_width / 2.0f, this->m_height / 2.0f)), color);
	VertexPositionColor v2(Vector2(this->m_width / 2.0f, this->m_height / 2.0f), color);
	this->m_primitiveBatch->DrawLine(v1, v2);
}

void LineBatch::DrawLine(Vector2 p1, Vector2 p2, XMVECTOR color)
{
	VertexPositionColor v1((Vector2(p1.x * (float)this->m_size, -p1.y * (float)this->m_size) + Vector2(this->m_width / 2.0f, this->m_height / 2.0f)), color);
	VertexPositionColor v2((Vector2(p2.x * (float)this->m_size, -p2.y * (float)this->m_size) + Vector2(this->m_width / 2.0f, this->m_height / 2.0f)), color);
	this->m_primitiveBatch->DrawLine(v1, v2);
}

void LineBatch::Draw(Vector3 p, XMVECTOR color)
{
	VertexPositionColor v1(Vector3(0.0f, 0.0f, 0.0f), color);
	VertexPositionColor v2(p, color);
	m_primitiveBatch->DrawLine(v1, v2);
}

void LineBatch::Draw(Vector3 p1, Vector3 p2, XMVECTOR color)
{
	VertexPositionColor v1(p1, color);
	VertexPositionColor v2(p2, color);
	m_primitiveBatch->DrawLine(v1, v2);
}

