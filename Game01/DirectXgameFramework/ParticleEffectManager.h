/**
* @file ParticleEffectManager.h
* @brief �p�[�e�B�N���G�t�F�N�g���Ǘ�����N���X�̃w�b�_�t�@�C��
* @author �������l
* @date 2017/11/07
*/
#pragma once
#include <vector>
#include <map>

#include <Windows.h>
#include <wrl/client.h>

#include <d3d11_1.h>

#include <SimpleMath.h>
#include <CommonStates.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>


#include "Framework\Camera.h"
#include "Framework\Graphics.h"
#include "ParticleEffect.h"


// �p�[�e�B�N���G�t�F�N�g���Ǘ�����N���X�̃w�b�_�t�@�C��
class ParticleEffectManager
{
public:
	static ParticleEffectManager* GetInstance();
public:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Vector4 = DirectX::SimpleMath::Vector4;


	static const int POINT_NUM;
	// �p�[�e�B�N���̍ő吔
	static const int PARTICLE_NUM_MAX;
	// ���̓��C�A�E�g�̍쐬
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	// �R���X�^���g�o�b�t�@
	struct Constants
	{
		DirectX::SimpleMath::Matrix WVP;		// ���[���h,�r���[,�v���W�F�N�V�����̍����s��
		DirectX::SimpleMath::Matrix Billboard;	// �r���{�[�h�s��
	};

public:
	// ������
	void Initialize(Camera* pCamera);
	// �X�V
	void Update();				
	// �ǂݍ���
	void AddTexture(std::string typeName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texure);
	// �`��
	void Draw();				
	// �o�^
	void Entry(ParticleEffect* particleData) ;

private:
	static ParticleEffectManager* s_instance;

private:
	ParticleEffectManager();// ����J�R���X�g���N�^

private:
	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_Primitivebatch;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
	//���_�f�[�^�z��
	std::vector<ParticleEffect*> m_particles;


	// �ėp�`��ݒ�
	std::unique_ptr<DirectX::CommonStates> m_commonStates;
	// �R���X�^���g�o�b�t�@�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_ConstantBuffer;
	// �e�N�X�`���̃}�b�v�R���e�i
	std::map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_Textures;
	// �e�N�X�`���T���v���[
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler;
	// �J����
	Camera* m_Camera;

};

