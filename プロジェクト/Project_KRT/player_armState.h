//===============================================================================
//
//  �v���C���[�̘r��ԊǗ��N���X(player_armState.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _PLAYER_ARMSTATE_H_
#define _PLAYER_ARMSTATE_H_

#include "main.h"
#include "xxx_player.h"

//�r��ԊǗ��N���X�̊��N���X
class PlayerArm_State
{
private:

public:
	//�r�̏�Ԃɂ���ĕω����郂�[�V������ʁX�Ɉ����p�̊֐�(�U�����[�V�����͕ʂŊǗ�)
	virtual void WalkMotion(CPlayerX* pPlayer) = 0;
	virtual void ParryMotion(CPlayerX* pPlayer) = 0;
	virtual void ParryStayMotion(CPlayerX* pPlayer) = 0;
};

//�ʏ�r�̎��̐U�镑�����Ǘ�����N���X
class Arm_Normal : public PlayerArm_State
{
	void WalkMotion(CPlayerX* pPlayer)override;
	void ParryMotion(CPlayerX* pPlayer) override;
	void ParryStayMotion(CPlayerX* pPlayer) override;
};

//�S�����r�̎��̐U�镑�����Ǘ�����N���X
class Arm_Gorira : public PlayerArm_State
{
	void WalkMotion(CPlayerX* pPlayer)override;
	void ParryMotion(CPlayerX* pPlayer) override;
	void ParryStayMotion(CPlayerX* pPlayer) override;
};


#endif 
