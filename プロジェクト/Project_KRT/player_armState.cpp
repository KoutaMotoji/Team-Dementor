//===============================================================================
//
//  �v���C���[�̘r��ԊǗ��N���X(player_armState.cpp)
//								����F���n�O��
// 
//===============================================================================

#include "player_armState.h"



void Arm_Normal::WalkMotion(CPlayerX* pPlayer)
{
	pPlayer->SetNextMotion(CPlayerX::MOTION_WALK);
}

void Arm_Normal::ParryMotion(CPlayerX* pPlayer)
{
	pPlayer->SetNextMotion(CPlayerX::MOTION_PARRY);
}

void Arm_Normal::ParryStayMotion(CPlayerX* pPlayer)
{
	pPlayer->SetNextMotion(CPlayerX::MOTION_PARRY_STAY);
}

void Arm_Gorira::WalkMotion(CPlayerX* pPlayer)
{
	pPlayer->SetNextMotion(CPlayerX::MOTION_GORIRA_WALK);
}

void Arm_Gorira::ParryMotion(CPlayerX* pPlayer)
{
	pPlayer->SetNextMotion(CPlayerX::MOTION_GORIRA_PARRY);
}

void Arm_Gorira::ParryStayMotion(CPlayerX* pPlayer)
{
	pPlayer->SetNextMotion(CPlayerX::MOTION_GORIRA_PARRY_STAY);
}