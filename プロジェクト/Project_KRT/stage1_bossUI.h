//===============================================================================
//
//		プレイヤー用UI(player_UI.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _STAGE1BOSS_UI_H_
#define _STAGE1BOSS_UI_H_

#include "main.h"
#include "object2D.h"

//プレイヤーHPゲージ本体
class CStage1BossGaugeLife :public CObject2D
{
public:
	CStage1BossGaugeLife(int nPriority = 7);		//コンストラクタ
	~CStage1BossGaugeLife()override;				//デストラクタ
	void Init()override;		//初期化
	void Uninit()override;		//終了
	void Update()override;		//更新
	void Draw()override;		//描画
	static CStage1BossGaugeLife* Create(int nMaxStage1BossGauge);
private:
	void SetStage1BossGauge(int nLife);
	int m_nMaxLife;
};

//プレイヤーHPゲージの外側フレーム
class CStage1BossGaugeLiFrame :public CObject2D
{
public:
	CStage1BossGaugeLiFrame(int nPriority = 7) :CObject2D(nPriority) {};		//コンストラクタ
	~CStage1BossGaugeLiFrame()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//描画

	static CStage1BossGaugeLiFrame* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
private:
};

//プレイヤーHPゲージの裏側
class CStage1BossGaugeLiBack :public CObject2D
{
public:
	CStage1BossGaugeLiBack(int nPriority = 6) : CObject2D(nPriority) {};		//コンストラクタ
	~CStage1BossGaugeLiBack()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//描画

	static CStage1BossGaugeLiBack* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
private:
};

//プレイヤーHPゲージの装飾
class CStage1BossGaugeLiDeco :public CObject2D
{
public:
	CStage1BossGaugeLiDeco(int nPriority = 5) : CObject2D(nPriority) {};		//コンストラクタ
	~CStage1BossGaugeLiDeco()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//描画

	static CStage1BossGaugeLiDeco* Create();
private:
};

#endif