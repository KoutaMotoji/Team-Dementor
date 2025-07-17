//=====================================================================================================================
//
//耐久力ゲージの処理[durability_gauge.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#include "durability_gauge.h"
#include "manager.h"

//静的メンバ変数
const D3DXCOLOR DurabilityGauge::COLOR_DURABILITY_FILL = { 0.75f, 0.75f, 0.75f, 1.0f };   //耐久力塗り部分の色
const D3DXVECTOR2 DurabilityGauge::ADD_SIZE_BACKGROUND = { 7.0f, 15.0f };   //背景のサイズの加算値

//=====================================================================================================================
//初期化処理
//=====================================================================================================================
void DurabilityGauge::Init()
{
	//ゲージの背景のインスタンスを生成する
	this->m_pGaugeBackground = new GaugeBackground(this);
	this->m_pGaugeBackground->Init();   //初期化処理
	this->m_pGaugeBackground->SetAddSize(DurabilityGauge::ADD_SIZE_BACKGROUND);   //サイズの加算値を設定する

	//耐久力の塗り部分のインスタンスを生成する
	this->m_pDurabilityFill = new DurabilityFill(this, DurabilityGauge::COLOR_DURABILITY_FILL);
	this->m_pDurabilityFill->Init();   //初期化処理

	//背景にテクスチャを設定する
	LPDIRECT3DTEXTURE9 pTexture = nullptr;   //設定するテクスチャ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();   //デバイスを取得
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\durability_gauge_bg_00.png", &pTexture);   //テクスチャを読み込む
	this->m_pGaugeBackground->SetTexture(pTexture);
}

//=====================================================================================================================
//終了処理
//=====================================================================================================================
void DurabilityGauge::Uninit()
{
	//耐久力の塗り部分を確認する
	if (this->m_pDurabilityFill != nullptr)
	{//耐久力の塗り部分が生成されている場合
		//耐久力の塗り部分を破棄する
		this->m_pDurabilityFill->Uninit();   //終了処理
		delete this->m_pDurabilityFill;
		this->m_pDurabilityFill = nullptr;
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
void DurabilityGauge::Update()
{
	//塗り部分の更新処理を行う
	this->m_pDurabilityFill->Update();   //耐久力
	this->m_pGaugeBackground->Update();   //背景
}

//=====================================================================================================================
//描画処理
//=====================================================================================================================
void DurabilityGauge::Draw()
{
	//塗り部分の描画処理を行う
	this->m_pDurabilityFill->Draw();   //耐久力
	this->m_pGaugeBackground->Draw();   //背景
}

//=====================================================================================================================
//ヒットポイントの適用処理
//=====================================================================================================================
void DurabilityGauge::ApplyDurability(int nDurability)
{
	//耐久力の塗り部分に残り耐久力の割合を設定する
	this->m_pDurabilityFill->SetRatio((float)nDurability / this->m_nMaxDurability);
}

//=====================================================================================================================
//生成処理
//=====================================================================================================================
DurabilityGauge* DurabilityGauge::Create(int nDurability, D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size)
{
	//耐久力ゲージのインスタンスを生成する
	DurabilityGauge* pDurabilityGauge = new DurabilityGauge(nDurability, v3Pos, v2Size);
	pDurabilityGauge->Init();   //初期化処理

	//耐久力ゲージのインスタンスを返す
	return pDurabilityGauge;
}