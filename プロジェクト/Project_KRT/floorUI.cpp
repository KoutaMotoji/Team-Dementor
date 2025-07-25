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
	std::string _FILENAME_FLOORUI = "data\\TEXTURE\\Floor.png";
	std::string _FILENAME_FLOORNUMBER = "data\\TEXTURE\\number000.png";


	D3DXVECTOR2 FloorSize = { 75.0f * 2.5, 75.0f };
	D3DXVECTOR2 FloorNumberSize = { 50.0f, 75.0f };

	D3DXVECTOR3 _FLOOR_UI_POS = { SCREEN_WIDTH - FloorSize.x * 0.5f - FloorNumberSize.x - 20.0f, 50.0f, 0.0f };
	D3DXVECTOR3 _FLOOR_UI_NUMBER_POS = { SCREEN_WIDTH - FloorNumberSize.x * 0.5f - 20.0f, 50.0f, 0.0f };

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

CFloorUI* CFloorUI::Create()
{
	CFloorUI* floorUI = new CFloorUI;

	floorUI->SetPolygonParam(_FLOOR_UI_POS, FloorSize.y, FloorSize.x);
	floorUI->Init();
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_FLOORUI.c_str());
	floorUI->BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	return floorUI;
}
 
 
void CFloorNumberUI::Init()
{
	CObject2D::Init();
	CField_Manager::GetInstance()->RegistObj(this);
	CFloorUI::Create();
}

void CFloorNumberUI::Update()
{
	CObject2D::Update();
}

void CFloorNumberUI::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//テクスチャ拡大時に色を近似値にする
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	CObject2D::Draw();

	//テクスチャ拡大時の色を線形補間
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

CFloorNumberUI* CFloorNumberUI::Create(int number)
{
	CFloorNumberUI* FloorNumberUI = new CFloorNumberUI;

	FloorNumberUI->SetPolygonParam(_FLOOR_UI_NUMBER_POS, FloorNumberSize.y, FloorNumberSize.x);
	FloorNumberUI->Init();
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_FLOORNUMBER.c_str());
	FloorNumberUI->BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 10, 1);
	FloorNumberUI->AddScore(number);

	return FloorNumberUI;
}
