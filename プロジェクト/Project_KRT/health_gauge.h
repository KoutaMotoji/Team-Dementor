//=====================================================================================================================
//
//体力ゲージの処理[health_gauge.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _HEALTH_GAUGE_H_
#define _HEALTH_GAUGE_H_

#include "gauge.h"
#include "gauge_background.h"
#include "health_fill.h"
#include "damage_fill.h"

//体力ゲージ
class HealthGauge : public Gauge   //(親)ゲージ
{
public:
	static const float SUB_DAMAGE_RATIO;   //ダメージ割合の減算量
	static const D3DXCOLOR COLOR_HEALTH_FILL;   //体力塗り部分の色
	static const D3DXCOLOR COLOR_DAMAGE_FILL;   //ダメージ塗り部分の色
	static const D3DXVECTOR2 ADD_SIZE_BACKGROUND;   //背景のサイズの加算値

	//コンストラクタ
	HealthGauge(int nHp, D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size) : Gauge(v3Pos, v2Size)
	{
		//メンバ変数を初期化する
		this->m_pHealthFill = nullptr;   //体力
		this->m_pDamageFill = nullptr;   //ダメージ
		this->m_pGaugeBackground = nullptr;   //背景
		this->m_nMaxHp = nHp;   //ヒットポイントの最大値
	}

	//デストラクタ
	~HealthGauge()
	{
	}

	void Init() override;   //初期化
	void Uninit() override;   //終了処理
	void Update() override;   //更新処理
	void Draw() override;   //描画処理
	void ApplyHp(int nHp);   //ヒットポイントの適用処理

	static HealthGauge* Create(int nHp, D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size);   //生成処理

private:
	HealthFill* m_pHealthFill;   //体力部分
	DamageFill* m_pDamageFill;   //ダメージ部分
	GaugeBackground* m_pGaugeBackground;   //背景部分
	int m_nMaxHp;   //ヒットポイントの最大値
};

#endif // !_HEALTH_GAUGE_H_
