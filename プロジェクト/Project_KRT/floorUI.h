//===============================================================================
//
//  フロアUI処理(floorUI.h)
//					制作：大竹熙
// 
//===============================================================================

#ifndef _FLOORUI_H_
#define _FLOORUI_H_

#include "object2D.h"

class CBaseFloorUI : public CObject2D
{
public:
	CBaseFloorUI(int nPriority = 3):CObject2D(nPriority) {};					//コンストラクタ
	~CBaseFloorUI()override = default;	//デストラクタ
	void Init()override;				//初期化
	void Update()override;				//更新

	void SetFloorNumberUI();

	void AddScore(int ntexpos) { m_nTexPos += ntexpos; SetFloorNumberUI(); SaveScore = m_nTexPos; }
	void SetTexPos(int ntexpos) { m_nTexPos = ntexpos; }

	static CBaseFloorUI* Create(D3DXVECTOR3 pos);
private:
	int  m_nTexPos;
	static int SaveScore;
};

class CFloorUI : public CBaseFloorUI
{
public:
	CFloorUI() {};						//コンストラクタ
	~CFloorUI()override = default;		//デストラクタ
	void Init()override;				//初期化
	void Update()override;				//更新
	void Draw()override;				//描画

	static CFloorUI* Create();
private:
};

class CFloorNumberUI : public CBaseFloorUI
{
public:
	CFloorNumberUI() {};						//コンストラクタ
	~CFloorNumberUI()override = default;		//デストラクタ
	void Init()override;				//初期化
	void Update()override;				//更新
	void Draw()override;				//描画

	static CFloorNumberUI* Create(int number);
private:
};



#endif