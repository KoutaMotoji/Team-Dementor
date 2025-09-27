//===============================================================================
//
//  エネミー処理(enemy.h)
//								制作：大竹熙
// 
//===============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "character.h"
#include "debug_line.h"

#include "manager.h"

//前方宣言
class Enemy_State;
class CStage1BossGaugeLife;
class E_AttackBehavior;
class Enemy_AI;
class EnemyAI;

class CEnemy :public CCharacter
{
public:
	CEnemy();					//コンストラクタ
	~CEnemy()override {};		//デストラクタ
	void Init()override;		//初期化
	void Uninit()override;		//終了
	void Update()override;		//更新
	void Draw()override;		//描画

	void OnWeaponPicked();
	void Respawn();
	void DoAttack();
	void Move();
	bool EndMotion()override;

	_forceinline void SetState(std::shared_ptr<Enemy_State>pState) {
		if (m_State != nullptr) {
			m_State = nullptr;
		}
		m_State = pState;
	}
	_forceinline void SetAttackState(std::shared_ptr<E_AttackBehavior>pState);

	bool IsHidden() const { return m_bHidden; }
	void SetRespawnPos(const D3DXVECTOR3& p) { m_RespawnPos = p; }

	void BeDamaged();			//外部から呼ぶ用
	void Damaged();				//Stateの中で呼ぶ用
	static CEnemy* Create(D3DXVECTOR3 pos);

	enum
	{
		MOTION_NUTORAL = 0,
		MOTION_WALK,
		MOTION_ATTACK,
		MOTION_DAMAGE_SMALL,
		MOTION_DIVE,
		MOTION_DIE,
	};
	std::vector<std::shared_ptr<CHitCircle>> GetBodyHitCircle() { return m_pHC_BodyCollision; }
	std::shared_ptr<EnemyAI> GetEnemyAI() { return m_pEnemyAI; }
	std::shared_ptr<Enemy_AI> GetEnemy_AI() { return m_bEnemyAI; }
private:
	std::shared_ptr<CDebugLine>m_pDebugLine;
	std::vector < std::shared_ptr<CDebugLine>>m_pDL_BodyCollision;

	std::vector<std::shared_ptr<CHitCircle>> m_pHC_BodyCollision;	//円の当たり判定配列

	std::shared_ptr<EnemyAI> m_pEnemyAI;
	std::shared_ptr<Enemy_State> m_State;
	std::shared_ptr<Enemy_AI>m_bEnemyAI;
	std::shared_ptr<E_AttackBehavior> m_AttackState;
	//ステータス用定数
	CStage1BossGaugeLife* m_HPGauge;
	D3DXVECTOR3 m_OldPos;					//過去の位置

	void FloorCollision();					//床との当たり判定
	bool m_bAttackCt;
	int m_nAttackcnt;
	bool m_moveFlag;
	bool m_bStopFlag;
	int m_nLife;
	int m_nTime;
	int m_Direction;
	D3DXVECTOR3 m_TargetPos;  // 突進時の目的地
	bool m_bChasing = false;  // 突進中フラグ

	// 死亡 / 復活管理
	bool m_bDead = false;       // 死亡フラグ
	float m_fDeathTimer = 0.0f; // 死亡経過時間
	bool m_bDying = false;               // 死亡アニメ中フラグ（アニメ再生中）
	bool m_bHidden = false;              // モデル非表示（死亡アニメ後、復活待ち）
	bool m_bDeathAnimFinished = false;   // 死亡アニメがEndMotionで終わったか
	int  m_RespawnTimerFrames = 0;       // 復活カウント（フレーム）
	int  m_RespawnDelayFrames = 60 * 5;  // 復活までのフレーム（例: 5秒）
	bool m_bCanMove = false;
	bool m_bCanAttack = false;
	bool m_bStunned = false;   // 被弾中かどうか
	int  m_StunTimer = 0;      // 被弾硬直の残りフレーム
	bool m_bItemDropped = false;   // アイテムを落とすフラグ
	bool m_bItemCreated = false;   // 実際に生成したかフラグ	
	D3DXVECTOR3 m_RespawnPos; // 固定復活位置（Createで上書き可）
	D3DXVECTOR3 m_WeaponDropPos; // 死亡時の座標保存用
	bool m_bPendingDropWeapon;
	bool m_bWeaponDropped;
	static int s_nWeaponCount;       // フィールド上の武器数
	static const int MAX_WEAPON; // 上限
};

//========================================================================================================
//	状態管理ステートクラス
class Enemy_State
{
public:
	virtual void Move(CEnemy* pGorira) = 0;
	virtual void Attack(CEnemy* pGorira) = 0;
	virtual void Damage(CEnemy* pGorira) = 0;
	virtual void Wait(CEnemy* pGorira) = 0;
};

class Enemy_Nutoral : public Enemy_State
{
public:
	void Move(CEnemy* pGorira)override;
	void Attack(CEnemy* pGorira)override;
	void Damage(CEnemy* pGorira)override;
	void Wait(CEnemy* pGorira)override;
};

class Enemy_Attack : public Enemy_State
{
public:
	void Move(CEnemy* pGorira)override;
	void Attack(CEnemy* pGorira)override;
	void Damage(CEnemy* pGorira)override;
	void Wait(CEnemy* pGorira)override;
};

class Enemy_Damage : public Enemy_State
{
public:
	void Move(CEnemy* pGorira)override;
	void Attack(CEnemy* pGorira)override;
	void Damage(CEnemy* pGorira)override;
	void Wait(CEnemy* pGorira)override;
};

class Enemy_Death : public Enemy_State
{
public:
	void Move(CEnemy* pGorira)override;
	void Attack(CEnemy* pGorira)override;
	void Damage(CEnemy* pGorira)override;
	void Wait(CEnemy* pGorira)override;
};

#endif