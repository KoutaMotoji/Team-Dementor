//===============================================================================
//
//  �v���C���[����(playerX.h)
//								����F���n�O��
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

//�O���錾
class CCTBarUI;
class CButtonUI;
class CCharacter;
class CPlayerMask;
class PlayerState;
class AttackBehavior;


class CPlayerX :public CCharacter
{
public:
	CPlayerX(int nPriority = 1);					//�R���X�g���N�^
	~CPlayerX()override;		//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��

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
	//�X�e�[�^�X�p�萔
	static constexpr int MAX_LIFE = 1000;			//�̗�

	D3DXVECTOR3 m_OldPos;					//�ߋ��̈ʒu
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

	void FloorCollision();					//���Ƃ̓����蔻��
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
	//========================			�N�I�[�^�j�I���p		====================================
	D3DXMATRIX m_mtxRot;		//��]�}�g���b�N�X(�ۑ��p)
	D3DXQUATERNION m_quat;		//�N�I�[�^�j�I��
	D3DXVECTOR3 m_vecAxis;		//��]���̃x�N�g��
	float m_fValueRot;			//��]��
};


//========================================================================================================
//�v���C���[��ԊǗ��X�e�[�g�N���X

class PlayerState
{	//�v���C���[�X�e�[�g���N���X�@
public:
	//���̏�ԂɂȂ邱�Ƃ͖����̂ŏ������z�֐�������
	virtual void Move(CPlayerX* pPlayer) = 0;
	virtual void Attack(CPlayerX* pPlayer) = 0;
	virtual void Parry(CPlayerX* pPlayer) = 0;
	virtual void ToAttack(CPlayerX* pPlayer) = 0;
	virtual void ToParry(CPlayerX* pPlayer) = 0;
private:
};

class State_Nutoral : public PlayerState
{	//�ʏ�X�e�[�g
public:
	void Move(CPlayerX* pPlayer)override;
	void Attack(CPlayerX* pPlayer)override;
	void Parry(CPlayerX* pPlayer)override;
	void ToAttack(CPlayerX* pPlayer)override;
	void ToParry(CPlayerX* pPlayer)override;
private:
};

class State_Attack : public PlayerState
{	//�U���X�e�[�g
public:
	void Move(CPlayerX* pPlayer)override;
	void Attack(CPlayerX* pPlayer)override;
	void Parry(CPlayerX* pPlayer)override;
	void ToAttack(CPlayerX* pPlayer)override;
	void ToParry(CPlayerX* pPlayer)override;
private:
};

class State_Parry : public PlayerState
{	//�p���B�X�e�[�g(�p���B�\�����p���B�ҋ@���p���B�����܂�)
public:
	void Move(CPlayerX* pPlayer)override;
	void Attack(CPlayerX* pPlayer)override;
	void Parry(CPlayerX* pPlayer)override;
	void ToAttack(CPlayerX* pPlayer)override;
	void ToParry(CPlayerX* pPlayer)override;
private:
};

class State_ParryAttack : public PlayerState
{	//�p���B�X�e�[�g(�p���B�\�����p���B�ҋ@���p���B�����܂�)
public:
	void Move(CPlayerX* pPlayer)override {};
	void Attack(CPlayerX* pPlayer)override {};
	void Parry(CPlayerX* pPlayer)override {};
	void ToAttack(CPlayerX* pPlayer)override {};
	void ToParry(CPlayerX* pPlayer)override {};

private:

};
class State_AttackWait : public PlayerState
{	//�U���I�������̒i�̍U��or�P�\�I���܂�
public:
	void Move(CPlayerX* pPlayer)override;
	void Attack(CPlayerX* pPlayer)override;
	void Parry(CPlayerX* pPlayer)override;
	void ToAttack(CPlayerX* pPlayer)override;
	void ToParry(CPlayerX* pPlayer)override;
private:
};
class State_Damage : public PlayerState
{	//��_���[�W�X�e�[�g
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
//�v���C���[�̘A���U��
class AttackBehavior
{
private:


protected:

	bool InputNormal();		//�ʏ�U���̓���
	bool InputExtended();	//�h���U���̓���
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