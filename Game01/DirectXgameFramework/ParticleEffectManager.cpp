/**
* @file �t�@�C����.h
* @brief �ȒP�Ȑ���
* @author �������l
* @date 2017/11/07
*/

#include "ParticleEffectManager.h"
#include <WICTextureLoader.h> 

#include "Framework\Graphics.h"
#include "BinaryFile.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

using Microsoft::WRL::ComPtr;

// �C���X�^���X���`
ParticleEffectManager* ParticleEffectManager::s_instance = nullptr;

// �p�[�e�B�N���̍ő吔
const int ParticleEffectManager::PARTICLE_NUM_MAX = 30000;
const int ParticleEffectManager::POINT_NUM = 200;

// ���̓��C�A�E�g�̒�`
const std::vector<D3D11_INPUT_ELEMENT_DESC>  ParticleEffectManager::INPUT_LAYOUT =
{
	{ "POSITION",	0,	 DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0,	 DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0,   DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Vector3) + sizeof(Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },


};

// �V���O���g���C���X�^���X�̎擾
ParticleEffectManager* ParticleEffectManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new ParticleEffectManager();
	}
	return s_instance;
}

ParticleEffectManager::ParticleEffectManager()
	:m_Camera(nullptr)
{
}

void ParticleEffectManager::Initialize(Camera* pCamera)
{
	// �R���p�C�����ꂽ�V�F�[�_�t�@�C���̓ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");

	// �f�o�C�X�A�f�o�C�X�R���e�L�X�g�̎擾
	ID3D11Device* device = Graphics::Get().Device().Get();
	ID3D11DeviceContext * context = Graphics::Get().Context().Get();

	// ���_�V�F�[�_���쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_VertexShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateVertexShader Failed", NULL, MB_OK);
	}

	// �W�I���g���V�F�[�_���쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_GeometryShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateGeometryShader Failed", NULL, MB_OK);
	}

	// �s�N�Z���V�F�[�_���쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_PixelShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreatePixelShader Failed", NULL, MB_OK);
	}

	m_Primitivebatch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context, 1, PARTICLE_NUM_MAX);

	// ���̓��C�A�E�g�̍쐬
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		INPUT_LAYOUT.size(),
		VSData.GetData(), VSData.GetSize(),
		m_InputLayout.GetAddressOf());

	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(Constants);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(device->CreateBuffer(&cb, nullptr, m_ConstantBuffer.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateBuffer Failed", NULL, MB_OK);
		return;

	}

	// �J�������Z�b�g
	m_Camera = pCamera;


	// �ėp�`��ݒ��������
	m_commonStates = make_unique<CommonStates>(device);



	// �e�N�X�`���T���v���[�̐ݒ�
	D3D11_SAMPLER_DESC sam;
	ZeroMemory(&sam, sizeof(sam));		// ������(�f�t�H���g�l)
	sam.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sam.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sam.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sam.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	// �ݒ����Ƀe�N�X�`���T���v�����쐬
	if (FAILED(device->CreateSamplerState(&sam, m_Sampler.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateSamplerState Failed", NULL, MB_OK);
		return;
	}
}

void ParticleEffectManager::Update()
{
// �e�f�[�^�̍X�V
	vector<ParticleEffect*>::iterator itr = m_particles.begin();
	while (itr != m_particles.end()) {
		(*itr)->Update();

		// �I�������p�[�e�B�N���f�[�^���폜
		if ((*itr)->GetEndFlag())
		{
			itr = m_particles.erase(itr);
		}
		else itr++;
	}


}

void ParticleEffectManager::AddTexture(std::string typeName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texure)
{
	m_Textures[typeName] = texure;
}

void ParticleEffectManager::Draw()
{
	// �_���Ȃ���Ε`�悵�Ȃ�
	if (m_particles.size() == 0) return;


	// �f�o�C�X�A�f�o�C�X�R���e�L�X�g�̎擾
	ID3D11Device* device = Graphics::Get().Device().Get();
	ID3D11DeviceContext * context = Graphics::Get().Context().Get();

	// �ݒ肵���o�b�t�@�����ۂɃV�F�[�_�ɓK�p
	context->VSSetConstantBuffers(0, 0, nullptr);
	context->GSSetConstantBuffers(0, 1, m_ConstantBuffer.GetAddressOf());
	context->PSSetConstantBuffers(0, 0, nullptr);

	// �f�o�C�X�R���e�L�X�g�ɃV�F�[�_���Z�b�g
	context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_GeometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_PixelShader.Get(), nullptr, 0);

	Matrix world = Matrix::Identity;
	Matrix view = m_Camera->GetView();
	Matrix proj = m_Camera->GetProj();

	world = Matrix::CreateScale(1.0f);
	Matrix wvp = world * view * proj;

	// �V�F�[�_�̃R���X�^���g�o�b�t�@�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(context->Map(m_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		Constants constants;
		constants.WVP = wvp;
		constants.Billboard = m_Camera->GetBillboard();

		// constants = = = >  pData.pData
		memcpy_s(pData.pData, pData.RowPitch, &constants, sizeof(Constants));
		// �}�b�v�I���
		context->Unmap(m_ConstantBuffer.Get(), 0);
	}
	// �f�o�C�X�R���e�L�X�g�ɓ��̓��C�A�E�g���Z�b�g
	context->IASetInputLayout(m_InputLayout.Get());
	// �A�ʏ����̐ݒ�
	context->RSSetState(m_commonStates->CullNone());


	ID3D11BlendState* blendStateSubtract;
	// ���Z�`��p�̃u�����h�X�e�[�g���쐬
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	device->CreateBlendState(&desc, &blendStateSubtract);

	// �A���t�@�u�����h�̐ݒ�
	//context->OMSetBlendState(m_commonStates->NonPremultiplied(), nullptr, 0xffffffff);
	// ���Z�`��
	context->OMSetBlendState(m_commonStates->Additive(), nullptr, 0xffffffff);
	// ���Z�`��
	//context->OMSetBlendState(blendStateSubtract, nullptr, 0xffffffff);

	// �[�x�e�X�g�̐ݒ�
	context->OMSetDepthStencilState(m_commonStates->DepthNone(), 0);
	// �e�N�X�`���T���v���[��ݒ�
	context->PSSetSamplers(0, 1, m_Sampler.GetAddressOf());


	for (auto& particle : m_particles)
	{
		// �e�N�X�`�����V�F�[�_�ɓn��
		auto texture = particle->GetType();
		context->PSSetShaderResources(0, 1, m_Textures[texture].GetAddressOf());

		m_Primitivebatch->Begin();
		m_Primitivebatch->Draw(D3D_PRIMITIVE_TOPOLOGY_POINTLIST, particle->GetVertexData(), 1);
		m_Primitivebatch->End();
	}
	
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

void ParticleEffectManager::Entry(ParticleEffect* particleData)  
{
	ParticleEffect* particle = new ParticleEffect(*particleData);

	// �R���e�i�Ɋi�[
	m_particles.push_back(particle);
}
