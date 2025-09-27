//===============================================================================
//
//  �X�e�[�W1�{�X����(stage1_boss.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _STAGE1_BOSS_H_
#define _STAGE1_BOSS_H_

#include "main.h"
#include "character.h"
#include "debug_line.h"

#include "manager.h"

//�O���錾
class Stage1Boss_State;
class CStage1BossGaugeLife;
class G_AttackBehavior;
class Gorira_AI;

class CG_Gorira :public CCharacter
{
public:
	CG_Gorira();						//�R���X�g���N�^
	~CG_Gorira()override {};		//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��

	void DoAttack();
	void Move();
	bool EndMotion()override;

	_forceinline void SetState(std::shared_ptr<Stage1Boss_State>pState) {
		if (m_State != nullptr) {
			m_State = nullptr;
		}
		m_State = pState;
	}
	_forceinline void SetAttackState(std::shared_ptr<G_AttackBehavior>pState);
	inline std::vector<int> GetAttackNumVec() { return m_AttackMotionNum; }
	void BeDamaged(int value);			//�O������Ăԗp
	void Damaged(int value);				//State�̒��ŌĂԗp
	static CG_Gorira* Create(D3DXVECTOR3 pos);

	enum
	{
		MOTION_NUTORAL = 0,
		MOTION_WALK,
		MOTION_ATTACK,
		MOTION_JUMP,
		MOTION_LANDING,
		MOTION_DAMAGE_BIG,
		MOTION_DAMAGE_SMALL,
		MOTION_DOUBLEHUMMER,
		MOTION_SWING,
		MOTION_BIGJUMP,
		MOTION_STAMP,
		MOTION_STAN,
		MOTION_BACKSTEP
	};
	std::vector<std::shared_ptr<CHitCircle>> GetBodyHitCircle() { return m_pHC_BodyCollision; }
private:
	std::shared_ptr<CDebugLine>m_pDebugLine;
	std::vector < std::shared_ptr<CDebugLine>>m_pDL_BodyCollision;

	std::vector<std::shared_ptr<CHitCircle>> m_pHC_BodyCollision;	//�~�̓����蔻��z��

	std::shared_ptr<Stage1Boss_State> m_State;
	std::shared_ptr<Gorira_AI>m_bBossAI;
	std::shared_ptr<G_AttackBehavior> m_AttackState;
	//�X�e�[�^�X�p�萔
	CStage1BossGaugeLife* m_HPGauge;
	D3DXVECTOR3 m_OldPos;					//�ߋ��̈ʒu

	void FloorCollision();					//���Ƃ̓����蔻��
	bool m_bAttackCt;
	int m_nAttackcnt;
	bool m_moveFlag;
	int m_nLife;
	std::vector<int> m_AttackMotionNum;
};

//========================================================================================================
//	��ԊǗ��X�e�[�g�N���X
class Stage1Boss_State
{
public:
	virtual void Move(CG_Gorira* pGorira) = 0;
	virtual void Attack(CG_Gorira* pGorira) = 0;
	virtual void Damage(CG_Gorira* pGorira, int value) = 0;
	virtual void Wait(CG_Gorira* pGorira) = 0;
};

class Stage1Boss_Nutoral : public Stage1Boss_State
{
public:
	void Move(CG_Gorira* pGorira)override;
	void Attack(CG_Gorira* pGorira)override;
	void Damage(CG_Gorira* pGorira, int value)override;
	void Wait(CG_Gorira* pGorira)override;
};

class Stage1Boss_Attack : public Stage1Boss_State
{
public:
	void Move(CG_Gorira* pGorira)override;
	void Attack(CG_Gorira* pGorira)override;
	void Damage(CG_Gorira* pGorira, int value)override;
	void Wait(CG_Gorira* pGorira)override;
};

class Stage1Boss_Damage : public Stage1Boss_State
{
public:
	void Move(CG_Gorira* pGorira)override;
	void Attack(CG_Gorira* pGorira)override;
	void Damage(CG_Gorira* pGorira, int value)override;
	void Wait(CG_Gorira* pGorira)override;
};

class Stage1Boss_Death : public Stage1Boss_State
{
public:
	void Move(CG_Gorira* pGorira)override;
	void Attack(CG_Gorira* pGorira)override;
	void Damage(CG_Gorira* pGorira, int value)override;
	void Wait(CG_Gorira* pGorira)override;
};
#endif