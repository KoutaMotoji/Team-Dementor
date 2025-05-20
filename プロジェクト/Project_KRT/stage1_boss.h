//===============================================================================
//
//  プレイヤー処理(playerX.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _STAGE1_BOSS_H_
#define _STAGE1_BOSS_H_

#include "main.h"
#include "character.h"

#include "manager.h"

//前方宣言

class CG_Gorira :public CCharacter
{
public:
	CG_Gorira();						//コンストラクタ
	~CG_Gorira()override {};		//デストラクタ
	void Init()override;		//初期化
	void Uninit()override;		//終了
	void Update()override;		//更新
	void Draw()override;		//描画

	static CG_Gorira* Create(D3DXVECTOR3 pos);

	enum
	{
		MOTION_NUTORAL = 0,
		MOTION_WALK,
		MOTION_ATTACK,
		MOTION_JUMP,
		MOTION_LANDING,
	};
private:
	//ステータス用定数
	static constexpr int MAX_LIFE = 1000;			//体力

	D3DXVECTOR3 m_move;						//移動量
	D3DXVECTOR3 m_OldPos;					//過去の位置

	void FloorCollision();					//床との当たり判定
	bool m_bAttackCt;
};

#endif