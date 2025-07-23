//===============================================================================
//
//  フィールド管理クラス(field_manager.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "manager.h"
#include "field_manager.h"
#include "stage1_boss.h"

#include "floor_stone.h"
#include "floorUI.h"

namespace
{
	//画面切り替え
	D3DXVECTOR3 DISSOLVE_POS = {
		SCREEN_WIDTH * 0.5f,
		-SCREEN_HEIGHT * 1.5f,
		0.0f
	};
	D3DXVECTOR3 DISSOLVE_SIZE = {
		SCREEN_WIDTH,
		SCREEN_HEIGHT * 3,
		0.0f
	};
	float DISSOLVE_SPEED = 50.0f;
}
std::shared_ptr<CField_Manager> CField_Manager::_instance = nullptr;

void CField_Manager::Init() {
	if (m_FieldDissolve != nullptr)return;
	m_FieldDissolve = FieldDissolve::Create();
}
void CField_Manager::Uninit() {
	if (m_FieldDissolve == nullptr)return;
	m_FieldDissolve->Uninit();
	m_FieldDissolve = nullptr;
	for (auto& e : m_vecFieldObj)
	{
		if (e != nullptr)
		{
			e->Release();
			e = nullptr;
		}
	}
	m_vecFieldObj.clear();
};
void CField_Manager::Update()
{
	m_vecFieldObj;
	if (!m_bActibateManager)return;

	//ディゾルブが半分に到達しているか確認
	if (!m_FieldDissolve->GetReach())return;


	for (auto& e : m_vecFieldObj)
	{
		if (e != nullptr)
		{
			e->Release();
			e = nullptr;
		}
	}
	m_vecFieldObj.clear();
	//次のマップを生成(今は仮、後々対応したファイル読み込みなどに置き換え)
	CMeshGround::Create({ 0.0f,0.0f,0.0f }, 0);
	CG_Gorira::Create({ 0.0f,300.0f,500.0f });

	//フロアのUI生成
	CFloorUI::Create({ 1050.0f, 75.0f, 0.0f });
	m_FloorNumberUI = CFloorNumberUI::Create({ 1110.0f, 75.0f, 0.0f },1);
	CFloorHyphenUI::Create({ 1160.0f, 75.0f, 0.0f });
	m_FloorTypeUI = CFloorTypeUI::Create({ 1225.0f,75.0f,0.0f },1);

	m_FieldDissolve->RestartDissolve();
	m_bActibateManager = false;
}

//外部からオブジェクト再配置スタート用の関数
void CField_Manager::SetField()
{
	m_FieldDissolve->StartDissolve();
	m_bActibateManager = true;
}

void FieldDissolve::Init()
{
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\fieldDissolve_nega.png");
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);
	CObject2D::Init();
}

void FieldDissolve::Update()
{
	if (m_bUse)
	{
		CObject2D::AddPos({ 0.0f,DISSOLVE_SPEED,0.0f });
	}
	CObject2D::Update();
	if ((CObject2D::GetPos().y >= (SCREEN_HEIGHT * 0.5f ) + DISSOLVE_SPEED && CObject2D::GetPos().y <= (SCREEN_HEIGHT * 0.5f) + (DISSOLVE_SPEED * 2)))
	{
		m_bReachHalf = true;
	}
	if (CObject2D::GetPos().y >= SCREEN_HEIGHT * 3)
	{
		m_bReachHalf = m_bDraw = m_bUse = false;
	}
}
void FieldDissolve::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	if (m_bDraw)
	{
		CObject2D::Draw();
	}
}

FieldDissolve* FieldDissolve::Create()
{
	FieldDissolve* pDisolve = new FieldDissolve;
	pDisolve->SetPolygonParam(DISSOLVE_POS, DISSOLVE_SIZE.y, DISSOLVE_SIZE.x);
	pDisolve->Init();
	return pDisolve;
}

//=================================================================================================================
//ディゾルブのスタンダード・リスタート

void FieldDissolve::StartDissolve()
{
	m_bReachHalf = false;
	m_bDraw = true;
	m_bUse = true;
	CObject2D::SetPos(DISSOLVE_POS);
}
void FieldDissolve::RestartDissolve()
{
	m_bReachHalf = false;
	m_bDraw = true;
	CObject2D::SetPos({SCREEN_WIDTH*0.5f,SCREEN_HEIGHT*0.5f,0.0f});
}
//=================================================================================================================
