//===============================================================================
//
//  タイトルシーン(title.cpp)
//								制作：元地弘汰
// 
//===============================================================================

#include "manager.h"

#include "mesh_cylinder.h"
#include "title_obj.h"
#include "title.h"
#include "fade.h"

namespace AnimPoint
{

}

namespace
{
	D3DXVECTOR3 LogoPos = { 260.0f,150.0f, 0.0f };
	D3DXVECTOR2 LogoSize = { 450.0f,280.0f };

	D3DXVECTOR3 ButtonPos = { SCREEN_WIDTH * 0.5f,550.0f, 0.0f };
	D3DXVECTOR2 ButtonSize = { 350.0f,80.0f };
	float SWAP_SPEED = 0.02f;
}


CTitle::CTitle() : m_bNowAnim(false), m_AnimTimer(0), m_nSelect(0)
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
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
	CT_Graound::Create();
	CT_Player::Create();
	CMeshCylinder::Create({ 0.0f,1000.0f,0.0f });
	D3DXVECTOR3 posA, posB;
	posA = { 300.0f,-100.0f,-200.0f };
	posB = { 120.0f,-20.0f,-30.0f };
	CManager::GetInstance()->GetCamera()->SetFreeCam(posA, posB, 120, false);
	CTitleBG::Create();
	CTitleButton::Create();
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
	++m_AnimTimer;
	if (m_AnimTimer > 120)
	{
		--m_AnimTimer;
		D3DXVECTOR3 posA, posB;
		posA = { 300.0f,-100.0f,-200.0f };
		posB = { 120.0f,-20.0f,-30.0f };
		CManager::GetInstance()->GetCamera()->SetFreeCam(posA, posB, 1, true);
	}
	//CManager::GetInstance()->GetCamera()->SetFreeCam({ 0.0f,0.0f,0.0f }, { -200.0f,-100.0f,-2000.0f }, 120);

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
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\titleLOGO.png");
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//枠の初期化処理
//==========================================================================================
void CTitleBG::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//テクスチャ拡大時に色を近似値にする
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//ステンシルマスクの設定時に無効化したZバッファをもとにもどす
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//アルファテスト設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//テクスチャ拡大時の色を線形補間
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//==========================================================================================
//枠の生成処理
//==========================================================================================
CTitleBG* CTitleBG::Create()
{
	CTitleBG* bg = new CTitleBG;

	bg->SetPolygonParam({ LogoPos.x,LogoPos.y,0.0f }, LogoSize.y, LogoSize.x);
	bg->Init();

	return bg;
}
//==========================================================================================
//枠の初期化処理
//==========================================================================================
void CTitleButton::Init()
{
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\PRESSA.png");
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//枠の初期化処理
//==========================================================================================
void CTitleButton::Draw()
{
	float speed = SWAP_SPEED;

	if (m_LocalCol.a <= 0.0f ||
		m_LocalCol.a >= 1.0f)
	{
		m_bColSwitch = m_bColSwitch ? false : true;
	}
	if (m_bSpeed)
	{
		speed *= 10;
	}
	if (m_bColSwitch)
	{
		m_LocalCol.a -= speed;
	}
	else
	{
		m_LocalCol.a += speed;
	}
	CObject2D::SetColor(m_LocalCol);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//テクスチャ拡大時に色を近似値にする
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//ステンシルマスクの設定時に無効化したZバッファをもとにもどす
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//アルファテスト設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//テクスチャ拡大時の色を線形補間
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//==========================================================================================
//枠の生成処理
//==========================================================================================
CTitleButton* CTitleButton::Create()
{
	CTitleButton* bg = new CTitleButton;

	bg->SetPolygonParam({ ButtonPos.x,ButtonPos.y,0.0f }, ButtonSize.y, ButtonSize.x);
	bg->Init();

	return bg;
}
