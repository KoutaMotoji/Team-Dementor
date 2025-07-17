//=====================================================================================================================
//
//ゲージの背景の処理[gauge_background.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _GAUGE_BACKGROUND_H_
#define _GAUGE_BACKGROUND_H_

#include "main.h"

//前方宣言
class Gauge;   //ゲージ

//ゲージの背景
class GaugeBackground
{
public:
	//コンストラクタ
	GaugeBackground(Gauge* pGauge)
	{
		//メンバ変数を初期化する
		this->m_pGauge = pGauge;   //ゲージ
		this->m_pVtxBuffer = nullptr;   //頂点バッファ
		this->m_pTexture = nullptr;   //テクスチャ
		this->m_color = { 1.0f, 1.0f, 1.0f, 1.0f };   //色
		this->m_v2AddSize = { 0.0f, 0.0f };   //サイズの加算値
	}

	//デストラクタ
	~GaugeBackground()
	{
	}

	void Init();   //初期化
	void Uninit();   //終了処理
	void Update();   //更新処理
	void Draw();   //描画処理
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { this->m_pTexture = pTexture; };   //テクスチャの設定処理
	void SetAddSize(D3DXVECTOR2 v2AddSize) { this->m_v2AddSize = v2AddSize; };   //サイズの加算値の設定処理

private:
	Gauge* m_pGauge;   //ゲージ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;   //頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;   //テクスチャ
	D3DXCOLOR m_color;   //色
	D3DXVECTOR2 m_v2AddSize;   //サイズの加算値
};

#endif // !_GAUGE_BACKGROUND_H_
