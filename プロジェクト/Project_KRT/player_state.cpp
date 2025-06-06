//===============================================================================
//
//  �v���C���[����(playerX.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "xxx_player.h"



//�ʏ펞�̃X�e�[�g
void State_Nutoral::Attack(CPlayerX* pPlayer)	{

}
void State_Nutoral::Parry(CPlayerX* pPlayer)	{

}
void State_Nutoral::Move(CPlayerX* pPlayer)
{
	pPlayer->PMove(CManager::GetInstance()->GetCamera()->GetRotZ());
	pPlayer->EnemyCollision();
}

//�U�����̃X�e�[�g
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
	//�U�����͈ړ��s�̂��߈ړ��̋@�\���������Ȃ�
}


//�p���B���̃X�e�[�g
void State_Parry::Attack(CPlayerX* pPlayer)
{

}
void State_Parry::Parry(CPlayerX* pPlayer)
{
	//�p���B��Ԃ̎��̂ݒʂ�����
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

//��_���[�W���̃X�e�[�g
void State_Damage::Attack(CPlayerX* pPlayer)
{

}
void State_Damage::Parry(CPlayerX* pPlayer)
{
	
}
void State_Damage::Move(CPlayerX* pPlayer)
{

}