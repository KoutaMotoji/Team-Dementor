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
	m_pScore = CScore::Create({ 800.0f,460.0f,0.0f }, 6, 60.0f, 90.0f);
	m_ptime_m = CScore::Create({ 110.0f,230.0f,0.0f }, 1, 60.0f, 100.0f);
	m_ptime_s = CScore::Create({ 260.0f,230.0f,0.0f }, 2, 60.0f, 100.0f);
	m_pkill = CScore::Create({ 700.0f,305.0f,0.0f }, 2, 40.0f, 60.0f);
	CManager::GetInstance()->GetGameInfo()->TimeDigit();
	m_pScore->AddScore(CManager::GetInstance()->GetGameInfo()->GetResultScore(true));
	int minuts = CManager::GetInstance()->GetGameInfo()->GetTimeMS() / 100;
	int second = CManager::GetInstance()->GetGameInfo()->GetTimeMS() % 100;

	m_ptime_m->AddScore(minuts);
	m_ptime_s->AddScore(second);

	m_pkill->AddScore(CManager::GetInstance()->GetGameInfo()->GetEnemyKillCnt());

	return S_OK;
}

//==========================================================================================
//終了処理
//==========================================================================================
void CGameover::Uninit()
{
	if (m_pScore != nullptr) {
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = nullptr;
	}
	if (m_ptime_m != nullptr) {
		m_ptime_m->Uninit();
		delete m_ptime_m;
		m_ptime_m = nullptr;
	}
	if (m_ptime_s != nullptr) {
		m_ptime_s->Uninit();
		delete m_ptime_s;
		m_ptime_s = nullptr;
	}
	if (m_pkill != nullptr) {
		m_pkill->Uninit();
		delete m_pkill;
		m_pkill = nullptr;
	}
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

