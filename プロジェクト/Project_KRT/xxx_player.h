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
#include "weapon.h"

#include "manager.h"

//前方宣言
class CCTBarUI;
class CButtonUI;
class CCharacter;
class CPlayerMask;
class PlayerState;
class PlayerArm_State;
class AttackBehavior;
class LockOn_State;

class CGaugeLife;
class CWeaponUI_Main;

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
	inline std::shared_ptr<PlayerArm_State>GetArmState() { return m_ArmState; }
	_forceinline void SetState(std::shared_ptr<PlayerState>pState) {
		if (m_PlayerState != nullptr)
		{
			m_PlayerState = nullptr;
		}
		m_PlayerState = pState;
	}
	_forceinline void SetArmState(std::shared_ptr<PlayerArm_State>pArmState) {
		if (m_ArmState != nullptr)
		{
			m_ArmState = nullptr;
		}
		m_ArmState = pArmState;
	}
	_forceinline void SetAttackBehavior(std::shared_ptr<AttackBehavior>pBehavior) {
		if (m_AttackBehavior != nullptr)
		{
			m_AttackBehavior = nullptr;
		}
		m_AttackBehavior = pBehavior;
	}
	_forceinline void SetLockOnState(std::shared_ptr<LockOn_State>pState) {
		if (m_LockOnState != nullptr)
		{
			m_LockOnState = nullptr;
		}
		m_LockOnState = pState;
	}
	inline std::shared_ptr<AttackBehavior> GetAttackBehavior() { return m_AttackBehavior; }
	enum
	{
		MOTION_NUTORAL = 0,
		MOTION_WALK,
		MOTION_PARRY,
		MOTION_PARRY_STAY,
		MOTION_PARRY_ATTACK,
		MOTION_KNOCKBACK,
		MOTION_ATTACK_N1,
		MOTION_ATTACK_N2,
		MOTION_ATTACK_N3,
		MOTION_ATTACK_N4,
		MOTION_ATTACK_N5,
		MOTION_ATTACK_N6,
		MOTION_ATTACK_N7,
		MOTION_ATTACK_Ex3,
		MOTION_ATTACK_Ex5,
		MOTION_ATTACK_Ex6,
		MOTION_GORIRA_WALK,
		MOTION_GORIRA_PARRY,
		MOTION_GORIRA_PARRY_STAY,
		MOTION_ATTACK_G_Ex3,
		MOTION_ATTACK_G_Ex4,
		MOTION_ATTACK_G_Ex6_toJump,
		MOTION_ATTACK_G_Ex6,
	};
	bool ToPlayerCollision();
	void EquipWeapon();
	void EnemyCollision();
	void ToEnemyAttack();
private:

	static constexpr int MAX_LIFE = 1000;			//体力

	D3DXVECTOR3 m_OldPos;					//過去の位置
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	void FloorCollision();					//床との当たり判定
	bool FloorbumpyMesh(LPD3DXMESH pMesh);

	void SetArmParts(std::string filename);

	_forceinline bool GetMoveInput() {
		return ((CManager::GetInstance()->GetJoypad()->GetJoyStickVecL().x != 0.0f ||
			CManager::GetInstance()->GetJoypad()->GetJoyStickVecL().y != 0.0f) ||
			(CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W) ||
			CManager::GetInstance()->GetKeyboard()->GetPress(DIK_A) ||
			CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S) ||
			CManager::GetInstance()->GetKeyboard()->GetPress(DIK_D)));
	}
	CCTBarUI* m_pCctBarUI;
	bool m_bAttackCt;
	int m_nPushedKey;
	std::vector<CButtonUI*>m_vButtonUI;
	float m_LastCamDis;
	std::shared_ptr<CDebugLine>m_pDebugLine;

	std::shared_ptr<PlayerState>m_PlayerState;
	std::shared_ptr<PlayerArm_State>m_ArmState;
	std::shared_ptr<AttackBehavior>m_AttackBehavior;
	std::shared_ptr<LockOn_State>m_LockOnState;
	CGaugeLife* m_pLifeGauge;
	CWeaponUI_Main* m_pWeaponIcon;
	CWeapon* m_pWeapon;
	CWeapon* m_pWeaponCandidate = nullptr;

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
	virtual void Move([[maybe_unused]] CPlayerX* pPlayer) = 0;
	virtual void Attack([[maybe_unused]]CPlayerX* pPlayer) = 0;
	virtual void Parry([[maybe_unused]]CPlayerX* pPlayer) = 0;
	virtual void ToAttack([[maybe_unused]]CPlayerX* pPlayer) = 0;
	virtual void ToParry([[maybe_unused]]CPlayerX* pPlayer) = 0;
private:
};

class State_Nutoral : public PlayerState
{	//通常ステート
public:
	void Move([[maybe_unused]]CPlayerX* pPlayer)override;
	void Attack([[maybe_unused]]CPlayerX* pPlayer)override;
	void Parry([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToAttack([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToParry([[maybe_unused]]CPlayerX* pPlayer)override;
private:
};

class State_Attack : public PlayerState
{	//攻撃ステート
public:
	void Move([[maybe_unused]]CPlayerX* pPlayer)override;
	void Attack([[maybe_unused]]CPlayerX* pPlayer)override;
	void Parry([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToAttack([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToParry([[maybe_unused]]CPlayerX* pPlayer)override;
private:
};

class State_Parry : public PlayerState
{	//パリィステート(パリィ構え→パリィ待機→パリィ解除まで)
public:
	void Move([[maybe_unused]]CPlayerX* pPlayer)override;
	void Attack([[maybe_unused]]CPlayerX* pPlayer)override;
	void Parry([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToAttack([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToParry([[maybe_unused]]CPlayerX* pPlayer)override;
private:
};

class State_ParryAttack : public PlayerState
{	//パリィステート(パリィ構え→パリィ待機→パリィ解除まで)
public:
	void Move([[maybe_unused]]CPlayerX* pPlayer)override {};
	void Attack([[maybe_unused]]CPlayerX* pPlayer)override {};
	void Parry([[maybe_unused]]CPlayerX* pPlayer)override {};
	void ToAttack([[maybe_unused]]CPlayerX* pPlayer)override {};
	void ToParry([[maybe_unused]]CPlayerX* pPlayer)override {};

private:

};
class State_Damage : public PlayerState
{	//被ダメージステート
public:
	void Move([[maybe_unused]]CPlayerX* pPlayer)override;
	void Attack([[maybe_unused]]CPlayerX* pPlayer)override;
	void Parry([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToAttack([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToParry([[maybe_unused]]CPlayerX* pPlayer)override;
private:
};

//========================================================================================================
//ロックオン状態管理クラス

class LockOn_State
{	//ロックオンステート基底クラス　
public:
	//この状態になることは無いので純粋仮想関数化する
	virtual void Swicth([[maybe_unused]]CPlayerX* pPlayer) = 0;
	virtual void UpdateCam([[maybe_unused]]CPlayerX* pPlayer) = 0;
private:
};

class LockEnable : public LockOn_State
{	//ロックオン状態クラス
public:
	static D3DXVECTOR3 s_savedPosV; // 保存用のカメラ視点
	static D3DXVECTOR3 s_savedPosR; // 保存用のカメラ注視点
	virtual void Swicth([[maybe_unused]]CPlayerX* pPlayer)override;
	virtual void UpdateCam([[maybe_unused]]CPlayerX* pPlayer)override;
private:
};

class LockDisable : public LockOn_State
{	//非ロックオン状態クラス
public:
	virtual void Swicth([[maybe_unused]]CPlayerX* pPlayer)override;
	virtual void UpdateCam([[maybe_unused]]CPlayerX* pPlayer)override;
private:
};

//========================================================================================================


#endif