//===============================================================================
//
//  ƒvƒŒƒCƒ„[‚Ìs“®ŠÇ—(player_behavior.cpp)
//								§ìFŒ³’nO‘¿
// 
//===============================================================================
#include "player_behavior.h"

std::shared_ptr<ExAttack_State>AttackBehavior:: m_pExState = nullptr;

void ExAttack_Normal::Ex3([[maybe_unused]] CPlayerX* pPlayer)
{
	pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_Ex3);
	pPlayer->SetAttackBehavior(std::make_shared<Attack_Extended3>());
}

void ExAttack_Normal::Ex6([[maybe_unused]] CPlayerX* pPlayer)
{
	pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_Ex6);
	pPlayer->SetAttackBehavior(std::make_shared<Attack_Extended6>());
}

void ExAttack_Gorira::Ex3([[maybe_unused]] CPlayerX* pPlayer)
{
	pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_G_Ex3);
	pPlayer->SetAttackBehavior(std::make_shared<Attack_ExGorira3>());
}

void ExAttack_Gorira::Ex6([[maybe_unused]] CPlayerX* pPlayer)
{
	pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_G_Ex6_toJump);
	pPlayer->SetAttackBehavior(std::make_shared<Attack_ExGorira6>());
}

//ƒL[“ü—Í‚ğ‚Ü‚Æ‚ß‚é
bool AttackBehavior::InputNormal()	
{
	return (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_X) || CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_J));
}
bool AttackBehavior::InputExtended()
{
	return (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_Y) || CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_K));
}

void Attack_None::NextAttack([[maybe_unused]] CPlayerX* pPlayer)
{
	if (InputNormal()) {
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_N1);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_Normal1>());
	}
}
void Attack_Normal1::NextAttack([[maybe_unused]] CPlayerX* pPlayer)
{
	if (InputNormal())	{
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_N2);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_Normal2>());
	}
}
void Attack_Normal2::NextAttack([[maybe_unused]] CPlayerX* pPlayer)
{
	if (InputNormal()) {
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_N3);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_Normal3>());
	}
	if (InputExtended()) 
	{
		m_pExState->Ex3(pPlayer);
	}
}
void Attack_Normal3::NextAttack([[maybe_unused]] CPlayerX* pPlayer)
{
	if (InputNormal()) {
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_N4);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_Normal4>());
	}
}
void Attack_Normal4::NextAttack([[maybe_unused]] CPlayerX* pPlayer)
{
	if (InputNormal()) {
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_N5);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_Normal5>());
	}
	if (InputExtended()) {
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_Ex5);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_Extended5>());
	}
}
void Attack_Normal5::NextAttack([[maybe_unused]] CPlayerX* pPlayer)
{
	if (InputNormal()) {
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_N6);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_Normal6>());
	}
}
void Attack_Normal6::NextAttack([[maybe_unused]] CPlayerX* pPlayer)
{
	if (InputNormal()) {
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_N7);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_Normal7>());
	}
}
void Attack_Normal7::NextAttack([[maybe_unused]] CPlayerX* pPlayer)
{
	//’ÊíUŒ‚‚ÌÅI’i‚È‚Ì‚Å‚È‚É‚à‚µ‚È‚¢
}
void Attack_Extended3::NextAttack([[maybe_unused]] CPlayerX* pPlayer)
{
	//”h¶UŒ‚‚Ì‹æØ‚è’i‚È‚Ì‚Å‚È‚É‚à‚µ‚È‚¢
}
void Attack_Extended5::NextAttack([[maybe_unused]] CPlayerX* pPlayer)
{
	if (InputExtended()) {
		m_pExState->Ex6(pPlayer);

	}
}
void Attack_Extended6::NextAttack([[maybe_unused]] CPlayerX* pPlayer)
{
	//”h¶UŒ‚‚ÌÅI’i‚È‚Ì‚Å‚È‚É‚à‚µ‚È‚¢
}
void Attack_ExGorira3::NextAttack([[maybe_unused]] CPlayerX* pPlayer)
{
	if (InputExtended()) {
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_G_Ex4);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_ExGorira4>());
	}
}
void Attack_ExGorira4::NextAttack([[maybe_unused]] CPlayerX* pPlayer)
{
	//”h¶UŒ‚‚ÌÅI’i‚È‚Ì‚Å‚È‚É‚à‚µ‚È‚¢
}
void Attack_ExGorira6::NextAttack([[maybe_unused]] CPlayerX* pPlayer)
{
	//”h¶UŒ‚‚ÌÅI’i‚È‚Ì‚Å‚È‚É‚à‚µ‚È‚¢
}