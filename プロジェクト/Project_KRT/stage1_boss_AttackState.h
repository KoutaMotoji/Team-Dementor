//===============================================================================
//
//  �S�����̍U��AI�N���X(stage1_boss_AttackState.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _GORIRA_ATTACKSTATE_H_
#define _GORIRA_ATTACKSTATE_H_

#include "main.h"
#include "stage1_boss.h"

class Gorira_AI
{
public:
	Gorira_AI() :m_bDoing(false){};
	~Gorira_AI() = default;
	void AI_Init();
	void AI_Update([[maybe_unused]] CG_Gorira* pGorira);
	void AI_DoFinish() { m_bDoing = false; }

private:
	void SetNextAction([[maybe_unused]] CG_Gorira* pGorira);		//���̍s��������
	void SetThinkValue();		//�v�l����Ԋu��ݒ�
	bool SearchPlayer([[maybe_unused]] CG_Gorira* pGorira);		//�����ꍇ��true��Ԃ�
	bool GetIsThinking() { return m_Timer <= 0; }
	int m_Timer;
	bool m_bDoing;
};

//========================================================================================================
//�{�X�̊e�U��
class G_AttackBehavior	//�U���X�e�[�g���N���X
{
private:

protected:

public:
	G_AttackBehavior() {};
	virtual void G_AttackInit([[maybe_unused]] CG_Gorira* pGorira) = 0;
	virtual void G_AttackUninit([[maybe_unused]] CG_Gorira* pGorira) = 0;

	virtual void G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira) = 0;
	virtual void G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira) = 0;
};


class G_Attack_None : public G_AttackBehavior		//��U�����
{
public:
	void G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)override {};
	void G_AttackUninit([[maybe_unused]] CG_Gorira* pGorira)override {};
	void G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira)override {};
	void G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)override {};
};
class G_Attack_Normal : public G_AttackBehavior	//�ʏ�U��
{
public:
	void G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackUninit([[maybe_unused]] CG_Gorira* pGorira)override {};
	void G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)override {};

};
class G_Attack_Dive : public G_AttackBehavior	//�ʏ��э���
{
public:
	void G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackUninit([[maybe_unused]] CG_Gorira* pGorira)override {};
	void G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)override;

private:
	void SlerpRotatedPosition([[maybe_unused]] CG_Gorira* pGorira,float frame);
	int m_NowFrame;			//���݂̕�ԃt���[��
	int m_DestFrame;		//��ԃt���[���̍ő�l
	D3DXVECTOR3 m_LastPos;
	D3DXVECTOR3 m_LastPlayerPos;

	D3DXQUATERNION quat;
};
class G_Attack_Spin : public G_AttackBehavior	//�ʏ�r��]
{
public:
	void G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackUninit([[maybe_unused]] CG_Gorira* pGorira)override {};
	void G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)override {};

};
class G_Attack_DoubleHammer : public G_AttackBehavior	//�_�u���X���b�W�n���}�[
{
public:
	void G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackUninit([[maybe_unused]] CG_Gorira* pGorira)override {}
	void G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)override {};

};

#endif 
