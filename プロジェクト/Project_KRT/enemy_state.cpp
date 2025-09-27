//===============================================================================
//
//  雑魚敵の状態管理(enemy_state.cpp)
//								制作：大竹熙
// 
//===============================================================================

#include "enemy.h"

//通常状態のステート
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

//攻撃状態のステート
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

//被ダメージ状態のステート
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

//死亡状態のステート
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