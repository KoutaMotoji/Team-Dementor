//===============================================================================
//
//  空用板ポリゴン処理(sky_bg.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _FLOOR_H_
#define _FLOOR_H_

#include "main.h"
#include "object3D.h"


class CFloor :public CObject3D
{
public:
	CFloor();					//コンストラクタ
	~CFloor()override;			//デストラクタ
	void Init()override;		//初期化
	void Uninit()override;		//終了
	void Update()override;		//更新
	void Draw()override;		//描画

	static CFloor* Create(D3DXVECTOR3 pos);

private:
	static constexpr float FLOOR_SIZE = 1000.0f;
};



#endif