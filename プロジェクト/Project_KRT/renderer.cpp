//===============================================================================
//
//  �`��Ǘ��N���X(renderer.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "main.h"
#include "object.h"
#include "renderer.h"
#include "manager.h"

CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_D3DDevice = nullptr;
}

CRenderer::~CRenderer()
{
	//Direct3D�f�o�C�X�̔j��
	if (m_D3DDevice != NULL)
	{
		m_D3DDevice->Release();
		m_D3DDevice = NULL;
	}
	//Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//==========================================================================================
//����������
//==========================================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm; //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;
	//Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	ZeroMemory(&d3dpp, sizeof(d3dpp));//�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	/*
	//�f�o�b�O�p�\���t�H���g�̐���
	D3DXCreateFont(m_D3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);
	*/

	//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_D3DDevice)))
	{
		//Direct3D�f�o�C�X�̐���(�`�揈�����n�[�h�E�F�A�A���_������CPU�ōs��
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_D3DDevice)))
		{
			//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_D3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//--------------------------------
	//�e��I�u�W�F�N�g�̏���������
	//--------------------------------

	//�����_�[�X�e�[�g�̐ݒ�
	m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// �T���v���[�X�e�[�g�̐ݒ�
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	return S_OK;
}

//==========================================================================================
//�I������
//==========================================================================================
void CRenderer::Uninit(void)
{
	/*
	//�f�o�b�O�p�\���t�H���g�̔j��k
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
	*/
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CRenderer::Update(void)
{
	//--------------------------------
	//�e��I�u�W�F�N�g�̍X�V����
	//--------------------------------

	CObject::UpdateAll();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CRenderer::Draw(CScene* pScene)
{
	//��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	m_D3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(50, 50, 50, 0), 1.0f, 0);
	//�`��J�n
	if (SUCCEEDED(m_D3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ
			//--------------------------------
			//�e��I�u�W�F�N�g�̕`�揈��
			//--------------------------------
		CManager::GetInstance()->GetCamera()->SetCamera();

		//�|���S���̕`�揈��
		pScene->Draw();

		CManager::GetInstance()->GetFade()->Draw();

		//�`��I��
		m_D3DDevice->EndScene();
		//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
		m_D3DDevice->Present(NULL, NULL, NULL, NULL);
	}
}

//==========================================================================================
//�f�o�C�X�̎擾
//==========================================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_D3DDevice;
}