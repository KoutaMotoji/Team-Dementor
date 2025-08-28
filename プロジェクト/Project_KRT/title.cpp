//===============================================================================
//
//  �^�C�g���V�[��(title.cpp)
//								����F���n�O��
// 
//===============================================================================

#include "manager.h"

#include "mesh_cylinder.h"
#include "title_obj.h"
#include "title.h"
#include "fade.h"

namespace AnimPoint
{

}

namespace 
{
	D3DXVECTOR3 LogoPos = {260.0f,150.0f, 0.0f};
	D3DXVECTOR2 LogoSize = { 450.0f,280.0f };

}


CTitle::CTitle(): m_bNowAnim(false), m_AnimTimer(0), m_nSelect(0)
{
}

CTitle::~CTitle()
{

}

//==========================================================================================
//����������
//==========================================================================================
HRESULT CTitle::Init()
{
	CScene::Init();
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
	CT_Graound::Create();
	CT_Player::Create();
	CMeshCylinder::Create({ 0.0f,1000.0f,0.0f });
	D3DXVECTOR3 posA, posB;
	posA = { 300.0f,-100.0f,-200.0f };
	posB = { 120.0f,-20.0f,-30.0f };
	CManager::GetInstance()->GetCamera()->SetFreeCam(posA,posB ,120,true);
	CTitleBG::Create();
	return S_OK;
}

//==========================================================================================
//�I������
//==========================================================================================
void CTitle::Uninit()
{
	CScene::Uninit();
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CTitle::Update()
{
	//CManager::GetInstance()->GetCamera()->SetFreeCam({ 0.0f,0.0f,0.0f }, { -200.0f,-100.0f,-2000.0f }, 120);

	if (CManager::GetInstance()->GetKeyboard()->CKeyboard::GetTrigger(DIK_RETURN) || CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_A)) 
	{
		CManager::GetInstance()->GetFade()->SetFade(CFade::FADE_IN, CScene::MODE_GAME);
	}
	CScene::Update();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CTitle::Draw()
{
	CScene::Draw();
}

//==========================================================================================
//�^�C�g���A�j���[�V��������
//==========================================================================================
void CTitle::UpdateAnim(int m)
{

	
}

//==========================================================================================
//�g�̏���������
//==========================================================================================
void CTitleBG::Init()
{
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\titleLOGO.png");
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//�g�̏���������
//==========================================================================================
void CTitleBG::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�e�N�X�`���g�厞�ɐF���ߎ��l�ɂ���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//�X�e���V���}�X�N�̐ݒ莞�ɖ���������Z�o�b�t�@�����Ƃɂ��ǂ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//�A���t�@�e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//�e�N�X�`���g�厞�̐F����`���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//==========================================================================================
//�g�̐�������
//==========================================================================================
CTitleBG* CTitleBG::Create()
{
	CTitleBG* bg = new CTitleBG;

	bg->SetPolygonParam({ LogoPos.x,LogoPos.y,0.0f }, LogoSize.y, LogoSize.x);
	bg->Init();

	return bg;
}
