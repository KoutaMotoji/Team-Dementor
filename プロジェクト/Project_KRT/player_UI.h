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

//プレイヤーHPゲージ本体
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

//プレイヤーHPゲージの外側フレーム
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

//プレイヤーHPゲージの裏側
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

//プレイヤーHPゲージの装飾
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

//円形ゲージ(用途未定)
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

//円形ゲージ裏側
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

//腕パーツUI-文字
class CWeaponUI_Sub :public CObject2D
{
public:
	CWeaponUI_Sub(int nPriority = 4) : CObject2D(nPriority) {};		//コンストラクタ
	~CWeaponUI_Sub()override = default;				//デストラクタ
	void Init()override;		//初期化

	static CWeaponUI_Sub* Create();
private:
};
//腕パーツUI-背景
class CWeaponUI_Back :public CObject2D
{
public:
	CWeaponUI_Back(int nPriority = 3) : CObject2D(nPriority) {};		//コンストラクタ
	~CWeaponUI_Back()override = default;				//デストラクタ
	void Init()override;		//初期化

	static CWeaponUI_Back* Create();
private:
};

//腕パーツUI-なにもなし
class CWeaponUI_Main :public CObject2D
{
public:
	CWeaponUI_Main(int nPriority = 4) : CObject2D(nPriority) {};		//コンストラクタ
	~CWeaponUI_Main()override = default;				//デストラクタ
	void Init()override;		//初期化

	static CWeaponUI_Main* Create();
private:
};
//腕パーツUI-ゴリラ
class CWeaponUI_Main_Gorira :public CWeaponUI_Main
{
public:
	CWeaponUI_Main_Gorira()  {};		//コンストラクタ
	~CWeaponUI_Main_Gorira()override = default;				//デストラクタ
	void Init()override;		//初期化

	static CWeaponUI_Main_Gorira* Create();
private:
};

#endif