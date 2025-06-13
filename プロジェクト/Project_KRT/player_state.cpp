//===============================================================================
//
//  プレイヤー処理(playerX.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "xxx_player.h"



//通常時のステート
void State_Nutoral::Attack(CPlayerX* pPlayer)	{
	pPlayer->PAttackInfo();
}
void State_Nutoral::Parry(CPlayerX* pPlayer)	{

}
void State_Nutoral::Move(CPlayerX* pPlayer)
{
	pPlayer->PMove(CManager::GetInstance()->GetCamera()->GetRotZ());
	pPlayer->EnemyCollision();
}
void State_Nutoral::ToAttack(CPlayerX* pPlayer) {
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_X) ||
		CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_J))
	{
		pPlayer->CCharacter::SetNextMotion(CPlayerX::MOTION_ATTACK_N1);
		pPlayer->SetState(std::make_shared<State_Attack>());
	}
}
void State_Nutoral::ToParry(CPlayerX* pPlayer)
{
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_RIGHT_SHOULDER) ||
		CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_L))
	{
		pPlayer->CCharacter::SetNextMotion(CPlayerX::MOTION_PARRY);
		pPlayer->SetState(std::make_shared<State_Parry>());
	}
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
void State_Attack::ToAttack(CPlayerX* pPlayer)
{
}
void State_Attack::ToParry(CPlayerX* pPlayer)
{
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_RIGHT_SHOULDER) ||
		CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_L))
	{
		pPlayer->CCharacter::SetNextMotion(CPlayerX::MOTION_PARRY);
		pPlayer->SetState(std::make_shared<State_Parry>());
	}
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
void State_Parry::ToAttack(CPlayerX* pPlayer)
{
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_X) ||
		CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_J))
	{
		pPlayer->CCharacter::SetNextMotion(CPlayerX::MOTION_ATTACK_N1);
		pPlayer->SetState(std::make_shared<State_Attack>());
	}
}
void State_Parry::ToParry(CPlayerX* pPlayer)
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
void State_Damage::ToAttack(CPlayerX* pPlayer)
{

}
void State_Damage::ToParry(CPlayerX* pPlayer)
{

}