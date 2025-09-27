//===============================================================================
//
//  �G�l�~�[����(enemy.h)
//								����F��|�
// 
//===============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "character.h"
#include "debug_line.h"

#include "manager.h"

//�O���錾
class Enemy_State;
class CStage1BossGaugeLife;
class E_AttackBehavior;
class Enemy_AI;
class EnemyAI;

class CEnemy :public CCharacter
{
public:
	CEnemy();					//�R���X�g���N�^
	~CEnemy()override {};		//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��

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

	void BeDamaged();			//�O������Ăԗp
	void Damaged();				//State�̒��ŌĂԗp
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

	std::vector<std::shared_ptr<CHitCircle>> m_pHC_BodyCollision;	//�~�̓����蔻��z��

	std::shared_ptr<EnemyAI> m_pEnemyAI;
	std::shared_ptr<Enemy_State> m_State;
	std::shared_ptr<Enemy_AI>m_bEnemyAI;
	std::shared_ptr<E_AttackBehavior> m_AttackState;
	//�X�e�[�^�X�p�萔
	CStage1BossGaugeLife* m_HPGauge;
	D3DXVECTOR3 m_OldPos;					//�ߋ��̈ʒu

	void FloorCollision();					//���Ƃ̓����蔻��
	bool m_bAttackCt;
	int m_nAttackcnt;
	bool m_moveFlag;
	bool m_bStopFlag;
	int m_nLife;
	int m_nTime;
	int m_Direction;
	D3DXVECTOR3 m_TargetPos;  // �ːi���̖ړI�n
	bool m_bChasing = false;  // �ːi���t���O

	// ���S / �����Ǘ�
	bool m_bDead = false;       // ���S�t���O
	float m_fDeathTimer = 0.0f; // ���S�o�ߎ���
	bool m_bDying = false;               // ���S�A�j�����t���O�i�A�j���Đ����j
	bool m_bHidden = false;              // ���f����\���i���S�A�j����A�����҂��j
	bool m_bDeathAnimFinished = false;   // ���S�A�j����EndMotion�ŏI�������
	int  m_RespawnTimerFrames = 0;       // �����J�E���g�i�t���[���j
	int  m_RespawnDelayFrames = 60 * 5;  // �����܂ł̃t���[���i��: 5�b�j
	bool m_bCanMove = false;
	bool m_bCanAttack = false;
	bool m_bStunned = false;   // ��e�����ǂ���
	int  m_StunTimer = 0;      // ��e�d���̎c��t���[��
	bool m_bItemDropped = false;   // �A�C�e���𗎂Ƃ��t���O
	bool m_bItemCreated = false;   // ���ۂɐ����������t���O	
	D3DXVECTOR3 m_RespawnPos; // �Œ蕜���ʒu�iCreate�ŏ㏑���j
	D3DXVECTOR3 m_WeaponDropPos; // ���S���̍��W�ۑ��p
	bool m_bPendingDropWeapon;
	bool m_bWeaponDropped;
	static int s_nWeaponCount;       // �t�B�[���h��̕��퐔
	static const int MAX_WEAPON; // ���
};

//========================================================================================================
//	��ԊǗ��X�e�[�g�N���X
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