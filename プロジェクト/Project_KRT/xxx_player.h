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
class AttackBehavior;


class CPlayerX :public CCharacter
{
public:
	CPlayerX(int nPriority = 1);					//コンストラクタ
	~CPlayerX()override;		//デストラクタ
	void Init()override;		//初期化
	void Uninit()override;		//終了
	void Update()override;		//更新
	void Draw()override;		//描画

	bool EndMotion()override;
	bool PMove(float fCamRotZ);
	bool PAttackInfo();
	static CPlayerX* Create(D3DXVECTOR3 pos);

	inline D3DXVECTOR3 GetPos() { return CCharacter::GetPos(); };
	inline D3DXVECTOR3 GetMove() { return CCharacter::GetMove(); };
	void SetParry();
	_forceinline void SetState(std::shared_ptr<PlayerState>pState) {
		if (m_PlayerState != nullptr)
		{
			m_PlayerState = nullptr;
		}
		m_PlayerState = pState;
	}
	_forceinline void SetAttackBehavior(std::shared_ptr<AttackBehavior>pBehavior) {
		if (m_AttackBehavior != nullptr)
		{
			m_AttackBehavior = nullptr;
		}
		m_AttackBehavior = pBehavior;
	}
	inline std::shared_ptr<AttackBehavior> GetAttackBehavior() { return m_AttackBehavior; }
	enum
	{
		MOTION_NUTORAL = 0,
		MOTION_WALK,
		MOTION_PARRY,
		MOTION_PARRY_STAY,
		MOTION_PARRY_ATTACK,
		MOTION_ATTACK_N1,
		MOTION_ATTACK_N2,
		MOTION_ATTACK_N3,
		MOTION_ATTACK_N4,
		MOTION_ATTACK_N5,
		MOTION_ATTACK_N6,
		MOTION_ATTACK_N7,
	};
	void EnemyCollision();
	void ToEnemyAttack();
private:
	enum
	{
		ATTACK_NORMAL = 0,
		ATTACK_GREAT
	};
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
	std::vector<CButtonUI*>m_vButtonUI;
	float m_LastCamDis;
	std::shared_ptr<CDebugLine>m_pDebugLine;

	std::shared_ptr<PlayerState>m_PlayerState;
	std::shared_ptr<AttackBehavior>m_AttackBehavior;
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
	virtual void ToAttack(CPlayerX* pPlayer) = 0;
	virtual void ToParry(CPlayerX* pPlayer) = 0;
private:
};

class State_Nutoral : public PlayerState
{	//通常ステート
public:
	void Move(CPlayerX* pPlayer)override;
	void Attack(CPlayerX* pPlayer)override;
	void Parry(CPlayerX* pPlayer)override;
	void ToAttack(CPlayerX* pPlayer)override;
	void ToParry(CPlayerX* pPlayer)override;
private:
};

class State_Attack : public PlayerState
{	//攻撃ステート
public:
	void Move(CPlayerX* pPlayer)override;
	void Attack(CPlayerX* pPlayer)override;
	void Parry(CPlayerX* pPlayer)override;
	void ToAttack(CPlayerX* pPlayer)override;
	void ToParry(CPlayerX* pPlayer)override;
private:
};

class State_Parry : public PlayerState
{	//パリィステート(パリィ構え→パリィ待機→パリィ解除まで)
public:
	void Move(CPlayerX* pPlayer)override;
	void Attack(CPlayerX* pPlayer)override;
	void Parry(CPlayerX* pPlayer)override;
	void ToAttack(CPlayerX* pPlayer)override;
	void ToParry(CPlayerX* pPlayer)override;
private:
};

class State_ParryAttack : public PlayerState
{	//パリィステート(パリィ構え→パリィ待機→パリィ解除まで)
public:
	void Move(CPlayerX* pPlayer)override {};
	void Attack(CPlayerX* pPlayer)override {};
	void Parry(CPlayerX* pPlayer)override {};
	void ToAttack(CPlayerX* pPlayer)override {};
	void ToParry(CPlayerX* pPlayer)override {};

private:

};
class State_AttackWait : public PlayerState
{	//攻撃終了→次の段の攻撃or猶予終了まで
public:
	void Move(CPlayerX* pPlayer)override;
	void Attack(CPlayerX* pPlayer)override;
	void Parry(CPlayerX* pPlayer)override;
	void ToAttack(CPlayerX* pPlayer)override;
	void ToParry(CPlayerX* pPlayer)override;
private:
};
class State_Damage : public PlayerState
{	//被ダメージステート
public:
	void Move(CPlayerX* pPlayer)override;
	void Attack(CPlayerX* pPlayer)override;
	void Parry(CPlayerX* pPlayer)override;
	void ToAttack(CPlayerX* pPlayer)override;
	void ToParry(CPlayerX* pPlayer)override;
private:
};
//========================================================================================================

//========================================================================================================
//プレイヤーの連続攻撃
class AttackBehavior
{
private:


protected:

	bool InputNormal();		//通常攻撃の入力
	bool InputExtended();	//派生攻撃の入力
	struct MyInfo
	{
		bool use;
		int motion_num;
	};
	void UseDisable(CPlayerX* pPlayer)
	{
		int nownum = pPlayer->GetNowMotion();
		int nextnum = pPlayer->GetNextMotion();

		if (m_MyMotionNum != nownum&& nownum == nextnum)
		{
			m_bUse = false;
		}
	}
public:
	bool m_bUse;
	int m_MyMotionNum;

	AttackBehavior(MyInfo info = { false,1 }) :m_bUse(info.use), m_MyMotionNum(info.motion_num) {};
	virtual void NextAttack(CPlayerX* pPlayer) = 0;
	bool GetUse() { return m_bUse; }
	int GetMyMotionNum() { return m_MyMotionNum; }
};


class Attack_None : public AttackBehavior
{
public:
	Attack_None(MyInfo info = { true,CPlayerX::MOTION_NUTORAL }) :AttackBehavior(info) {}
	void NextAttack(CPlayerX* pPlayer)override;
};
class Attack_Normal1 : public AttackBehavior
{
public:
	Attack_Normal1(MyInfo info = { true,CPlayerX::MOTION_ATTACK_N1 }) :AttackBehavior(info) {}
	void NextAttack(CPlayerX* pPlayer)override;
};
class Attack_Normal2 : public AttackBehavior
{
public:
	Attack_Normal2(MyInfo info = { true,CPlayerX::MOTION_ATTACK_N2 }) :AttackBehavior(info) {}
	void NextAttack(CPlayerX* pPlayer)override;
};
class Attack_Normal3 : public AttackBehavior
{
public:
	Attack_Normal3(MyInfo info = { true,CPlayerX::MOTION_ATTACK_N3 }) :AttackBehavior(info) {}
	void NextAttack(CPlayerX* pPlayer)override;
};
class Attack_Normal4 : public AttackBehavior
{
public:
	Attack_Normal4(MyInfo info = { true,CPlayerX::MOTION_ATTACK_N4 }) :AttackBehavior(info) {}
	void NextAttack(CPlayerX* pPlayer)override;
};
class Attack_Normal5 : public AttackBehavior
{
public:
	Attack_Normal5(MyInfo info = { true,CPlayerX::MOTION_ATTACK_N5 }) :AttackBehavior(info) {}
	void NextAttack(CPlayerX* pPlayer)override;
};
class Attack_Normal6 : public AttackBehavior
{
public:
	Attack_Normal6(MyInfo info = { true,CPlayerX::MOTION_ATTACK_N6 }) :AttackBehavior(info) {}
	void NextAttack(CPlayerX* pPlayer)override;
};
class Attack_Normal7 : public AttackBehavior
{
public:
	Attack_Normal7(MyInfo info = { true,CPlayerX::MOTION_ATTACK_N7 }) :AttackBehavior(info) {}
	void NextAttack(CPlayerX* pPlayer)override;
};

#endif