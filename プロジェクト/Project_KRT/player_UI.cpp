//===============================================================================
//
//  �v���C���[��UI�\��(player_UI.cpp)
//								����F���n�O��
// 
//===============================================================================

#include "player_UI.h"

#include "player_observer.h"
#include "manager.h"

namespace
{
	std::string _FILENAME_HP_GAUGE = "data\\TEXTURE\\playerHP.png";
	std::string _FILENAME_HP_FRAME = "data\\TEXTURE\\playerHPframe.png";
	std::string _FILENAME_HP_BACK = "data\\TEXTURE\\playerHPback.png";
	std::string _FILENAME_HP_DECO = "data\\TEXTURE\\playerHPdeco.png";
	std::string _FILENAME_HP_CIRCLEGAUGE = "data\\TEXTURE\\UI000.png";

	std::string _FILENAME_WEAPON_SUB = "data\\TEXTURE\\weapon.png";
	std::string _FILENAME_WEAPON_BACK = "data\\TEXTURE\\WeaponUI_Sub.png";
	std::string _FILENAME_WEAPON_MAIN = "data\\TEXTURE\\Weapn_free.png";
	std::string _FILENAME_WEAPON_GORIRA = "data\\TEXTURE\\Boss000.png";



	D3DXVECTOR2 _HP_GAUGE_SIZE = { 400.0f,70.0f };		//HP�Q�[�W��UI�T�C�Y
	D3DXVECTOR2 _HP_GAUGE_DECO_SIZE = { 600.0f,80.0f };	//HP�Q�[�W�����T�C�Y
	D3DXVECTOR3 _HP_GAUGE_POS = { (_HP_GAUGE_DECO_SIZE.x * 0.5f) - 50.0f,SCREEN_HEIGHT - (_HP_GAUGE_DECO_SIZE.y * 0.5f),0.0f };		//HP�Q�[�W��UI���W
	D3DXVECTOR3 _HP_GAUGE_DECO_POS = { _HP_GAUGE_POS.x + 50.0f,_HP_GAUGE_POS.y,0.0f };		//HP�Q�[�W��UI���W
	D3DXVECTOR3 _HP_GAUGE_CIRCLE_POS = { 1000.0f,500.0f,0.0f };

	D3DXVECTOR3 _WEAPON_SUBUI_POS = { _HP_GAUGE_POS.x ,_HP_GAUGE_POS.y - 60.0f,0.0f };
	D3DXVECTOR3 _WEAPON_SUBUI_SIZE = { 500.0f ,80.0f,0.0f };
	D3DXVECTOR3 _WEAPON_BACKUI_POS = { _WEAPON_SUBUI_POS.x - 50.0f,_WEAPON_SUBUI_POS.y ,0.0f };
	D3DXVECTOR3 _WEAPON_BACKUI_SIZE = { 150.0f ,30.0f,0.0f };
	D3DXVECTOR3 _WEAPON_UI_POS = { _WEAPON_SUBUI_POS.x + 100.0f,_WEAPON_SUBUI_POS.y ,0.0f };
	D3DXVECTOR3 _WEAPON_UI_SIZE = { 80.0f ,80.0f,0.0f };


	float _GAUGE_RADIUS = 100.0f;

	D3DXCOLOR _GAUGE_COLOR = { 0.0f,1.0f,0.2f,1.0f };
}

CGaugeLife::CGaugeLife(int nPriority) :CObject2D(nPriority)
{

}

CGaugeLife::~CGaugeLife()
{

}

//==========================================================================================
//����������
//==========================================================================================
void CGaugeLife::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_HP_GAUGE.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CGaugeLiFrame::Create(CObject2D::GetPos(), _HP_GAUGE_SIZE.x, _HP_GAUGE_SIZE.y);
	CGaugeLiBack::Create(CObject2D::GetPos(), _HP_GAUGE_SIZE.x, _HP_GAUGE_SIZE.y);
	CGaugeLiDeco::Create();
	CWeaponUI_Sub::Create();
	CWeaponUI_Back::Create();

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
	CObject2D::SetColor(_GAUGE_COLOR);
}

//==========================================================================================
//�I������
//==========================================================================================
void CGaugeLife::Uninit()
{
	CObject2D::Uninit();
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CGaugeLife::Update()
{
	CGaugeLife::SetGauge();
	CObject2D::Update();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CGaugeLife::Draw()
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
CGaugeLife* CGaugeLife::Create(int nMaxGauge)
{
	CGaugeLife* gauge = new CGaugeLife;
	gauge->SetPolygonParam(_HP_GAUGE_POS, _HP_GAUGE_SIZE.y, _HP_GAUGE_SIZE.x, nMaxGauge, false);
	gauge->Init();
	return gauge;
}

//==========================================================================================
//���l���擾���Ĕ��f
//==========================================================================================
void CGaugeLife::SetGauge()
{
	int nNowGauge = CPlayerObserver::GetInstance()->GetPlayerLife();
	CObject2D::SetGauge(nNowGauge);
}

//----------------------------------------------------------------------------------------------------------------------------------
//�g�E���E�����ݒ�p

//==========================================================================================
//�g�̏���������
//==========================================================================================
void CGaugeLiFrame::Init()
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
void CGaugeLiFrame::Draw()
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
CGaugeLiFrame* CGaugeLiFrame::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CGaugeLiFrame* gauge = new CGaugeLiFrame;
	gauge->SetPolygonParam(pos, fHeight, fWidth, { 1.0f,1.0f,1.0f,1.0f });
	gauge->Init();
	return gauge;
}

//==========================================================================================
//��둤�̏���������
//==========================================================================================
void CGaugeLiBack::Init()
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
void CGaugeLiBack::Draw()
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
CGaugeLiBack* CGaugeLiBack::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CGaugeLiBack* gauge = new CGaugeLiBack;
	gauge->SetPolygonParam(pos, fHeight, fWidth, { 1.0f,1.0f,1.0f,1.0f });
	gauge->Init();
	return gauge;
}

//==========================================================================================
//HP�����̏���������
//==========================================================================================
void CGaugeLiDeco::Init()
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
void CGaugeLiDeco::Draw()
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
CGaugeLiDeco* CGaugeLiDeco::Create()
{
	CGaugeLiDeco* gauge = new CGaugeLiDeco;

	gauge->SetPolygonParam(_HP_GAUGE_DECO_POS, _HP_GAUGE_DECO_SIZE.y, _HP_GAUGE_DECO_SIZE.x, { 1.0f,1.0f,1.0f,1.0f });
	gauge->Init();

	return gauge;
}

//==========================================================================================
//�~�`�Q�[�W�̏���������
//==========================================================================================
void CGaugeCircle::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_HP_CIRCLEGAUGE.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx));

	CObject::SetType(TYPE_2D_UI);
	CObjectCircleGauge::Init();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CGaugeCircle::Update()
{
	int life = 1000 - CPlayerObserver::GetInstance()->GetPlayerLife();
	float nNowGauge = (float)life / 1000.0f;

	CObjectCircleGauge::SetGaugePercent(nNowGauge);

	CObjectCircleGauge::Update();

}


//==========================================================================================
//�`�揈��
//==========================================================================================
void CGaugeCircle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();


	CObjectCircleGauge::Draw();
}

//==========================================================================================
//�~�`�Q�[�W�̐�������
//==========================================================================================
CGaugeCircle* CGaugeCircle::Create()
{
	CGaugeCircle* gauge = new CGaugeCircle;

	gauge->SetPolygonParam(_HP_GAUGE_CIRCLE_POS, _GAUGE_RADIUS);
	gauge->Init();

	return gauge;
}

//==========================================================================================
//�~�`�Q�[�W�w�i�̏���������
//==========================================================================================
void CGaugeCircleDeco::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_HP_CIRCLEGAUGE.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CGaugeCircleDeco::Draw()
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
//�~�`�Q�[�W�w�i�̐�������
//==========================================================================================
CGaugeCircleDeco* CGaugeCircleDeco::Create()
{
	CGaugeCircleDeco* gauge = new CGaugeCircleDeco;
	D3DXVECTOR3 pos = {
		_HP_GAUGE_CIRCLE_POS.x + _GAUGE_RADIUS,
		_HP_GAUGE_CIRCLE_POS.y + _GAUGE_RADIUS,
		0.0f
	};
	gauge->SetPolygonParam(pos, _GAUGE_RADIUS * 2, _GAUGE_RADIUS * 2, { 1.0f,1.0f,1.0f,0.4f });
	gauge->Init();

	return gauge;
}

//==========================================================================================
//����UI�����̏�����
//==========================================================================================
void CWeaponUI_Sub::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_WEAPON_SUB.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//����UI�����̐���
//==========================================================================================
CWeaponUI_Sub* CWeaponUI_Sub::Create()
{
	CWeaponUI_Sub* gauge = new CWeaponUI_Sub;
	gauge->SetPolygonParam(_WEAPON_BACKUI_POS, _WEAPON_BACKUI_SIZE.y, _WEAPON_BACKUI_SIZE.x);
	gauge->Init();

	return gauge;
}

//==========================================================================================
//����UI�w�i�̏�����
//==========================================================================================
void CWeaponUI_Back::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_WEAPON_BACK.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//����UI�w�i�̐���
//==========================================================================================
CWeaponUI_Back* CWeaponUI_Back::Create()
{
	CWeaponUI_Back* gauge = new CWeaponUI_Back;
	gauge->SetPolygonParam(_WEAPON_SUBUI_POS, _WEAPON_SUBUI_SIZE.y, _WEAPON_SUBUI_SIZE.x);
	gauge->Init();

	return gauge;
}

//==========================================================================================
//����UI(�Ȃ�)�̏�����
//==========================================================================================
void CWeaponUI_Main::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_WEAPON_MAIN.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//����UI(�Ȃ�)�̐���
//==========================================================================================
CWeaponUI_Main* CWeaponUI_Main::Create()
{
	CWeaponUI_Main* gauge = new CWeaponUI_Main;
	gauge->SetPolygonParam(_WEAPON_UI_POS, _WEAPON_UI_SIZE.y, _WEAPON_UI_SIZE.x);
	gauge->Init();

	return gauge;
}

//==========================================================================================
//����UI(�S����)�̏�����
//==========================================================================================
void CWeaponUI_Main_Gorira::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_WEAPON_GORIRA.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//����UI(�S����)�̐���
//==========================================================================================
CWeaponUI_Main_Gorira* CWeaponUI_Main_Gorira::Create()
{
	CWeaponUI_Main_Gorira* gauge = new CWeaponUI_Main_Gorira;
	gauge->SetPolygonParam(_WEAPON_UI_POS, _WEAPON_UI_SIZE.y, _WEAPON_UI_SIZE.x);
	gauge->Init();

	return gauge;
}