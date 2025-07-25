//===============================================================================
//
//		時計UI(Clock.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _CLOCK_UI_H_
#define _CLOCK_UI_H_

#include "main.h"
#include "object2D.h"
#include "objectCircleGauge.h"

class CClock
{
private:
	static std::shared_ptr<CClock>_instance;
	int m_LastCount;	//残りカウント数
	int m_MaxCount;		//最大カウント数

	int m_FrameCnt;		//フレーム計測用
	bool m_bCountedThisFrame;	//現在のフレーム内で2度以上更新されないようにするフラグ
	bool m_bTimerStop;
public:
	CClock() :m_bCountedThisFrame(false), m_LastCount(0), m_FrameCnt(0), m_bTimerStop(false){}
	~CClock() = default;
	_inline static std::shared_ptr<CClock> GetInstance() {
		if (_instance == nullptr)
		{
			_instance = std::make_shared<CClock>();
			_instance->m_LastCount = 1;
			_instance->m_MaxCount = 1;
		}
		return _instance;
	}
	void Update()
	{
		if (m_bCountedThisFrame)return;
		if (m_bTimerStop)return;
		if (m_LastCount <= 0)return;
		if (m_FrameCnt >= 60)
		{
			m_FrameCnt = 0;
			--m_LastCount;
		}
		else ++m_FrameCnt;
		m_bCountedThisFrame = true;
	}

	void FrameFragDisable() { m_bCountedThisFrame = false; }	//現在のフレーム内での使用フラグを非に
	int GetLastCount() { return m_LastCount; }					//現在の残り時間を返す
	int GetMaxCount() { return m_MaxCount; }					//現在の残り時間を返す

	bool GetTimeUped() { return m_LastCount <= 0; }				//現在が制限時間内かを返す
	void SetTimerStop(bool bStop) { m_bTimerStop = bStop; }		//タイマー停止
	void SetClock(int Value) { m_LastCount = Value; m_MaxCount = Value; }
};


//====================================================================================================
//以下UI処理

//ポインタ取得用前方宣言
class CClockHands;
class CClockBack;

//時計用ゲージ本体
class CClockGauge :public CObjectCircleGauge
{
public:
	CClockGauge(int nPriority = 5) : CObjectCircleGauge(nPriority), m_pClockHands(nullptr){};		//コンストラクタ
	~CClockGauge()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Uninit()override;
	void Update()override;		//更新

	void Draw()override;		//描画

	static CClockGauge* Create();
private:
	void QuakeObj();
	CClockHands* m_pClockHands;
	CClockBack* m_pClockBack;
};

//時計用ゲージ
class CClockBack :public CObject2D
{
public:
	CClockBack(int nPriority = 4) : CObject2D(nPriority) {};		//コンストラクタ
	~CClockBack()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//描画

	static CClockBack* Create();
private:
};

//時計用針
class CClockHands :public CObject2D
{
public:
	CClockHands(int nPriority = 6) : CObject2D(nPriority) {};		//コンストラクタ
	~CClockHands()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//描画

	static CClockHands* Create();
private:
};

#endif