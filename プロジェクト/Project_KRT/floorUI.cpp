//===============================================================================
//
//  フロアUI処理(floorUI.cpp)
//					制作：大竹熙
// 
//===============================================================================

#include "floorUI.h"
#include "manager.h"
#include "field_manager.h"

namespace
{
	D3DXVECTOR2 FloorSize = { 50.0f, 100.0f };
	D3DXVECTOR2 FloorHyphenSize = { 50.0f, 50.0f };
	D3DXVECTOR2 FloorNumberSize = { 75.0f, 100.0f };
	D3DXVECTOR2 FloorTypeSize = { 75.0f, 100.0f };
}

int CBaseFloorUI::SaveScore = 0;

void CBaseFloorUI::Init()
{
	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
	CField_Manager::GetInstance()->RegistObj(this);
}

void CBaseFloorUI::Update()
{
	CObject2D::Update();
}

void CBaseFloorUI::SetFloorNumberUI()
{
	int nType = 1;
	int nValue = m_nTexPos;		//スコアをローカルにコピー
	int Num = 0;
	nType *= 10;			//桁数計算用の数値を設定
	Num = (nValue % nType * 10) / nType;	//指定桁数の数字を抜き出す

	CObject2D::SetAnim({ (float)Num,CObject2D::GetAnim().y });
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
	CField_Manager::GetInstance()->RegistObj(this);
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
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\F.png");
	floorUI->BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	return floorUI;
}
 
void CFloorHyphenUI::Init()
{
	CObject2D::Init();
	CField_Manager::GetInstance()->RegistObj(this);
}

void CFloorHyphenUI::Update()
{
	CObject2D::Update();
}

void CFloorHyphenUI::Draw()
{
	CObject2D::Draw();
}

CFloorHyphenUI* CFloorHyphenUI::Create(D3DXVECTOR3 pos)
{
	CFloorHyphenUI* floorhyphenUI = new CFloorHyphenUI;

	floorhyphenUI->SetPolygonParam(pos, FloorHyphenSize.y, FloorHyphenSize.x);
	floorhyphenUI->Init();
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\-.png");
	floorhyphenUI->BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	return floorhyphenUI;
}
 
void CFloorNumberUI::Init()
{
	CObject2D::Init();
	CField_Manager::GetInstance()->RegistObj(this);
}

void CFloorNumberUI::Update()
{
	CObject2D::Update();
}

void CFloorNumberUI::Draw()
{
	CObject2D::Draw();
}

CFloorNumberUI* CFloorNumberUI::Create(D3DXVECTOR3 pos, int i)
{
	CFloorNumberUI* FloorNumberUI = new CFloorNumberUI;

	FloorNumberUI->SetPolygonParam(pos, FloorNumberSize.y, FloorNumberSize.x);
	FloorNumberUI->Init();
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\number000.png");
	FloorNumberUI->BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 10, 1);
	FloorNumberUI->AddScore(i);

	return FloorNumberUI;
}

void CFloorTypeUI::Init()
{
	CObject2D::Init();
	CField_Manager::GetInstance()->RegistObj(this);
}

void CFloorTypeUI::Update()
{
	CObject2D::Update();
}

void CFloorTypeUI::Draw()
{
	CObject2D::Draw();
}

CFloorTypeUI* CFloorTypeUI::Create(D3DXVECTOR3 pos, int i)
{
	CFloorTypeUI* FloorTypeUI = new CFloorTypeUI;

	FloorTypeUI->SetPolygonParam(pos, FloorTypeSize.y, FloorTypeSize.x);
	FloorTypeUI->Init();
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\AB.png");
	FloorTypeUI->BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 2, 1);
	FloorTypeUI->AddScore(i);

	return FloorTypeUI;
}

