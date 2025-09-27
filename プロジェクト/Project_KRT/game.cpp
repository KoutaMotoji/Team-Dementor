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
#include "clock.h"
#include "enemy.h"

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
	CManager::GetInstance()->GetCamera()->DefuseFreeCam();

	CMeshGround::Create({ 0.0f,0.0f,0.0f });
	CPlayerX::Create({ 200.0f,1000.0f,0.0f });
	CMeshCylinder::Create({ 0.0f,0.0f,0.0f });
	CAreaGate::Create({ 0.0f,0.0f,700.0f });
	CFloorNumberUI::Create(1);
	CClock::GetInstance()->SetClock(240);
	CClockGauge::Create();
	CClock::GetInstance()->SetTimerStop(true);
	CPlayerMask::Create();
	CField_Manager::GetInstance()->Init();
	CPlayerObserver::GetInstance()->PlayerSearch();
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	CManager::GetInstance()->GetGameInfo()->AllReset();

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
#endif // _DEBUG
	CManager::GetInstance()->GetGameInfo()->TimeUpdate();
	CClock::GetInstance()->Update();
	CField_Manager::GetInstance()->Update();
	CScene::Update();
	CClock::GetInstance()->FrameFragDisable();
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