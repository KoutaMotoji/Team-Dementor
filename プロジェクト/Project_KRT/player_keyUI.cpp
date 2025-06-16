//===============================================================================
//
//  プレイヤーボタンUI処理(player_keyUI.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "player_keyUI.h"
#include "manager.h"

namespace
{
	D3DXVECTOR2 BarSize = {220.0f,5.0f};
	D3DXVECTOR3 BarPos = {220.0f,300.0f,0.0f};
	D3DXVECTOR2 ButtonSize = { 220.0f / 3,220.0f / 3 };

	D3DXCOLOR BarColNormal = { 1.0f,1.0f,1.0f,1.0f };
	D3DXCOLOR BarColHalf = { 1.0f,0.0f,0.0f,1.0f };
}

//==========================================================================================
//ボタンUIの初期化処理
//==========================================================================================
void CCTBarUI::Init()
{
	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
	CObject2D::SetColor(BarColNormal);
}

//==========================================================================================
//ボタンUIの初期化処理
//==========================================================================================
void CCTBarUI::Update()
{
	--m_GaugeValue;
	if (m_GaugeValue < 0)	{
		m_EndFrag = true;
		return;
	}

	CObject2D::SetGauge(m_GaugeValue);
	CObject2D::Update();
}

//==========================================================================================
//ボタンUIの初期化処理
//==========================================================================================
void CCTBarUI::Draw()
{
	if (m_GaugeValue <= m_MaxValue * 0.5f) {
		CObject2D::SetColor(BarColHalf);
	}
	else if (m_GaugeValue > m_MaxValue * 0.5f)
	{
		CObject2D::SetColor(BarColNormal);
	}
	CObject2D::Draw();
}

//==========================================================================================
//ボタンUIの生成処理
//==========================================================================================
CCTBarUI* CCTBarUI::Create(int MaxValue)
{
	CCTBarUI* ui = new CCTBarUI;

	ui->SetPolygonParam(BarPos, BarSize.y, BarSize.x, MaxValue,true);
	ui->Init();
	ui->m_GaugeValue = MaxValue;
	ui->m_MaxValue = MaxValue;
	return ui;
}

//==========================================================================================
//ボタンUIの初期化処理
//==========================================================================================
void CButtonUI::Init()
{
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\burger.png");
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//ボタンUIの初期化処理
//==========================================================================================
void CButtonUI::Update()
{
	CObject2D::Update();
}

//==========================================================================================
//ボタンUIの生成処理
//==========================================================================================
CButtonUI* CButtonUI::Create(D3DXVECTOR3 pos)
{
	CButtonUI* ui = new CButtonUI;

	ui->SetPolygonParam(pos, ButtonSize.y, ButtonSize.x);
	ui->Init();
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\ButtonY.png");
	ui->BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	return ui;
}

//==========================================================================================
//ボタンUIの生成処理
//==========================================================================================
CButtonUI* CButtonUI::Create(D3DXVECTOR3 pos,int s)
{
	CButtonUI* ui = new CButtonUI;

	ui->SetPolygonParam(pos, ButtonSize.y, ButtonSize.x);
	ui->Init();
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\ButtonX.png");
	ui->BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	return ui;
}