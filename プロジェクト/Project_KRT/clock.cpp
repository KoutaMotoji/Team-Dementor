//===============================================================================
//
//		���vUI(Clock.h)
//								����F���n�O��
// 
//===============================================================================
#include "clock.h"
#include "manager.h"

namespace
{
	std::string _FILENAME_CLOCK_GAUGE = "data\\TEXTURE\\ClockScale.png";
	std::string _FILENAME_CLOCK_DECO = "data\\TEXTURE\\Clockback.png";
	std::string _FILENAME_CLOCK_HANDS = "data\\TEXTURE\\counter.png";

	float _GAUGE_RADIUS = 80.0f;

	D3DXVECTOR3 _HP_GAUGE_CIRCLE_POS = { _GAUGE_RADIUS - 20.0f,_GAUGE_RADIUS - 50.0f,0.0f };
}

std::shared_ptr<CClock> CClock::_instance = nullptr;


//==========================================================================================
//�~�`�Q�[�W�̏���������
//==========================================================================================
void CClockGauge::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_CLOCK_GAUGE.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx));

	CObject::SetType(TYPE_2D_UI);
	CObjectCircleGauge::Init();
	CObjectCircleGauge::SetColor({ 1.0f,0.0f,0.1f,0.8f });

	m_pClockBack = CClockBack::Create();
	m_pClockHands = CClockHands::Create();
}
//==========================================================================================
//�I������
//==========================================================================================
void CClockGauge::Uninit()
{
	CObjectCircleGauge::Uninit();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CClockGauge::Update()
{

	int nMaxTime = CClock::GetInstance()->GetMaxCount();
	int nNowTime = nMaxTime - CClock::GetInstance()->GetLastCount();

	float nNowGauge = (float)nNowTime / (float)nMaxTime;

	CObjectCircleGauge::SetGaugePercent(nNowGauge);
	float SetAngleValue = 1.0f - nNowGauge;
	float Radian = (D3DX_PI * 2) * SetAngleValue;
	m_pClockHands->SetRot({ 0.0f,0.0f,Radian });
	if (CClock::GetInstance()->GetTimeUped())
	{
		QuakeObj();
	}
	CObjectCircleGauge::Update();
}


//==========================================================================================
//�`�揈��
//==========================================================================================
void CClockGauge::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CObjectCircleGauge::Draw();
}

//==========================================================================================
//�~�`�Q�[�W�̐�������
//==========================================================================================
CClockGauge* CClockGauge::Create()
{
	CClockGauge* gauge = new CClockGauge;

	gauge->SetPolygonParam(_HP_GAUGE_CIRCLE_POS, _GAUGE_RADIUS);
	gauge->Init();

	return gauge;
}

void CClockGauge::QuakeObj()
{
	std::random_device rnd;				// �񌈒�I�ȗ���������ŃV�[�h�����@�𐶐�
	std::mt19937 mt(rnd());				//  �����Z���k�c�C�X�^�[��32�r�b�g�ŁA�����͏����V�[�h
	std::uniform_int_distribution<> rand_num_x(0, 20);     // [0, 20] �͈͂̈�l����
	std::uniform_int_distribution<> rand_num_y(0, 20);     // [0, 20] �͈͂̈�l����

	float quakeValue_X = (float)(rand_num_x(mt)) - 10;
	float quakeValue_Y = (float)(rand_num_y(mt)) - 10;

	D3DXVECTOR3 QuakePos = { _HP_GAUGE_CIRCLE_POS.x + quakeValue_X,_HP_GAUGE_CIRCLE_POS.y + quakeValue_Y,0.0f };
	D3DXVECTOR3 QuakePosV = { _HP_GAUGE_CIRCLE_POS.x + quakeValue_X + _GAUGE_RADIUS,_HP_GAUGE_CIRCLE_POS.y + quakeValue_Y + _GAUGE_RADIUS,0.0f };

	m_pClockHands->SetPos(QuakePosV);
	m_pClockBack->SetPos(QuakePosV);
	SetPos(QuakePos);
}

//==========================================================================================
//�~�`�Q�[�W�w�i�̏���������
//==========================================================================================
void CClockBack::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_CLOCK_DECO.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CClockBack::Draw()
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
CClockBack* CClockBack::Create()
{
	CClockBack* gauge = new CClockBack;
	D3DXVECTOR3 pos = {
		_HP_GAUGE_CIRCLE_POS.x + _GAUGE_RADIUS,
		_HP_GAUGE_CIRCLE_POS.y + _GAUGE_RADIUS,
		0.0f
	};
	gauge->SetPolygonParam(pos, _GAUGE_RADIUS * 2, _GAUGE_RADIUS * 2, { 1.0f,1.0f,1.0f,1.0f });
	gauge->Init();

	return gauge;
}

//==========================================================================================
//�~�`�Q�[�W�w�i�̏���������
//==========================================================================================
void CClockHands::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_CLOCK_HANDS.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CClockHands::Draw()
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
CClockHands* CClockHands::Create()
{
	CClockHands* gauge = new CClockHands;
	D3DXVECTOR3 pos = {
		_HP_GAUGE_CIRCLE_POS.x + _GAUGE_RADIUS,
		_HP_GAUGE_CIRCLE_POS.y + _GAUGE_RADIUS,
		0.0f
	};
	gauge->SetPolygonParam(pos, _GAUGE_RADIUS * 2, _GAUGE_RADIUS * 2, { 1.0f,1.0f,1.0f,1.0f });
	gauge->Init();

	return gauge;
}