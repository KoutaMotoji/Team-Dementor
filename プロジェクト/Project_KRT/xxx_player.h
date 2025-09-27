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
#include "weapon.h"

#include "manager.h"

//�O���錾
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

	static constexpr int MAX_LIFE = 1000;			//�̗�

	D3DXVECTOR3 m_OldPos;					//�ߋ��̈ʒu
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

	void FloorCollision();					//���Ƃ̓����蔻��
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
	virtual void Move([[maybe_unused]] CPlayerX* pPlayer) = 0;
	virtual void Attack([[maybe_unused]]CPlayerX* pPlayer) = 0;
	virtual void Parry([[maybe_unused]]CPlayerX* pPlayer) = 0;
	virtual void ToAttack([[maybe_unused]]CPlayerX* pPlayer) = 0;
	virtual void ToParry([[maybe_unused]]CPlayerX* pPlayer) = 0;
private:
};

class State_Nutoral : public PlayerState
{	//�ʏ�X�e�[�g
public:
	void Move([[maybe_unused]]CPlayerX* pPlayer)override;
	void Attack([[maybe_unused]]CPlayerX* pPlayer)override;
	void Parry([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToAttack([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToParry([[maybe_unused]]CPlayerX* pPlayer)override;
private:
};

class State_Attack : public PlayerState
{	//�U���X�e�[�g
public:
	void Move([[maybe_unused]]CPlayerX* pPlayer)override;
	void Attack([[maybe_unused]]CPlayerX* pPlayer)override;
	void Parry([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToAttack([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToParry([[maybe_unused]]CPlayerX* pPlayer)override;
private:
};

class State_Parry : public PlayerState
{	//�p���B�X�e�[�g(�p���B�\�����p���B�ҋ@���p���B�����܂�)
public:
	void Move([[maybe_unused]]CPlayerX* pPlayer)override;
	void Attack([[maybe_unused]]CPlayerX* pPlayer)override;
	void Parry([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToAttack([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToParry([[maybe_unused]]CPlayerX* pPlayer)override;
private:
};

class State_ParryAttack : public PlayerState
{	//�p���B�X�e�[�g(�p���B�\�����p���B�ҋ@���p���B�����܂�)
public:
	void Move([[maybe_unused]]CPlayerX* pPlayer)override {};
	void Attack([[maybe_unused]]CPlayerX* pPlayer)override {};
	void Parry([[maybe_unused]]CPlayerX* pPlayer)override {};
	void ToAttack([[maybe_unused]]CPlayerX* pPlayer)override {};
	void ToParry([[maybe_unused]]CPlayerX* pPlayer)override {};

private:

};
class State_Damage : public PlayerState
{	//��_���[�W�X�e�[�g
public:
	void Move([[maybe_unused]]CPlayerX* pPlayer)override;
	void Attack([[maybe_unused]]CPlayerX* pPlayer)override;
	void Parry([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToAttack([[maybe_unused]]CPlayerX* pPlayer)override;
	void ToParry([[maybe_unused]]CPlayerX* pPlayer)override;
private:
};

//========================================================================================================
//���b�N�I����ԊǗ��N���X

class LockOn_State
{	//���b�N�I���X�e�[�g���N���X�@
public:
	//���̏�ԂɂȂ邱�Ƃ͖����̂ŏ������z�֐�������
	virtual void Swicth([[maybe_unused]]CPlayerX* pPlayer) = 0;
	virtual void UpdateCam([[maybe_unused]]CPlayerX* pPlayer) = 0;
private:
};

class LockEnable : public LockOn_State
{	//���b�N�I����ԃN���X
public:
	static D3DXVECTOR3 s_savedPosV; // �ۑ��p�̃J�������_
	static D3DXVECTOR3 s_savedPosR; // �ۑ��p�̃J���������_
	virtual void Swicth([[maybe_unused]]CPlayerX* pPlayer)override;
	virtual void UpdateCam([[maybe_unused]]CPlayerX* pPlayer)override;
private:
};

class LockDisable : public LockOn_State
{	//�񃍃b�N�I����ԃN���X
public:
	virtual void Swicth([[maybe_unused]]CPlayerX* pPlayer)override;
	virtual void UpdateCam([[maybe_unused]]CPlayerX* pPlayer)override;
private:
};

//========================================================================================================


#endif