// Game.h

#pragma once
#ifndef GAME
#define GAME

#include <windows.h>
#include <iostream>
#include <string>
#include <iomanip>

#include <d3d11.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Model.h>
#include <Keyboard.h>
#include <GeometricPrimitive.h>
#include <WICTextureLoader.h>
#include <Effects.h>

#include "..\StepTimer.h"

#include "Window.h"
#include "Graphics.h"
#include "DebugCamera.h"
#include "Grid.h"

class Window;

// D3D11�f�o�C�X�𐶐����A�Q�[�����[�v��񋟂����{�Q�[������
// A basic game implementation that creates a D3D11 device and provides a game loop.
class Game
{
public:
	// �R���X�g���N�^ Constructor
    Game(int width, int height);
    // �������ƊǗ� Initialization and management
	virtual void Initialize();
	// �I�������������Ȃ� Finalize game
	virtual void Finalize();
    // ��{�Q�[�����[�v Basic game loop
	MSG Update();

    // ���b�Z�[�W Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);
    // �v���p�e�B Properties
    void GetDefaultSize(int& width, int& height) const;

protected:
	// �Q�[�����X�V���� Update game
    virtual void Update(DX::StepTimer const& timer);
    // �V�[����`�悷�� Render scene
	virtual void Render(DX::StepTimer const & timer);
	// ��ʂ��N���A���� Clear screen
	virtual void Clear();
	virtual void Present();
	// FPS��`�悷�� Draw FPS
	void DrawFPS();

protected:

	// �C���X�^���X�n���h��
	HINSTANCE hInstance;
	// ���s���̃E�B���h�E�̑傫��
	int nCmdShow;
	// �f�o�C�X���\�[�X Device resources
	HWND hWnd;
	// �o�͕� window width
	int width;
	// �o�͍� window height
	int height;

	// �E�B���h�E�f�[�^
	std::unique_ptr<Window> window;
	// �O���t�B�b�N�X Graphics
	std::unique_ptr<Graphics> graphics;
	// �@�\���x�� Feature level
    D3D_FEATURE_LEVEL featureLevel;
    // ���[�v�^�C�}�[��`�悷�� Rendering loop timer
    DX::StepTimer timer;

	// �L�[�{�[�h Keyboard
	std::unique_ptr<Keyboard> keyboard;
	// �X�v���C�g�o�b�` SpriteBatch
	std::unique_ptr<SpriteBatch>	spriteBatch;

	// �O���b�h�t���A GridFloor
	std::unique_ptr<GridFloor> gridFloor;
	// �t�H���g Font
	std::unique_ptr<SpriteFont> font;
	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	//���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �G�t�F�N�g�t�@�N�g���C���^�[�t�F�[�X IEffectFactory
	std::unique_ptr<IEffectFactory> fxFactory;
	// �R�����X�e�[�g CommonStates
	std::unique_ptr<CommonStates> commonStates;

	// ���[���h world
	DirectX::SimpleMath::Matrix world;
	// �X�P�[�� scale
	float scale;


	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_proj;
};


#endif	// GAME
