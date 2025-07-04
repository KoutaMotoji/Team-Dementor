//===============================================================================
//
//  地形メッシュの処理(mesh_ground.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _FLOOR_STONE_H_
#define _FLOOR_STONE_H_

#include "main.h"
#include "objectX.h"

class CMeshGround :public CObjectX
{
public:
	CMeshGround(int nPriority = 2);				//コンストラクタ
	~CMeshGround()override;		//デストラクタ
	void Init()override;		//初期化
	void Uninit()override;		//終了
	void Update()override;		//更新
	void Draw()override;		//描画
	static CMeshGround* Create(D3DXVECTOR3 pos);
	static CMeshGround* Create(D3DXVECTOR3 pos,int i);

protected:

private:
	int m_mode;
};

#endif