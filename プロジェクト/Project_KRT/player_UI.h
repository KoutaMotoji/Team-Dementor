//===============================================================================
//
//		プレイヤー用UI(player_UI.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _PLAYER_UI_H_
#define _PLAYER_UI_H_

#include "main.h"
#include "object2D.h"
#include "objectCircleGauge.h"

class CGaugeLife :public CObject2D
{
public:
	CGaugeLife(int nPriority = 7) ;		//コンストラクタ
	~CGaugeLife()override;				//デストラクタ
	void Init()override;		//初期化
	void Uninit()override;		//終了
	void Update()override;		//更新
	void Draw()override;		//描画
	static CGaugeLife* Create(int nMaxGauge);
private:
	void SetGauge();
};

class CGaugeLiFrame :public CObject2D
{
public:
	CGaugeLiFrame(int nPriority = 7) :CObject2D(nPriority) {};		//コンストラクタ
	~CGaugeLiFrame()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//描画

	static CGaugeLiFrame* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
private:
};

class CGaugeLiBack :public CObject2D
{
public:
	CGaugeLiBack(int nPriority = 6) : CObject2D(nPriority) {};		//コンストラクタ
	~CGaugeLiBack()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//描画

	static CGaugeLiBack* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
private:
};

class CGaugeLiDeco :public CObject2D
{
public:
	CGaugeLiDeco(int nPriority = 5) : CObject2D(nPriority) {};		//コンストラクタ
	~CGaugeLiDeco()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//描画

	static CGaugeLiDeco* Create();
private:
};

class CGaugeCircle :public CObjectCircleGauge
{
public:
	CGaugeCircle(int nPriority = 5) : CObjectCircleGauge(nPriority) {};		//コンストラクタ
	~CGaugeCircle()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Update()override;		//更新
	void Draw()override;		//描画

	static CGaugeCircle* Create();
private:
};

class CGaugeCircleDeco :public CObject2D
{
public:
	CGaugeCircleDeco(int nPriority = 4) : CObject2D(nPriority) {};		//コンストラクタ
	~CGaugeCircleDeco()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//描画

	static CGaugeCircleDeco* Create();
private:
};

#endif