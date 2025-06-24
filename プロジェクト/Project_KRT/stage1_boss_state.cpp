//===============================================================================
//
//  ステージ1ボス(Gリーラ)の状態管理(stage1_boss_state.cpp)
//								制作：元地弘汰
// 
//===============================================================================

#include "stage1_boss.h"

//通常状態のステート
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

//攻撃状態のステート
void Stage1Boss_Attack::Move(CG_Gorira* pGorira)
{

}
void Stage1Boss_Attack::Attack(CG_Gorira* pGorira)
{

}
void Stage1Boss_Attack::Damage(CG_Gorira* pGorira)
{

}

//被ダメージ状態のステート
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

//死亡状態のステート
void Stage1Boss_Death::Move(CG_Gorira* pGorira)
{

}
void Stage1Boss_Death::Attack(CG_Gorira* pGorira)
{

}
void Stage1Boss_Death::Damage(CG_Gorira* pGorira)
{

}