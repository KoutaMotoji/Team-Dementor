//=====================================================================================================================
//
//塗り部分の処理[fill.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _FILL_H_
#define _FILL_H_

#include "main.h"

//前方宣言
class Gauge;   //ゲージ

//塗り部分
class Fill
{
public:
	//コンストラクタ
	Fill(Gauge* pGauge , D3DXCOLOR color)
	{
		//メンバ変数を初期化する
		this->m_pGauge = pGauge;   //ゲージ
		this->m_pVtxBuffer = nullptr;   //頂点バッファ
		this->m_color = color;   //色
		this->m_fRatio = 1.0f;   //割合
	}

	//デストラクタ
	~Fill()
	{
	}

	void Init();   //初期化
	void Uninit();   //終了処理
	void Update();   //更新処理
	void Draw();   //描画処理
	void SetRatio(float fRatio) { this->m_fRatio = fRatio; };   //割合の設定処理
	float GetRatio() { return this->m_fRatio; };   //割合の取得処理

private:
	Gauge* m_pGauge;   //ゲージ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;   //頂点バッファ
	D3DXCOLOR m_color;   //色
	float m_fRatio;   //割合
};

#endif // !_FILL_H_
