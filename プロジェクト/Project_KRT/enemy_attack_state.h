//===============================================================================
//
//  �G���G�̍U��AI�N���X(enemy_attack_state.h)
//								����F��|�
// 
//===============================================================================

#ifndef _GORIRA_ATTACKSTATE_H_
#define _GORIRA_ATTACKSTATE_H_

#include "main.h"
#include "enemy.h"

class Enemy_AI
{
public:
	Enemy_AI() : m_Timer(0), m_bDoing(false), m_CoolTime(0) {};
	~Enemy_AI() = default;
	void AI_Init();
	void AI_Update([[maybe_unused]] CEnemy* pEnemy);
	void AI_DoFinish() { m_bDoing = false; }
	void FinishAction();

private:
	void SetNextAction([[maybe_unused]] CEnemy* pEnemy);		//���̍s��������
	void SetThinkValue();		//�v�l����Ԋu��ݒ�
	bool SearchPlayer([[maybe_unused]] CEnemy* pEnemy);		//�����ꍇ��true��Ԃ�
	bool GetIsThinking() { return m_Timer <= 0; }
	int m_Timer;
	bool m_bDoing;
	int m_CoolTime;    // �U����N�[���^�C��
};

//========================================================================================================
//�G���G�̊e�U��
class E_AttackBehavior	//�U���X�e�[�g���N���X
{
private:

protected:

public:
	E_AttackBehavior() {};
	virtual void AttackInit([[maybe_unused]] CEnemy* pEnemy) = 0;
	virtual void AttackUninit([[maybe_unused]] CEnemy* pEnemy) = 0;
	virtual void AttackUpdate([[maybe_unused]] CEnemy* pEnemy) = 0;
	virtual void AttackFinish([[maybe_unused]] CEnemy* pEnemy) = 0;
};

class E_Attack_None : public E_AttackBehavior		//��U�����
{
public:
	void AttackInit([[maybe_unused]] CEnemy* pEnemy)override {};
	void AttackUninit([[maybe_unused]] CEnemy* pEnemy)override {};
	void AttackUpdate([[maybe_unused]] CEnemy* pEnemy)override {};
	void AttackFinish([[maybe_unused]] CEnemy* pEnemy)override {};
};

class E_Attack_Normal : public E_AttackBehavior	//�ʏ�U��
{
public:
	void AttackInit([[maybe_unused]] CEnemy* pEnemy)override;
	void AttackUninit([[maybe_unused]] CEnemy* pEnemy)override {};
	void AttackUpdate([[maybe_unused]] CEnemy* pEnemy)override;
	void AttackFinish([[maybe_unused]] CEnemy* pEnemy)override {};

};

class E_Attack_Dive : public E_AttackBehavior	//�ʏ��э���
{
public:
	void AttackInit([[maybe_unused]] CEnemy* pEnemy)override;
	void AttackUninit([[maybe_unused]] CEnemy* pEnemy)override {};
	void AttackUpdate([[maybe_unused]] CEnemy* pEnemy)override;
	void AttackFinish([[maybe_unused]] CEnemy* pEnemy)override;

private:
	void SlerpRotatedPosition([[maybe_unused]] CEnemy* pEnemy, float frame);
	int m_NowFrame;			//���݂̕�ԃt���[��
	int m_DestFrame;		//��ԃt���[���̍ő�l
	D3DXVECTOR3 m_LastPos;
	D3DXVECTOR3 m_LastPlayerPos;
	D3DXVECTOR3 m_Dir;

	D3DXQUATERNION quat;
};
#endif 
