//===============================================================================
//
//  �X�e�[�W1�{�X(G���[��)�̏�ԊǗ�(stage1_boss_state.cpp)
//								����F���n�O��
// 
//===============================================================================

#include "stage1_boss.h"

//�ʏ��Ԃ̃X�e�[�g
void Stage1Boss_Nutoral::Move([[maybe_unused]] CG_Gorira* pGorira)
{
	pGorira->Move();
}
void Stage1Boss_Nutoral::Attack([[maybe_unused]] CG_Gorira* pGorira)
{
	pGorira->DoAttack();
}
void Stage1Boss_Nutoral::Damage([[maybe_unused]] CG_Gorira* pGorira, int value)
{
	pGorira->Damaged(value);
}
void Stage1Boss_Nutoral::Wait([[maybe_unused]] CG_Gorira* pGorira)
{

}

//�U����Ԃ̃X�e�[�g
void Stage1Boss_Attack::Move([[maybe_unused]] CG_Gorira* pGorira)
{

}
void Stage1Boss_Attack::Attack([[maybe_unused]] CG_Gorira* pGorira)
{

}
void Stage1Boss_Attack::Damage([[maybe_unused]] CG_Gorira* pGorira, int value)
{
	pGorira->Damaged(value);
}
void Stage1Boss_Attack::Wait([[maybe_unused]] CG_Gorira* pGorira)
{

}

//��_���[�W��Ԃ̃X�e�[�g
void Stage1Boss_Damage::Move([[maybe_unused]] CG_Gorira* pGorira)
{

}
void Stage1Boss_Damage::Attack([[maybe_unused]] CG_Gorira* pGorira)
{

}
void Stage1Boss_Damage::Damage([[maybe_unused]] CG_Gorira* pGorira, int value)
{
	pGorira->Damaged(value);
}
void Stage1Boss_Damage::Wait([[maybe_unused]] CG_Gorira* pGorira)
{

}

//���S��Ԃ̃X�e�[�g
void Stage1Boss_Death::Move([[maybe_unused]] CG_Gorira* pGorira)
{

}
void Stage1Boss_Death::Attack([[maybe_unused]] CG_Gorira* pGorira)
{

}
void Stage1Boss_Death::Damage([[maybe_unused]] CG_Gorira* pGorira, int value)
{

}
void Stage1Boss_Death::Wait([[maybe_unused]] CG_Gorira* pGorira)
{

}