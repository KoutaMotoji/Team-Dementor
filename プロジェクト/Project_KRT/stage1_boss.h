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
#include "debug_line.h"

#include "manager.h"

//前方宣言
class Stage1Boss_State;
class CStage1BossGaugeLife;
class G_AttackBehavior;

class CG_Gorira :public CCharacter
{
public:
	CG_Gorira();						//コンストラクタ
	~CG_Gorira()override {};		//デストラクタ
	void Init()override;		//初期化
	void Uninit()override;		//終了
	void Update()override;		//更新
	void Draw()override;		//描画

	void DoAttack();
	void Move();

	_forceinline void SetState(std::shared_ptr<Stage1Boss_State>pState) {
		if (m_State != nullptr)		{
			m_State = nullptr;
		}
		m_State = pState;
	}
	_forceinline void SetAttackState(std::shared_ptr<G_AttackBehavior>pState);

	void BeDamaged() ;			//外部から呼ぶ用
	void Damaged();				//Stateの中で呼ぶ用
	static CG_Gorira* Create(D3DXVECTOR3 pos);

	enum
	{
		MOTION_NUTORAL = 0,
		MOTION_WALK,
		MOTION_ATTACK,
		MOTION_DAMAGE_BIG,
		MOTION_DAMAGE_SMALL,
	};
	std::vector<std::shared_ptr<CHitCircle>> GetBodyHitCircle() { return m_pHC_BodyCollision; }
private:
	std::shared_ptr<CDebugLine>m_pDebugLine;
	std::vector < std::shared_ptr<CDebugLine>>m_pDL_BodyCollision;

	std::vector<std::shared_ptr<CHitCircle>> m_pHC_BodyCollision;	//円の当たり判定配列

	std::shared_ptr<Stage1Boss_State> m_State;
	std::shared_ptr<G_AttackBehavior> m_AttackState;
	//ステータス用定数
	CStage1BossGaugeLife* m_HPGauge;
	D3DXVECTOR3 m_OldPos;					//過去の位置

	void FloorCollision();					//床との当たり判定
	bool m_bAttackCt;
	int m_nAttackcnt;
	bool m_moveFlag;
	int m_nLife;
};

//========================================================================================================
//	状態管理ステートクラス
class Stage1Boss_State
{
public:
	virtual void Move(CG_Gorira* pGorira) = 0;
	virtual void Attack(CG_Gorira* pGorira) = 0;
	virtual void Damage(CG_Gorira* pGorira) = 0;
	virtual void Wait(CG_Gorira* pGorira) = 0;
};

class Stage1Boss_Nutoral : public Stage1Boss_State
{
public:
	void Move(CG_Gorira* pGorira)override;
	void Attack(CG_Gorira* pGorira)override;
	void Damage(CG_Gorira* pGorira)override;
	void Wait(CG_Gorira* pGorira)override;
};

class Stage1Boss_Attack : public Stage1Boss_State
{
public:
	void Move(CG_Gorira* pGorira)override;
	void Attack(CG_Gorira* pGorira)override;
	void Damage(CG_Gorira* pGorira)override;
	void Wait(CG_Gorira* pGorira)override;
};

class Stage1Boss_Damage: public Stage1Boss_State
{
public:
	void Move(CG_Gorira* pGorira)override;
	void Attack(CG_Gorira* pGorira)override;
	void Damage(CG_Gorira* pGorira)override;
	void Wait(CG_Gorira* pGorira)override;
};

class Stage1Boss_Death : public Stage1Boss_State
{
public:
	void Move(CG_Gorira* pGorira)override;
	void Attack(CG_Gorira* pGorira)override;
	void Damage(CG_Gorira* pGorira)override;
	void Wait(CG_Gorira* pGorira)override;
};
#endif