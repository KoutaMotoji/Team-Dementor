//===============================================================================
//
//  �G���G�̏�ԊǗ�(enemy_state.cpp)
//								����F��|�
// 
//===============================================================================

#include "enemy.h"

//�ʏ��Ԃ̃X�e�[�g
void Enemy_Nutoral::Move([[maybe_unused]] CEnemy* pEnemy)
{
	pEnemy->Move();
}
void Enemy_Nutoral::Attack([[maybe_unused]] CEnemy* pEnemy)
{
	pEnemy->DoAttack();
}
void Enemy_Nutoral::Damage([[maybe_unused]] CEnemy* pEnemy)
{
	pEnemy->Damaged();
}
void Enemy_Nutoral::Wait([[maybe_unused]] CEnemy* pEnemy)
{

}

//�U����Ԃ̃X�e�[�g
void Enemy_Attack::Move([[maybe_unused]] CEnemy* pEnemy)
{

}
void Enemy_Attack::Attack([[maybe_unused]] CEnemy* pEnemy)
{

}
void Enemy_Attack::Damage([[maybe_unused]] CEnemy* pEnemy)
{

}
void Enemy_Attack::Wait([[maybe_unused]] CEnemy* pEnemy)
{

}

//��_���[�W��Ԃ̃X�e�[�g
void Enemy_Damage::Move([[maybe_unused]] CEnemy* pEnemy)
{

}
void Enemy_Damage::Attack([[maybe_unused]] CEnemy* pEnemy)
{

}
void Enemy_Damage::Damage([[maybe_unused]] CEnemy* pEnemy)
{
	pEnemy->Damaged();
}
void Enemy_Damage::Wait([[maybe_unused]] CEnemy* pEnemy)
{

}

//���S��Ԃ̃X�e�[�g
void Enemy_Death::Move([[maybe_unused]] CEnemy* pEnemy)
{

}
void Enemy_Death::Attack([[maybe_unused]] CEnemy* pEnemy)
{

}
void Enemy_Death::Damage([[maybe_unused]] CEnemy* pEnemy)
{

}
void Enemy_Death::Wait([[maybe_unused]] CEnemy* pEnemy)
{

}