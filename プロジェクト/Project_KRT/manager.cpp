//===============================================================================
//
//  �e�Ǘ��N���X�̈ꊇ�Ǘ��N���X(manager.cpp)
//								����F���n�O��
// 
//===============================================================================

#include "manager.h"
#include <stdlib.h>
#include <stdio.h>
#include "object.h"
#include "object2D.h"
#include "object3D.h"

CManager* CManager::_instance = nullptr;

CManager::CManager():MAP_SLICE_X(24), MAP_SLICE_Y(18)
{

}

CManager::~CManager()
{

}

//==========================================================================================
//����������
//==========================================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_���[�̐���
	m_pRenderer = new CRenderer();
	//�J�����̐���
	m_pCamera = new CCamera();
	//���C�g�̐���
	m_pLight = new CLight();
	////�T�E���h�̐���
	//m_pSound = new CSound();
	m_pMouse = new CMouse();
	//�L�[�{�[�h�̐���
	m_pKeyboard = new CKeyboard();
	//�W���C�p�b�h�̐���
	m_pJoypad = new CJoypad();

	//�e�N�X�`���̐���
	m_pTexture = new CTexture();

	m_pFade = new CFade();
	//�������ݒ�
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//�����������s�����ꍇ
		return -1;
	}
	//�L�[�{�[�h�̏������ݒ�
	m_pKeyboard->Init(hInstance, hWnd);
	//�W���C�p�b�h�̏�����
	m_pJoypad->Init(hInstance,hWnd);
	m_pMouse->Init(hInstance, hWnd);
	//�J�����̏�����
	m_pCamera->Init();
	////�T�E���h�̏�����
	//m_pSound->Init(hWnd);
	//���C�g�̏�����
	m_pLight->Init();

	SetMode(CScene::MODE_TITLE);
	m_pFade->SetFade(m_pFade->FADE_OUT, CScene::MODE_GAME);
	return S_OK;
}

//==========================================================================================
//�I�����i
//==========================================================================================
void CManager::Uninit()
{
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
	/*if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}*/
	if (m_pTexture != nullptr)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
	if (m_pMouse != nullptr)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}
	if (m_pJoypad != nullptr)
	{
		m_pJoypad->Uninit();
		delete m_pJoypad;
		m_pJoypad = nullptr;
	}
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CManager::Update()
{

	m_pFade->Update();
	
	m_pScene->Update();
	m_pRenderer->Update();
	m_pMouse->Update();
	m_pKeyboard->Update();
	m_pJoypad->Update();
	m_pCamera->Update();
	
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CManager::Draw()
{
	m_pRenderer->Draw(m_pScene);
}

//==========================================================================================
//�V�[���؂�ւ�
//==========================================================================================
void CManager::SetMode(CScene::MODE mode)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
	m_pScene = CScene::Create(mode);
	m_pScene->Init();
}
