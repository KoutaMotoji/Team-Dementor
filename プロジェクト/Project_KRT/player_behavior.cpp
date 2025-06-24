//===============================================================================
//
//  �v���C���[�̍s���Ǘ�(player_behavior.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "xxx_player.h"


//�L�[���͂��܂Ƃ߂�
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
	//�ʏ�U���̍ŏI�i�Ȃ̂łȂɂ����Ȃ�
}