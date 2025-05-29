//===============================================================================
//
//  プレイヤー処理(playerX.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _PLAYERX_H_
#define _PLAYERX_H_

#include "main.h"
#include "character.h"
#include "object2D.h"
#include "modelparts.h"


#include "manager.h"

//前方宣言
class CCTBarUI;
class CButtonUI;
class CCharacter;
class CPlayerMask;

class CPlayerX :public CCharacter
{
public:
	CPlayerX(int nPriority = 1);					//コンストラクタ
	~CPlayerX()override;		//デストラクタ
	void Init()override;		//初期化
	void Uninit()override;		//終了
	void Update()override;		//更新
	void Draw()override;		//描画

	bool PMove(float fCamRotZ);
	bool PAttackInfo();
	static CPlayerX* Create(D3DXVECTOR3 pos);

	inline D3DXVECTOR3 GetPos() { return CCharacter::GetPos(); };
	inline D3DXVECTOR3 GetMove() { return CCharacter::GetMove(); };
	void SetParry();
	enum
	{
		MOTION_NUTORAL = 0,
		MOTION_WALK,
		MOTION_ATTACK,
		MOTION_JUMP,
		MOTION_LANDING,
		MOTION_PARRY,
		MOTION_PARRY_STAY,
		MOTION_PARRY_ATTACK
	};
private:

	//ステータス用定数
	static constexpr int MAX_LIFE = 1000;			//体力

	D3DXVECTOR3 m_OldPos;					//過去の位置
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	void FloorCollision();					//床との当たり判定
	void EnemyCollision();
	void CamFloorCollision(LPD3DXMESH pMesh);
	bool FloorbumpyMesh(LPD3DXMESH pMesh);
	CCTBarUI* m_pCctBarUI;
	bool m_bAttackCt;
	int m_nPushedKey;
	bool m_bParryWait;
	std::vector<CButtonUI*>m_vButtonUI;
	float m_LastCamDis;
	//========================			クオータニオン用		====================================
	D3DXMATRIX m_mtxRot;		//回転マトリックス(保存用)
	D3DXQUATERNION m_quat;		//クオータニオン
	D3DXVECTOR3 m_vecAxis;		//回転軸のベクトル
	float m_fValueRot;			//回転量
};



#endif