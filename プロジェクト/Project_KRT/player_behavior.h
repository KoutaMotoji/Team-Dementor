//===============================================================================
//
//  �v���C���[�̘r��ԊǗ��N���X(player_armState.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _PLAYER_BEHAVIOR_H_
#define _PLAYER_BEHAVIOR_H_

#include "main.h"
#include "xxx_player.h"

//========================================================================================================
//�v���C���[�̘r�ɂ���ē���U����ς���p�̃X�e�[�g

class ExAttack_State
{
public:
	virtual void Ex3(CPlayerX* pPlayer) = 0;
	virtual void Ex6(CPlayerX* pPlayer) = 0;
};

class ExAttack_Normal : public ExAttack_State
{
public:
	void Ex3(CPlayerX* pPlayer)override;
	void Ex6(CPlayerX* pPlayer)override;
};

class ExAttack_Gorira : public ExAttack_State
{
public:
	void Ex3(CPlayerX* pPlayer)override;
	void Ex6(CPlayerX* pPlayer)override;
};

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
	static std::shared_ptr<ExAttack_State> m_pExState;
public:
	bool m_bUse;
	int m_MyMotionNum;

	AttackBehavior(MyInfo info = { false,1 }) :m_bUse(info.use), m_MyMotionNum(info.motion_num) {};
	virtual void NextAttack(CPlayerX* pPlayer) = 0;
	virtual void UseDisable() {}
	bool GetUse() { return m_bUse; }
	int GetMyMotionNum() { return m_MyMotionNum; }
	void SetExState(std::shared_ptr<ExAttack_State> pState)	{ 
		if (m_pExState == nullptr)
		{
			m_pExState = std::make_shared<ExAttack_Normal>();
		}
		m_pExState = pState;
	}
};


class Attack_None : public AttackBehavior		//��U�����
{
public:
	Attack_None(MyInfo info = { true,CPlayerX::MOTION_NUTORAL }) :AttackBehavior(info) {}
	void NextAttack([[maybe_unused]] CPlayerX* pPlayer)override;
	void UseDisable()override { m_bUse = false; }

};
class Attack_Normal1 : public AttackBehavior	//�ʏ�1�i��
{
public:
	Attack_Normal1(MyInfo info = { true,CPlayerX::MOTION_ATTACK_N1 }) :AttackBehavior(info) {}
	void NextAttack([[maybe_unused]] CPlayerX* pPlayer)override;
	void UseDisable()override { m_bUse = false; }

};
class Attack_Normal2 : public AttackBehavior	//�ʏ�2�i��
{
public:
	Attack_Normal2(MyInfo info = { true,CPlayerX::MOTION_ATTACK_N2 }) :AttackBehavior(info) {}
	void NextAttack([[maybe_unused]] CPlayerX* pPlayer)override;
	void UseDisable()override { m_bUse = false; }

};
class Attack_Normal3 : public AttackBehavior	//�ʏ�3�i��
{
public:
	Attack_Normal3(MyInfo info = { true,CPlayerX::MOTION_ATTACK_N3 }) :AttackBehavior(info) {}
	void NextAttack([[maybe_unused]] CPlayerX* pPlayer)override;
	void UseDisable()override { m_bUse = false; }
};
class Attack_Normal4 : public AttackBehavior	//�ʏ�4�i��
{
public:
	Attack_Normal4(MyInfo info = { true,CPlayerX::MOTION_ATTACK_N4 }) :AttackBehavior(info) {}
	void NextAttack([[maybe_unused]] CPlayerX* pPlayer)override;
	void UseDisable()override { m_bUse = false; }
};
class Attack_Normal5 : public AttackBehavior	//�ʏ�5�i��
{
public:
	Attack_Normal5(MyInfo info = { true,CPlayerX::MOTION_ATTACK_N5 }) :AttackBehavior(info) {}
	void NextAttack([[maybe_unused]] CPlayerX* pPlayer)override;
	void UseDisable()override { m_bUse = false; }
};
class Attack_Normal6 : public AttackBehavior	//�ʏ�6�i��
{
public:
	Attack_Normal6(MyInfo info = { true,CPlayerX::MOTION_ATTACK_N6 }) :AttackBehavior(info) {}
	void NextAttack([[maybe_unused]] CPlayerX* pPlayer)override;
	void UseDisable()override { m_bUse = false; }
};
class Attack_Normal7 : public AttackBehavior	//�ʏ�ŏI�i��
{
public:
	Attack_Normal7(MyInfo info = { true,CPlayerX::MOTION_ATTACK_N7 }) :AttackBehavior(info) {}
	void NextAttack([[maybe_unused]] CPlayerX* pPlayer)override;
	void UseDisable()override { m_bUse = false; }
};
class Attack_Extended3 : public AttackBehavior		//�h��3�i��
{
public:
	Attack_Extended3(MyInfo info = { true,CPlayerX::MOTION_ATTACK_Ex3 }) :AttackBehavior(info) {}
	void NextAttack([[maybe_unused]] CPlayerX* pPlayer)override;
	void UseDisable()override { m_bUse = false; }
};
class Attack_Extended5 : public AttackBehavior		//�h��5�i��
{
public:
	Attack_Extended5(MyInfo info = { true,CPlayerX::MOTION_ATTACK_Ex5 }) :AttackBehavior(info) {}
	void NextAttack([[maybe_unused]] CPlayerX* pPlayer)override;
	void UseDisable()override { m_bUse = false; }
};
class Attack_Extended6 : public AttackBehavior		//�h��6�i��
{
public:
	Attack_Extended6(MyInfo info = { true,CPlayerX::MOTION_ATTACK_Ex6 }) :AttackBehavior(info) {}
	void NextAttack([[maybe_unused]] CPlayerX* pPlayer)override;
	void UseDisable()override { m_bUse = false; }
};

class Attack_ExGorira3 : public AttackBehavior		//�h��5�i��
{
public:
	Attack_ExGorira3(MyInfo info = { true,CPlayerX::MOTION_ATTACK_G_Ex3 }) :AttackBehavior(info) {}
	void NextAttack([[maybe_unused]] CPlayerX* pPlayer)override;
	void UseDisable()override { m_bUse = false; }
};
class Attack_ExGorira4 : public AttackBehavior		//�h��5�i��
{
public:
	Attack_ExGorira4(MyInfo info = { true,CPlayerX::MOTION_ATTACK_G_Ex4 }) :AttackBehavior(info) {}
	void NextAttack([[maybe_unused]] CPlayerX* pPlayer)override;
	void UseDisable()override { m_bUse = false; }
};

class Attack_ExGorira6 : public AttackBehavior		//�h��6�i��
{
public:
	Attack_ExGorira6(MyInfo info = { true,CPlayerX::MOTION_ATTACK_G_Ex6 }) :AttackBehavior(info) {}
	void NextAttack([[maybe_unused]] CPlayerX* pPlayer)override;
	void UseDisable()override { m_bUse = false; }
};

#endif 
