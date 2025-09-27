//===============================================================================
//
//  装備の処理(weapom.h)
//					制作：大竹熙
// 
//===============================================================================

#ifndef _WEAPOM_H_
#define _WEAPOM_H_

#include "main.h"
#include "objectX.h"
#include "collision.h"

class CWeapon :public CObjectX
{
public:
	CWeapon(int nPriority = 2);				//コンストラクタ
	~CWeapon()override;		//デストラクタ
	void Init()override;		//初期化
	void Uninit()override;		//終了
	void Update()override;		//更新
	void Draw()override;		//描画

	void OnPickedUp();
	void SetEquipped(bool b) { m_bEquipped = b; }
	bool IsEquipped() const { return m_bEquipped; }
	static CWeapon* Create(D3DXVECTOR3 pos);

protected:


private:
	CHitCircle* m_pHitCircle = nullptr;
	std::vector<std::shared_ptr<CHitCircle>> m_HitCircle;	//円の当たり判定配列

	LPDIRECT3DTEXTURE9 m_pTextureObjectX[MAX_OBJ_TEX];
	DWORD m_dwNumMat;
	LPD3DXMESH m_pMesh;
	float m_baseY;
	bool m_bEquipped = false;
	float m_floatTime; // 上下運動用時間
};

#endif