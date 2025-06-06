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
#include "debug_line.h"

#include "manager.h"

//前方宣言
class CCTBarUI;
class CButtonUI;
class CCharacter;
class CPlayerMask;
class PlayerState;


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
	void SetState(std::shared_ptr<PlayerState>pState) {
		if (m_PlayerState != nullptr)
		{
			m_PlayerState = nullptr;
		}
		m_PlayerState = pState;
	}
	enum
	{
		MOTION_NUTORAL = 0,
		MOTION_WALK,
		MOTION_PARRY,
		MOTION_PARRY_STAY,
		MOTION_PARRY_ATTACK,
		MOTION_ATTACK,

	};
	void EnemyCollision();

private:

	//ステータス用定数
	static constexpr int MAX_LIFE = 1000;			//体力

	D3DXVECTOR3 m_OldPos;					//過去の位置
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	void FloorCollision();					//床との当たり判定
	void CamFloorCollision(LPD3DXMESH pMesh);
	bool FloorbumpyMesh(LPD3DXMESH pMesh);
	CCTBarUI* m_pCctBarUI;
	bool m_bAttackCt;
	int m_nPushedKey;
	bool m_bParryWait;
	std::vector<CButtonUI*>m_vButtonUI;
	float m_LastCamDis;
	std::shared_ptr<CDebugLine>m_pDebugLine;
	std::shared_ptr<PlayerState>m_PlayerState;
	//========================			クオータニオン用		====================================
	D3DXMATRIX m_mtxRot;		//回転マトリックス(保存用)
	D3DXQUATERNION m_quat;		//クオータニオン
	D3DXVECTOR3 m_vecAxis;		//回転軸のベクトル
	float m_fValueRot;			//回転量
};


//========================================================================================================
//プレイヤー状態管理ステートクラス

class PlayerState
{	//プレイヤーステート基底クラス　
public:
	//この状態になることは無いので純粋仮想関数化する
	virtual void Move(CPlayerX* pPlayer) = 0;
	virtual void Attack(CPlayerX* pPlayer) = 0;
	virtual void Parry(CPlayerX* pPlayer) = 0;
	
private:

};

class State_Nutoral : public PlayerState
{	//通常ステート
public:
	void Move(CPlayerX* pPlayer)override;
	void Attack(CPlayerX* pPlayer)override;
	void Parry(CPlayerX* pPlayer)override;
private:

};

class State_Attack : public PlayerState
{	//攻撃ステート
public:
	void Move(CPlayerX* pPlayer)override;
	void Attack(CPlayerX* pPlayer)override;
	void Parry(CPlayerX* pPlayer)override;
private:

};

class State_Parry : public PlayerState
{	//パリィステート(パリィ構え→パリィ待機→パリィ解除まで)
public:
	void Move(CPlayerX* pPlayer)override;
	void Attack(CPlayerX* pPlayer)override;
	void Parry(CPlayerX* pPlayer)override;
private:

};

class State_Damage : public PlayerState
{	//被ダメージステート
public:
	void Move(CPlayerX* pPlayer)override;
	void Attack(CPlayerX* pPlayer)override;
	void Parry(CPlayerX* pPlayer)override;
private:

};
#endif