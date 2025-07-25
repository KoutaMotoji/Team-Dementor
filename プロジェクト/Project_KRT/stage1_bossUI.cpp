//===============================================================================
//
//  �v���C���[��UI�\��(player_UI.cpp)
//								����F���n�O��
// 
//===============================================================================

#include "stage1_bossUI.h"

#include "player_observer.h"
#include "manager.h"

namespace
{
	std::string _FILENAME_HP_GAUGE = "data\\TEXTURE\\bossHP.png";
	std::string _FILENAME_HP_FRAME = "data\\TEXTURE\\bossHPframe.png";
	std::string _FILENAME_HP_BACK = "data\\TEXTURE\\bossHPback.png";
	std::string _FILENAME_HP_DECO = "data\\TEXTURE\\bossback.png";


	D3DXVECTOR2 _HP_GAUGE_SIZE = { 520.0f,40.0f };		//HP�Q�[�W��UI�T�C�Y
	D3DXVECTOR2 _HP_GAUGE_DECO_SIZE = { 630.0f,85.0f };	//HP�Q�[�W�����T�C�Y
	D3DXVECTOR3 _HP_GAUGE_POS = { SCREEN_WIDTH * 0.5f,(_HP_GAUGE_DECO_SIZE.y * 0.5f) + 15.0f,0.0f };		//HP�Q�[�W��UI���W
	D3DXVECTOR3 _HP_GAUGE_DECO_POS = { _HP_GAUGE_POS.x,_HP_GAUGE_POS.y - 15.0f,0.0f };		//HP�Q�[�W��UI���W

	D3DXCOLOR _GAUGE_COLOR = { 1.0f,0.0f,0.0f,1.0f };
}

CStage1BossGaugeLife::CStage1BossGaugeLife(int nPriority) :CObject2D(nPriority)
{

}

CStage1BossGaugeLife::~CStage1BossGaugeLife()
{

}

//==========================================================================================
//����������
//==========================================================================================
void CStage1BossGaugeLife::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_HP_GAUGE.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CStage1BossGaugeLiFrame::Create(CObject2D::GetPos(), _HP_GAUGE_SIZE.x, _HP_GAUGE_SIZE.y);
	CStage1BossGaugeLiBack::Create(CObject2D::GetPos(), _HP_GAUGE_SIZE.x, _HP_GAUGE_SIZE.y);
	CStage1BossGaugeLiDeco::Create();

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
	CObject2D::SetColor(_GAUGE_COLOR);
}

//==========================================================================================
//�I������
//==========================================================================================
void CStage1BossGaugeLife::Uninit()
{
	CObject2D::Uninit();
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CStage1BossGaugeLife::Update()
{
	CObject2D::Update();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CStage1BossGaugeLife::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	//�e�N�X�`���g�厞�ɐF���ߎ��l�ɂ���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//�A���t�@�e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//�e�N�X�`���g�厞�̐F����`���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//==========================================================================================
//��������
//==========================================================================================
CStage1BossGaugeLife* CStage1BossGaugeLife::Create(int nMaxStage1BossGauge)
{
	CStage1BossGaugeLife* gauge = new CStage1BossGaugeLife;
	gauge->SetPolygonParam(_HP_GAUGE_POS, _HP_GAUGE_SIZE.y, _HP_GAUGE_SIZE.x, nMaxStage1BossGauge, false);
	gauge->Init();
	return gauge;
}

//==========================================================================================
//���l���擾���Ĕ��f
//==========================================================================================
void CStage1BossGaugeLife::SetStage1BossGauge(int nLife)
{
	int nNowStage1BossGauge = CPlayerObserver::GetInstance()->GetPlayerLife();
	CObject2D::SetGauge(nNowStage1BossGauge);
}

//----------------------------------------------------------------------------------------------------------------------------------
//�g�E���E�����ݒ�p

//==========================================================================================
//�g�̏���������
//==========================================================================================
void CStage1BossGaugeLiFrame::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_HP_FRAME.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CStage1BossGaugeLiFrame::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	//�e�N�X�`���g�厞�ɐF���ߎ��l�ɂ���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
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
CStage1BossGaugeLiFrame* CStage1BossGaugeLiFrame::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CStage1BossGaugeLiFrame* gauge = new CStage1BossGaugeLiFrame;
	gauge->SetPolygonParam(pos, fHeight, fWidth, { 1.0f,1.0f,1.0f,1.0f });
	gauge->Init();
	return gauge;
}

//==========================================================================================
//��둤�̏���������
//==========================================================================================
void CStage1BossGaugeLiBack::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_HP_BACK.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CStage1BossGaugeLiBack::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�e�N�X�`���g�厞�ɐF���ߎ��l�ɂ���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//�A���t�@�e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//�e�N�X�`���g�厞�̐F����`���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//==========================================================================================
//��둤�̐�������
//==========================================================================================
CStage1BossGaugeLiBack* CStage1BossGaugeLiBack::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CStage1BossGaugeLiBack* gauge = new CStage1BossGaugeLiBack;
	gauge->SetPolygonParam(pos, fHeight, fWidth, { 1.0f,1.0f,1.0f,1.0f });
	gauge->Init();
	return gauge;
}

//==========================================================================================
//HP�����̏���������
//==========================================================================================
void CStage1BossGaugeLiDeco::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_HP_DECO.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CStage1BossGaugeLiDeco::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�e�N�X�`���g�厞�ɐF���ߎ��l�ɂ���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	//�A���t�@�e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//�e�N�X�`���g�厞�̐F����`���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//==========================================================================================
//HP�����̐�������
//==========================================================================================
CStage1BossGaugeLiDeco* CStage1BossGaugeLiDeco::Create()
{
	CStage1BossGaugeLiDeco* gauge = new CStage1BossGaugeLiDeco;

	gauge->SetPolygonParam(_HP_GAUGE_DECO_POS, _HP_GAUGE_DECO_SIZE.y, _HP_GAUGE_DECO_SIZE.x, { 1.0f,1.0f,1.0f,1.0f });
	gauge->Init();

	return gauge;
}

