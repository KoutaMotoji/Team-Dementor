//===============================================================================
//
//  �Q�[���V�[��(game.cpp)
//								����F���n�O��
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

CGame::CGame()
{
}

CGame::~CGame()
{

}

//==========================================================================================
//����������
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


	CPlayerMask::Create();
	CField_Manager::GetInstance()->Init();
	CPlayerObserver::GetInstance()->PlayerSearch();
	return S_OK;
}

//==========================================================================================
//�I������
//==========================================================================================
void CGame::Uninit()
{
	CField_Manager::GetInstance()->Uninit();
	CPlayerObserver::GetInstance()->PlayerObsDestroy();
	CScene::Uninit();
}

//==========================================================================================
//�X�V����
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
	if (CManager::GetInstance()->GetKeyboard()->CKeyboard::GetTrigger(DIK_F))
	{
		CFloorUI::Create({ 1150.0f, 75.0f, 0.0f });
		CFloorNumberUI::Create({ 900.0f, 75.0f, 0.0f });
	}
#endif // _DEBUG
	CField_Manager::GetInstance()->Update();
	CScene::Update();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CGame::Draw()
{
	CScene::Draw();
}

//==========================================================================================
//�i�F�p�̖؂������_���Őݒu���鏈��
//==========================================================================================
void CGame::MakeRandTree()
{
}