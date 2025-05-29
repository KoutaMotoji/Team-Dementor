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

#include "game.h"

#include "floor.h"


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

	CG_Gorira::Create({ 0.0f,300.0f,500.0f });
	CPlayerMask::Create();

	return S_OK;
}

//==========================================================================================
//�I������
//==========================================================================================
void CGame::Uninit()
{
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
		CManager::GetInstance()->GetFade()->SetFade(CFade::FADE_IN, CScene::MODE_MAPEDIT);
		return;
	}
#endif // _DEBUG
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