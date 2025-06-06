//===============================================================================
//
//  プレイヤー処理(playerX.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "xxx_player.h"



//通常時のステート
void State_Nutoral::Attack(CPlayerX* pPlayer)	{

}
void State_Nutoral::Parry(CPlayerX* pPlayer)	{

}
void State_Nutoral::Move(CPlayerX* pPlayer)
{
	pPlayer->PMove(CManager::GetInstance()->GetCamera()->GetRotZ());
	pPlayer->EnemyCollision();
}

//攻撃時のステート
void State_Attack::Attack(CPlayerX* pPlayer)
{
	pPlayer->ToEnemyAttack();
	pPlayer->PAttackInfo();
}
void State_Attack::Parry(CPlayerX* pPlayer)
{

}
void State_Attack::Move(CPlayerX* pPlayer)
{
	//攻撃時は移動不可のため移動の機能を実装しない
}


//パリィ時のステート
void State_Parry::Attack(CPlayerX* pPlayer)
{

}
void State_Parry::Parry(CPlayerX* pPlayer)
{
	//パリィ状態の時のみ通す処理
	if (pPlayer->GetNowMotion() != CPlayerX::MOTION_PARRY&& pPlayer->GetNowMotion() != CPlayerX::MOTION_PARRY_ATTACK && pPlayer->GetNextMotion() != CPlayerX::MOTION_PARRY_ATTACK)
	{
		pPlayer->CCharacter::SetNextMotion(CPlayerX::MOTION_PARRY_STAY);
	}
	pPlayer->SetParry();
	if (CManager::GetInstance()->GetJoypad()->GetRelease(CJoypad::JOYPAD_RIGHT_SHOULDER) ||
		CManager::GetInstance()->GetKeyboard()->GetRelease(DIK_L))
	{
		pPlayer->CCharacter::SetNextMotion(CPlayerX::MOTION_NUTORAL);
		pPlayer->SetState( std::make_shared<State_Nutoral>());
	}
}
void State_Parry::Move(CPlayerX* pPlayer)
{

}

//被ダメージ時のステート
void State_Damage::Attack(CPlayerX* pPlayer)
{

}
void State_Damage::Parry(CPlayerX* pPlayer)
{
	
}
void State_Damage::Move(CPlayerX* pPlayer)
{

}