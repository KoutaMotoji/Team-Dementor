//===============================================================================
//
//  �X�e�[�W1�{�X(G���[��)�̏�ԊǗ�(stage1_boss_state.cpp)
//								����F���n�O��
// 
//===============================================================================

#include "stage1_boss.h"

//�ʏ��Ԃ̃X�e�[�g
void Stage1Boss_Nutoral::Move(CG_Gorira* pGorira)
{
	pGorira->Move();
}
void Stage1Boss_Nutoral::Attack(CG_Gorira* pGorira)
{
	pGorira->DoAttack();
}
void Stage1Boss_Nutoral::Damage(CG_Gorira* pGorira)
{
	pGorira->Damaged();
}

//�U����Ԃ̃X�e�[�g
void Stage1Boss_Attack::Move(CG_Gorira* pGorira)
{

}
void Stage1Boss_Attack::Attack(CG_Gorira* pGorira)
{

}
void Stage1Boss_Attack::Damage(CG_Gorira* pGorira)
{

}

//��_���[�W��Ԃ̃X�e�[�g
void Stage1Boss_Damage::Move(CG_Gorira* pGorira)
{

}
void Stage1Boss_Damage::Attack(CG_Gorira* pGorira)
{

}
void Stage1Boss_Damage::Damage(CG_Gorira* pGorira)
{
	pGorira->Damaged();
}

//���S��Ԃ̃X�e�[�g
void Stage1Boss_Death::Move(CG_Gorira* pGorira)
{

}
void Stage1Boss_Death::Attack(CG_Gorira* pGorira)
{

}
void Stage1Boss_Death::Damage(CG_Gorira* pGorira)
{

}