//=====================================================================================================================
//
//体力ゲージの処理[health_gauge.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#include "health_gauge.h"
#include "manager.h"

//静的メンバ変数
const float HealthGauge::SUB_DAMAGE_RATIO = 0.001f;
const D3DXCOLOR HealthGauge::COLOR_HEALTH_FILL = { 0.25f, 1.0f, 0.25f, 1.0f };   //体力塗り部分の色
const D3DXCOLOR HealthGauge::COLOR_DAMAGE_FILL = { 1.0f, 0.25f, 0.25f, 1.0f };   //ダメージ塗り部分の色
const D3DXVECTOR2 HealthGauge::ADD_SIZE_BACKGROUND = { 20.0f, 15.0f };   //背景のサイズの加算値

//=====================================================================================================================
//初期化処理
//=====================================================================================================================
void HealthGauge::Init()
{
	//ゲージの背景のインスタンスを生成する
	this->m_pGaugeBackground = new GaugeBackground(this);
	this->m_pGaugeBackground->Init();   //初期化処理
	this->m_pGaugeBackground->SetAddSize(HealthGauge::ADD_SIZE_BACKGROUND);   //サイズの加算値を設定する

	//ダメージ部分のインスタンスを生成する
	this->m_pDamageFill = new DamageFill(this, HealthGauge::COLOR_DAMAGE_FILL);
	this->m_pDamageFill->Init();   //初期化処理

	//体力部分のインスタンスを生成する
	this->m_pHealthFill = new HealthFill(this, HealthGauge::COLOR_HEALTH_FILL);
	this->m_pHealthFill->Init();   //初期化処理

	//背景にテクスチャを設定する
	LPDIRECT3DTEXTURE9 pTexture = nullptr;   //設定するテクスチャ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();   //デバイスを取得
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\health_gauge_bg_00.png", &pTexture);   //テクスチャを読み込む
	this->m_pGaugeBackground->SetTexture(pTexture);
}

//=====================================================================================================================
//終了処理
//=====================================================================================================================
void HealthGauge::Uninit()
{
	//体力を確認する
	if (this->m_pHealthFill != nullptr)
	{//体力が生成されている場合
		//体力を破棄する
		this->m_pHealthFill->Uninit();   //終了処理
		delete this->m_pHealthFill;
		this->m_pHealthFill = nullptr;
	}

	//ダメージを確認する
	if (this->m_pDamageFill != nullptr)
	{//ダメージが生成されている場合
		//ダメージを破棄する
		this->m_pDamageFill->Uninit();   //終了処理
		delete this->m_pDamageFill;
		this->m_pDamageFill = nullptr;
	}

	//背景を確認する
	if (this->m_pGaugeBackground != nullptr)
	{//背景が生成されている場合
		//背景を破棄する
		this->m_pGaugeBackground->Uninit();   //終了処理
		delete this->m_pGaugeBackground;
		this->m_pGaugeBackground = nullptr;
	}
}

//=====================================================================================================================
//更新処理
//=====================================================================================================================
void HealthGauge::Update()
{
	//Kキーの入力を確認する
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_K))
	{//Kキーが押された時
		//HPを適用する
		HealthGauge::ApplyHp(50);
	}

	//体力の塗り部分の割合とダメージの塗り部分の割合を確認する
	float fRatioHealth = this->m_pHealthFill->GetRatio();   //体力の塗り部分の割合
	float fRatioDamage = this->m_pDamageFill->GetRatio();   //ダメージの塗り部分の割合
	if (fRatioHealth < fRatioDamage)
	{//体力の割合の方がダメージの割合より小さい場合
		//ダメージの割合を減らす
		this->m_pDamageFill->SetRatio(this->m_pDamageFill->GetRatio() - HealthGauge::SUB_DAMAGE_RATIO);
	}
	else if (fRatioHealth > fRatioDamage)
	{//体力の割合の方がダメージの割合より大きい場合
		//ダメージの割合を体力の割合に合わせる
		this->m_pDamageFill->SetRatio(fRatioHealth);
	}

	//更新処理を行う
	this->m_pHealthFill->Update();   //体力
	this->m_pDamageFill->Update();   //ダメージ
	this->m_pGaugeBackground->Update();   //背景
}

//=====================================================================================================================
//描画処理
//=====================================================================================================================
void HealthGauge::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ステンシルマスクの設定時に無効化したZバッファをもとにもどす
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//描画処理を行う
	this->m_pHealthFill->Draw();   //体力
	this->m_pDamageFill->Draw();   //ダメージ
	this->m_pGaugeBackground->Draw();   //背景
}

//=====================================================================================================================
//ヒットポイントの適用処理
//=====================================================================================================================
void HealthGauge::ApplyHp(int nHp)
{
	//体力に残りHPの割合を設定する
	this->m_pHealthFill->SetRatio((float)nHp / this->m_nMaxHp);
}

//=====================================================================================================================
//生成処理
//=====================================================================================================================
HealthGauge* HealthGauge::Create(int nHp, D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size)
{
	//体力ゲージのインスタンスを生成する
	HealthGauge* pHealthGauge = new HealthGauge(nHp, v3Pos, v2Size);
	pHealthGauge->Init();   //初期化処理

	//体力ゲージのインスタンスを返す
	return pHealthGauge;
}