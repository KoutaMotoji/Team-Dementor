//===============================================================================
//
//  ゲームオーバーシーン(gameover.cpp)
//								制作：元地弘汰
// 
//===============================================================================

#include "manager.h"
#include "fade.h"
#include "object.h"
#include "gameover.h"

#include"result_obj.h"

namespace
{
	D3DXVECTOR3 LogoPos = { 320.0f,150.0f, 0.0f };
	D3DXVECTOR2 LogoSize = { 300.0f,300.0f };

}

CGameover::CGameover()
{

}

CGameover::~CGameover()
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
HRESULT CGameover::Init()
{
	CScene::Init();
	CResultBG::Create();
	CR_Graound::Create();
	CResultBGBack::Create();
	CResultReview::Create(true);
	CResultRank::Create(0);
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);

	return S_OK;
}

//==========================================================================================
//終了処理
//==========================================================================================
void CGameover::Uninit()
{

	CScene::Uninit();
}

//==========================================================================================
//更新処理
//==========================================================================================
void CGameover::Update()
{
	if (CManager::GetInstance()->GetKeyboard()->CKeyboard::GetTrigger(DIK_RETURN) || CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_A))
	{

		CManager::GetInstance()->GetFade()->SetFade(CFade::FADE_IN, CScene::MODE_TITLE);

	}

	CScene::Update();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CGameover::Draw()
{
	CScene::Draw();
}

