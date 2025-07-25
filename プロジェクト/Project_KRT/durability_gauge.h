//=====================================================================================================================
//
//耐久力ゲージの処理[durability_gauge.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _DURABILITY_GAUGE_H_
#define _DURABILITY_GAUGE_H_

#include "gauge.h"
#include "durability_fill.h"
#include "gauge_background.h"

//耐久力ゲージ
class DurabilityGauge : public Gauge   //(親)ゲージ
{
public:
	static const D3DXCOLOR COLOR_DURABILITY_FILL;   //耐久力塗り部分の色
	static const D3DXVECTOR2 ADD_SIZE_BACKGROUND;   //背景のサイズの加算値

	//コンストラクタ
	DurabilityGauge(int nDurability, D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size) : Gauge(v3Pos, v2Size)
	{
		//メンバ変数を初期化する
		this->m_pDurabilityFill = nullptr;   //耐久力の塗り部分
		this->m_pGaugeBackground = nullptr;   //背景
		this->m_nMaxDurability = nDurability;   //耐久力の最大値
	}

	//デストラクタ
	~DurabilityGauge()
	{
	}

	void Init() override;   //初期化
	void Uninit() override;   //終了処理
	void Update() override;   //更新処理
	void Draw() override;   //描画処理
	void ApplyDurability(int nDurability);   //耐久力の適用処理

	static DurabilityGauge* Create(int nDurability, D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size);   //生成処理

private:
	DurabilityFill* m_pDurabilityFill;   //耐久力の塗り部分
	GaugeBackground* m_pGaugeBackground;   //背景部分
	int m_nMaxDurability;   //耐久力の最大値
};

#endif // !_DURABILITY_GAUGE_H_
