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
	CFloorNumberUI() {};						//コンストラクタ
	~CFloorNumberUI()override = default;		//デストラクタ
	void Init()override;				//初期化
	void Update()override;				//更新
	void Draw()override;				//描画
	
	void SetFloorNumberUI(int nfloornumber);
	void AddFloorNumber(int addnumber) { m_FloorNumber + addnumber; }
	void SetTexPos(int ntexpos) { m_nTexPos = ntexpos; }

	static CFloorNumberUI* Create(D3DXVECTOR3 pos);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFloorNumberUI;
	int  m_nTexPos;
	int m_FloorNumber;
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
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFloorTypeUI;
	int  m_nTexPos;
};

#endif