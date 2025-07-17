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
	CBaseFloorUI() {};					//コンストラクタ
	~CBaseFloorUI()override = default;	//デストラクタ
	void Init()override;				//初期化
	void Update()override;				//更新

	static CBaseFloorUI* Create(D3DXVECTOR3 pos);
private:
};

class CFloorUI : public CBaseFloorUI
{
public:
	CFloorUI() {};						//コンストラクタ
	~CFloorUI()override = default;		//デストラクタ
	void Init()override;				//初期化
	void Update()override;				//更新
	void Draw()override;				//描画

	static CFloorUI* Create(D3DXVECTOR3 pos);
private:
};

class CFloorNumberUI : public CBaseFloorUI
{
public:
	CFloorNumberUI();						//コンストラクタ
	~CFloorNumberUI()override = default;		//デストラクタ
	void Init()override;				//初期化
	void Update()override;				//更新
	void Draw()override;				//描画
	
	inline void SetScore(int nScore) { m_nTexPos = nScore; SetFloorNumberUI(); SaveScore = m_nTexPos; }
	void AddScore(int ntexpos) { m_nTexPos += ntexpos; SetFloorNumberUI(); SaveScore = m_nTexPos; }
	void SetTexPos(int ntexpos) { m_nTexPos = ntexpos; }

	static CFloorNumberUI* Create(D3DXVECTOR3 pos);
private:
	void SetFloorNumberUI();
	static int  m_nTexPos;
	static int SaveScore;
};

class CFloorTypeUI : public CBaseFloorUI
{
public:
	CFloorTypeUI() {};						//コンストラクタ
	~CFloorTypeUI()override = default;		//デストラクタ
	void Init()override;					//初期化
	void Update()override;					//更新
	void Draw()override;					//描画
		
	static CFloorTypeUI* Create(D3DXVECTOR3 pos);
private:
	int  m_nTexPos;
};

#endif