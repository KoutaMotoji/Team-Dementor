//===============================================================================
//
//  フロアUI処理(floorUI.cpp)
//					制作：大竹熙
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

int CFloorNumberUI::SaveScore = 0;
int CFloorNumberUI::m_nTexPos = 0;

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
 
CFloorNumberUI::CFloorNumberUI()
{

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

void CFloorNumberUI::SetFloorNumberUI()
{
	int nType = 1;
	int nValue = m_nTexPos;		//スコアをローカルにコピー
	int Num = 0;
	nType *= 10;			//桁数計算用の数値を設定
	Num = (nValue % nType * 10) / nType;	//指定桁数の数字を抜き出す

	CObject2D::SetAnim({ (float)Num,CObject2D::GetAnim().y });
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
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\AB-.png");
	FloorTypeUI->BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	return FloorTypeUI;
}

