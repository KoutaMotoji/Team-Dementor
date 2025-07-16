//===============================================================================
//
//  プレイヤーのUI表示(player_UI.cpp)
//								制作：元地弘汰
// 
//===============================================================================

#include "player_UI.h"

#include "player_observer.h"
#include "manager.h"

namespace
{
	std::string _FILENAME_HP_GAUGE = "data\\TEXTURE\\playerHP.png";
	std::string _FILENAME_HP_FRAME = "data\\TEXTURE\\playerHPframe.png";
	std::string _FILENAME_HP_BACK = "data\\TEXTURE\\playerHPback.png";
	std::string _FILENAME_HP_DECO = "data\\TEXTURE\\playerHPdeco.png";
	std::string _FILENAME_HP_CIRCLEGAUGE = "data\\TEXTURE\\UI000.png";


	D3DXVECTOR2 _HP_GAUGE_SIZE = {400.0f,70.0f};
	D3DXVECTOR2 _HP_GAUGE_DECO_SIZE = {600.0f,80.0f};
	D3DXVECTOR3 _HP_GAUGE_POS = { (_HP_GAUGE_DECO_SIZE.x * 0.5f) - 50.0f,SCREEN_HEIGHT - (_HP_GAUGE_DECO_SIZE.y * 0.5f),0.0f };
	D3DXVECTOR3 _HP_GAUGE_DECO_POS = { _HP_GAUGE_POS.x + 50.0f,_HP_GAUGE_POS.y,0.0f };
	D3DXVECTOR3 _HP_GAUGE_CIRCLE_POS = { 1000.0f,500.0f,0.0f };

	float _GAUGE_RADIUS = 100.0f;

	D3DXCOLOR _GAUGE_COLOR = { 0.0f,1.0f,0.2f,1.0f };
}

CGaugeLife::CGaugeLife(int nPriority) :CObject2D(nPriority)
{

}

CGaugeLife::~CGaugeLife()
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
void CGaugeLife::Init()
{
	//テクスチャの登録・割り当て
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_HP_GAUGE.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CGaugeLiFrame::Create(CObject2D::GetPos(), _HP_GAUGE_SIZE.x, _HP_GAUGE_SIZE.y);
	CGaugeLiBack::Create(CObject2D::GetPos(), _HP_GAUGE_SIZE.x, _HP_GAUGE_SIZE.y);
	CGaugeLiDeco::Create();
	CGaugeCircle::Create();
	CGaugeCircleDeco::Create();

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
	CObject2D::SetColor(_GAUGE_COLOR);
}

//==========================================================================================
//終了処理
//==========================================================================================
void CGaugeLife::Uninit()
{
	CObject2D::Uninit();
}

//==========================================================================================
//更新処理
//==========================================================================================
void CGaugeLife::Update()
{
	CGaugeLife::SetGauge();
	CObject2D::Update();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CGaugeLife::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	//テクスチャ拡大時に色を近似値にする
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//アルファテスト設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//テクスチャ拡大時の色を線形補間
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//==========================================================================================
//生成処理
//==========================================================================================
CGaugeLife* CGaugeLife::Create(int nMaxGauge)
{
	CGaugeLife* gauge = new CGaugeLife;
	gauge->SetPolygonParam(_HP_GAUGE_POS, _HP_GAUGE_SIZE.y, _HP_GAUGE_SIZE.x, nMaxGauge, false);
	gauge->Init();
	return gauge;
}

//==========================================================================================
//数値を取得して反映
//==========================================================================================
void CGaugeLife::SetGauge()
{
	int nNowGauge = CPlayerObserver::GetInstance()->GetPlayerLife();
	CObject2D::SetGauge(nNowGauge);
}

//----------------------------------------------------------------------------------------------------------------------------------
//枠・後ろ・装飾設定用

//==========================================================================================
//枠の初期化処理
//==========================================================================================
void CGaugeLiFrame::Init()
{
	//テクスチャの登録・割り当て
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_HP_FRAME.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CGaugeLiFrame::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	//テクスチャ拡大時に色を近似値にする
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
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
CGaugeLiFrame* CGaugeLiFrame::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CGaugeLiFrame* gauge = new CGaugeLiFrame;
	gauge->SetPolygonParam(pos, fHeight, fWidth, { 1.0f,1.0f,1.0f,1.0f });
	gauge->Init();
	return gauge;
}

//==========================================================================================
//後ろ側の初期化処理
//==========================================================================================
void CGaugeLiBack::Init()
{
	//テクスチャの登録・割り当て
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_HP_BACK.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CGaugeLiBack::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//テクスチャ拡大時に色を近似値にする
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//アルファテスト設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//テクスチャ拡大時の色を線形補間
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//==========================================================================================
//後ろ側の生成処理
//==========================================================================================
CGaugeLiBack* CGaugeLiBack::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CGaugeLiBack* gauge = new CGaugeLiBack;
	gauge->SetPolygonParam(pos, fHeight, fWidth, { 1.0f,1.0f,1.0f,1.0f });
	gauge->Init();
	return gauge;
}

//==========================================================================================
//HP装飾の初期化処理
//==========================================================================================
void CGaugeLiDeco::Init()
{
	//テクスチャの登録・割り当て
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_HP_DECO.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CGaugeLiDeco::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	
	//テクスチャ拡大時に色を近似値にする
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	//アルファテスト設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//テクスチャ拡大時の色を線形補間
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//==========================================================================================
//HP装飾の生成処理
//==========================================================================================
CGaugeLiDeco* CGaugeLiDeco::Create()
{
	CGaugeLiDeco* gauge = new CGaugeLiDeco;

	gauge->SetPolygonParam(_HP_GAUGE_DECO_POS, _HP_GAUGE_DECO_SIZE.y, _HP_GAUGE_DECO_SIZE.x, { 1.0f,1.0f,1.0f,1.0f });
	gauge->Init();

	return gauge;
}

//==========================================================================================
//円形ゲージの初期化処理
//==========================================================================================
void CGaugeCircle::Init()
{
	//テクスチャの登録・割り当て
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_HP_CIRCLEGAUGE.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx));

	CObject::SetType(TYPE_2D_UI);
	CObjectCircleGauge::Init();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CGaugeCircle::Update()
{
	int life = 1000 - CPlayerObserver::GetInstance()->GetPlayerLife();
	float nNowGauge = (float)life / 1000.0f;

	CObjectCircleGauge::SetGaugePercent(nNowGauge);

	CObjectCircleGauge::Update();

}


//==========================================================================================
//描画処理
//==========================================================================================
void CGaugeCircle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();


	CObjectCircleGauge::Draw();
}

//==========================================================================================
//円形ゲージの生成処理
//==========================================================================================
CGaugeCircle* CGaugeCircle::Create()
{
	CGaugeCircle* gauge = new CGaugeCircle;

	gauge->SetPolygonParam(_HP_GAUGE_CIRCLE_POS, _GAUGE_RADIUS);
	gauge->Init();

	return gauge;
}

//==========================================================================================
//HP装飾の初期化処理
//==========================================================================================
void CGaugeCircleDeco::Init()
{
	//テクスチャの登録・割り当て
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(_FILENAME_HP_CIRCLEGAUGE.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), 1, 1);

	CObject::SetType(TYPE_2D_UI);
	CObject2D::Init();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CGaugeCircleDeco::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//テクスチャ拡大時に色を近似値にする
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	//アルファテスト設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	//テクスチャ拡大時の色を線形補間
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//==========================================================================================
//HP装飾の生成処理
//==========================================================================================
CGaugeCircleDeco* CGaugeCircleDeco::Create()
{
	CGaugeCircleDeco* gauge = new CGaugeCircleDeco;
	D3DXVECTOR3 pos = {
		_HP_GAUGE_CIRCLE_POS.x + _GAUGE_RADIUS,
		_HP_GAUGE_CIRCLE_POS.y + _GAUGE_RADIUS,
		0.0f
	};
	gauge->SetPolygonParam(pos, _GAUGE_RADIUS * 2, _GAUGE_RADIUS * 2, { 1.0f,1.0f,1.0f,0.4f });
	gauge->Init();

	return gauge;
}