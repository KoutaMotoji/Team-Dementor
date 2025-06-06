//===============================================================================
//
//  タイトルシーン(title.cpp)
//								制作：元地弘汰
// 
//===============================================================================

#include "manager.h"


#include "title.h"
#include "fade.h"

namespace AnimPoint
{

}

namespace 
{
	D3DXVECTOR3 LogoPos = {320.0f,150.0f, 0.0f};
	D3DXVECTOR2 LogoSize = { 300.0f,300.0f };

}


CTitle::CTitle(): m_bNowAnim(false), m_AnimTimer(0), m_nSelect(0)
{
}

CTitle::~CTitle()
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
HRESULT CTitle::Init()
{
	CScene::Init();
	CTitleBG::Create();
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//==========================================================================================
//終了処理
//==========================================================================================
void CTitle::Uninit()
{
	CScene::Uninit();
}

//==========================================================================================
//更新処理
//==========================================================================================
void CTitle::Update()
{

	if (CManager::GetInstance()->GetKeyboard()->CKeyboard::GetTrigger(DIK_RETURN) || CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_A)) 
	{
		CManager::GetInstance()->GetFade()->SetFade(CFade::FADE_IN, CScene::MODE_GAME);
	}
	CScene::Update();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CTitle::Draw()
{
	CScene::Draw();
}

//==========================================================================================
//タイトルアニメーション処理
//==========================================================================================
void CTitle::UpdateAnim(int m)
{

	
}

//==========================================================================================
//枠の初期化処理
//==========================================================================================
void CTitleBG::Init()
{
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\burger.png");
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//枠の生成処理
//==========================================================================================
CTitleBG* CTitleBG::Create()
{
	CTitleBG* bg = new CTitleBG;

	bg->SetPolygonParam({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, LogoSize.x, LogoSize.y);
	bg->Init();

	return bg;
}
