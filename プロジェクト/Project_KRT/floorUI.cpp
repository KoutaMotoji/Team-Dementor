//===============================================================================
//
//  ƒtƒƒAUIˆ—(floorUI.cpp)
//					§ìF‘å’|ê¤
// 
//===============================================================================

#include "floorUI.h"
#include "manager.h"

namespace
{
	D3DXVECTOR2 FloorSize = { 200.0f, 100.0f };
	D3DXVECTOR2 FloorNumberSize = { 50.0f, 100.0f };
	D3DXVECTOR2 FloorTypeSize = { 100.0f, 100.0f };
}

void CBaseFloorUI::Init()
{
	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

void CBaseFloorUI::Update()
{
	CObject2D::Update();
}

CBaseFloorUI* CBaseFloorUI::Create(D3DXVECTOR3 pos)
{
	CBaseFloorUI* basefloorUI = new CBaseFloorUI;

	basefloorUI->SetPolygonParam(pos, FloorSize.y, FloorSize.x);
	basefloorUI->Init();

	return basefloorUI;
}

void CFloorUI::Init()
{
	CObject2D::Init();
}

void CFloorUI::Update()
{
	CObject2D::Update();
}

void CFloorUI::Draw()
{
	CObject2D::Draw();
}

CFloorUI* CFloorUI::Create(D3DXVECTOR3 pos)
{
	CFloorUI* floorUI = new CFloorUI;

	floorUI->SetPolygonParam(pos, FloorSize.y, FloorSize.x);
	floorUI->Init();
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\FAB-.png");
	floorUI->BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	return floorUI;
}

void CFloorNumberUI::Init()
{
	CObject2D::Init();
}

void CFloorNumberUI::Update()
{
	CObject2D::Update();
}

void CFloorNumberUI::Draw()
{
	CObject2D::Draw();
}

void CFloorNumberUI::SetFloorNumberUI(int nfloornumber)
{
	int aPosTexU;      //ŠeŒ…‚Ì”Žš‚ðŠi”[
	m_FloorNumber = nfloornumber;
	int nTemp = m_FloorNumber;

	aPosTexU = (nTemp % 10);
	nTemp /= 10;
	SetTexPos(aPosTexU);
}

CFloorNumberUI* CFloorNumberUI::Create(D3DXVECTOR3 pos)
{
	CFloorNumberUI* FloorNumberUI = new CFloorNumberUI;

	FloorNumberUI->SetPolygonParam(pos, FloorNumberSize.y, FloorNumberSize.x);
	FloorNumberUI->Init();
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\number000.png");
	FloorNumberUI->BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 10, 1);

	return FloorNumberUI;
}

void CFloorTypeUI::Init()
{
	CObject2D::Init();
}

void CFloorTypeUI::Update()
{
	CObject2D::Update();
}

void CFloorTypeUI::Draw()
{
	CObject2D::Draw();
}

CFloorTypeUI* CFloorTypeUI::Create(D3DXVECTOR3 pos)
{
	CFloorTypeUI* FloorTypeUI = new CFloorTypeUI;

	FloorTypeUI->SetPolygonParam(pos, FloorTypeSize.y, FloorTypeSize.x);
	FloorTypeUI->Init();
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\FAB-.png");
	FloorTypeUI->BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	return FloorTypeUI;
}

