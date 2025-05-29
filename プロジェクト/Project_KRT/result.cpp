//===============================================================================
//
//  ƒŠƒUƒ‹ƒgƒV[ƒ“(result.cpp)
//								§ìFŒ³’nO‘¿
// 
//===============================================================================

#include "manager.h"
#include "fade.h"
#include "object.h"
#include "result.h"

namespace 
{
	D3DXVECTOR3 LogoPos = { 320.0f,150.0f, 0.0f };
	D3DXVECTOR2 LogoSize = { 300.0f,300.0f };

}

CResult::CResult()
{
	
}

CResult::~CResult()
{

}

//==========================================================================================
//‰Šú‰»ˆ—
//==========================================================================================
HRESULT CResult::Init()
{
	CScene::Init();
	CResultBG::Create();
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);

	return S_OK;
}

//==========================================================================================
//I—¹ˆ—
//==========================================================================================
void CResult::Uninit()
{

	CScene::Uninit();
}

//==========================================================================================
//XVˆ—
//==========================================================================================
void CResult::Update()
{
	if (CManager::GetInstance()->GetKeyboard()->CKeyboard::GetTrigger(DIK_RETURN) || CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_A))
	{

		CManager::GetInstance()->GetFade()->SetFade(CFade::FADE_IN, CScene::MODE_TITLE);
		
	}

	CScene::Update();
}

//==========================================================================================
//•`‰æˆ—
//==========================================================================================
void CResult::Draw()
{
	CScene::Draw();
}

//==========================================================================================
//˜g‚Ì‰Šú‰»ˆ—
//==========================================================================================
void CResultBG::Init()
{
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\hotdog.png");
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//˜g‚Ì¶¬ˆ—
//==========================================================================================
CResultBG* CResultBG::Create()
{
	CResultBG* bg = new CResultBG;

	bg->SetPolygonParam({SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f}, LogoSize.x, LogoSize.y);
	bg->Init();

	return bg;
}
