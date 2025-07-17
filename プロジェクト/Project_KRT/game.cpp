//===============================================================================
//
//  ゲームシーン(game.cpp)
//								制作：元地弘汰
// 
//===============================================================================

#include "manager.h"
#include "fade.h"
#include "object.h"
#include "xxx_player.h"
#include "floor_stone.h"
#include "mesh_cylinder.h"
#include "stage1_boss.h"
#include "stencile_mask.h"
#include "area_move_gate.h"
#include "player_observer.h"


#include "field_manager.h"

#include "game.h"

#include "floor.h"
#include "floorUI.h"
#include "score.h"

CGame::CGame()
{
}

CGame::~CGame()
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
HRESULT CGame::Init()
{
	CScene::Init();
	CManager::GetInstance()->GetCamera()->SetCameraHeigjt(400.0f);
	CManager::GetInstance()->GetCamera()->SetCameraDistance(1200.0f);

	CMeshGround::Create({ 0.0f,0.0f,0.0f });
	CPlayerX::Create({ 200.0f,1000.0f,0.0f });
	CMeshCylinder::Create({ 0.0f,0.0f,0.0f });
	CAreaGate::Create({ 0.0f,0.0f,700.0f });
	CFloorUI::Create({ 1050.0f, 75.0f, 0.0f });
	m_FloorNumberUI = CFloorNumberUI::Create({ 1110.0f, 75.0f, 0.0f });
	CFloorHyphenUI::Create({ 1160.0f, 75.0f, 0.0f });
	m_FloorTypeUI = CFloorTypeUI::Create({ 1225.0f,75.0f,0.0f });

	CPlayerMask::Create();
	CField_Manager::GetInstance()->Init();
	CPlayerObserver::GetInstance()->PlayerSearch();

	return S_OK;
}

//==========================================================================================
//終了処理
//==========================================================================================
void CGame::Uninit()
{
	CField_Manager::GetInstance()->Uninit();
	CPlayerObserver::GetInstance()->PlayerObsDestroy();
	CScene::Uninit();
}

//==========================================================================================
//更新処理
//==========================================================================================
void CGame::Update()
{
#if _DEBUG

	if (CManager::GetInstance()->GetKeyboard()->CKeyboard::GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetFade()->SetFade(CFade::FADE_IN, CScene::MODE_RESULT);
	}
	if (CManager::GetInstance()->GetKeyboard()->CKeyboard::GetTrigger(DIK_F3))
	{
		CField_Manager::GetInstance()->SetField();
	}
	if (CManager::GetInstance()->GetKeyboard()->CKeyboard::GetTrigger(DIK_U))
	{
		m_FloorNumberUI->AddScore(1);
	}
	if (CManager::GetInstance()->GetKeyboard()->CKeyboard::GetTrigger(DIK_Y))
	{
		m_FloorTypeUI->AddScore(1);
	}
#endif // _DEBUG
	CField_Manager::GetInstance()->Update();
	CScene::Update();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CGame::Draw()
{
	CScene::Draw();
}

//==========================================================================================
//景色用の木をランダムで設置する処理
//==========================================================================================
void CGame::MakeRandTree()
{
}