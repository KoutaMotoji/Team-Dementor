//===============================================================================
//
//  プレイヤーの行動管理(player_behavior.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "player_behavior.h"

std::shared_ptr<ExAttack_State>AttackBehavior:: m_pExState = nullptr;

void ExAttack_Normal::Ex3(CPlayerX* pPlayer)
{
	pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_Ex3);
	pPlayer->SetAttackBehavior(std::make_shared<Attack_Extended3>());
}

void ExAttack_Normal::Ex6(CPlayerX* pPlayer)
{
	pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_Ex6);
	pPlayer->SetAttackBehavior(std::make_shared<Attack_Extended6>());
}

void ExAttack_Gorira::Ex3(CPlayerX* pPlayer)
{
	pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_G_Ex3);
	pPlayer->SetAttackBehavior(std::make_shared<Attack_ExGorira3>());
}

void ExAttack_Gorira::Ex6(CPlayerX* pPlayer)
{
	pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_G_Ex6_toJump);
	pPlayer->SetAttackBehavior(std::make_shared<Attack_ExGorira6>());
}

//キー入力をまとめる
bool AttackBehavior::InputNormal()	
{
	return (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_X) || CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_J));
}
bool AttackBehavior::InputExtended()
{
	return (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_Y) || CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_K));
}

void Attack_None::NextAttack(CPlayerX* pPlayer)
{
	if (InputNormal()) {
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_N1);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_Normal1>());
	}
}
void Attack_Normal1::NextAttack(CPlayerX* pPlayer)
{
	if (InputNormal())	{
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_N2);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_Normal2>());
	}
}
void Attack_Normal2::NextAttack(CPlayerX* pPlayer)
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
void Attack_Normal3::NextAttack(CPlayerX* pPlayer)
{
	if (InputNormal()) {
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_N4);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_Normal4>());
	}
}
void Attack_Normal4::NextAttack(CPlayerX* pPlayer)
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
void Attack_Normal5::NextAttack(CPlayerX* pPlayer)
{
	if (InputNormal()) {
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_N6);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_Normal6>());
	}
}
void Attack_Normal6::NextAttack(CPlayerX* pPlayer)
{
	if (InputNormal()) {
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_N7);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_Normal7>());
	}
}
void Attack_Normal7::NextAttack(CPlayerX* pPlayer)
{
	//通常攻撃の最終段なのでなにもしない
}
void Attack_Extended3::NextAttack(CPlayerX* pPlayer)
{
	//派生攻撃の区切り段なのでなにもしない
}
void Attack_Extended5::NextAttack(CPlayerX* pPlayer)
{
	if (InputExtended()) {
		m_pExState->Ex6(pPlayer);

	}
}
void Attack_Extended6::NextAttack(CPlayerX* pPlayer)
{
	//派生攻撃の最終段なのでなにもしない
}
void Attack_ExGorira3::NextAttack(CPlayerX* pPlayer)
{
	if (InputExtended()) {
		pPlayer->SetNextMotion(CPlayerX::MOTION_ATTACK_G_Ex4);
		pPlayer->SetAttackBehavior(std::make_shared<Attack_ExGorira4>());
	}
}
void Attack_ExGorira4::NextAttack(CPlayerX* pPlayer)
{
	//派生攻撃の最終段なのでなにもしない
}
void Attack_ExGorira6::NextAttack(CPlayerX* pPlayer)
{
	//派生攻撃の最終段なのでなにもしない
}