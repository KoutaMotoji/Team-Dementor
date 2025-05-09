//===============================================================================
//
//  �t�F�[�h�p����(fade.cpp)
//								����F���n�O��
// 
//===============================================================================

#include "manager.h"
#include "texture.h"
#include "fade.h"

const float CFade::ALPHA_DEC = 5.0f;
const int CFade::MAX_ALPHA = 255;


CFade::CFade():m_bFinish(false),m_bUse(false), m_FADE_type(FADE_IN)
{
	m_pVtxBuffFade = nullptr;
}

CFade::~CFade()
{

}

//==========================================================================================
//����������
//==========================================================================================
HRESULT CFade::Init()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffFade,
		NULL);

	VERTEX_2D* pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = { 0.0f,0.0f,0.0f };
	pVtx[1].pos = {SCREEN_WIDTH,0.0f,0.0f};
	pVtx[2].pos = {0.0f,SCREEN_HEIGHT,0.0f};
	pVtx[3].pos = {SCREEN_WIDTH,SCREEN_HEIGHT,0.0f};

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffFade->Unlock();

	return S_OK;
}

//==========================================================================================
//�I������
//==========================================================================================
void CFade::Uninit()
{

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuffFade != nullptr)
	{
		m_pVtxBuffFade->Release();
		m_pVtxBuffFade = nullptr;
	}
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CFade::Update()
{	
	if (!m_bFinish)
	{
		if (m_FADE_type == FADE_IN)
		{
			if (FadeIn())
			{
				m_bFinish = true;
				m_bUse = false;
				CManager::GetInstance()->SetMode(setmode);

				SetFade(FADE_OUT, setmode);
			}
		}
		else if(m_FADE_type == FADE_OUT)
		{
			if (FadeOut())
			{
				m_bFinish = true;
			}
		}
	}
	else if (m_bFinish)
	{
		m_bUse = false;
	}

	VERTEX_2D* pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = { 0.0f,0.0f,0.0f };
	pVtx[1].pos = { SCREEN_WIDTH,0.0f,0.0f };
	pVtx[2].pos = { 0.0f,SCREEN_HEIGHT,0.0f };
	pVtx[3].pos = { SCREEN_WIDTH,SCREEN_HEIGHT,0.0f };

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffFade->Unlock();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CFade::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�ʏ�̍����ɖ߂��ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CFade::SetFade(FADE_TYPE type, CScene::MODE mode)
{
	if (!m_bUse)
	{
		m_FADE_type = type;
		m_bUse = true;
		m_bFinish = false;

		setmode = mode;

		if (type == FADE_IN)
		{
			m_nAlpha = 0;
		}
		else
		{
			m_nAlpha = 255;
		}
		if (m_pVtxBuffFade == nullptr)
		{
			Init();
		}
	}
}

//==========================================================================================
//�t�F�[�h���s���Ă邩��Ԃ�����
//==========================================================================================
bool CFade::GetUse()
{
	return m_bUse;
}

//==========================================================================================
//�t�F�[�h�C������
//==========================================================================================
bool CFade::FadeIn()
{
	m_nAlpha += ALPHA_DEC;

	return m_nAlpha >= MAX_ALPHA;
}

//==========================================================================================
//�t�F�[�h�A�E�g����
//==========================================================================================
bool CFade::FadeOut()
{
	m_nAlpha -= ALPHA_DEC;

	return m_nAlpha <= 0;
}
