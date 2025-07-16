//===============================================================================
//
//  �v���C���[�̏�ԊǗ�(player_state.cpp)
//								����F���n�O��
// 
//===============================================================================

#include "xxx_player.h"
#include "stage1_boss.h"

//�ʏ펞�̃X�e�[�g
void State_Nutoral::Attack(CPlayerX* pPlayer) {
	//pPlayer->PAttackInfo();
}
void State_Nutoral::Parry(CPlayerX* pPlayer) {

}
void State_Nutoral::Move(CPlayerX* pPlayer)
{
	pPlayer->PMove(CManager::GetInstance()->GetCamera()->GetRotZ());
	pPlayer->EnemyCollision();
}
void State_Nutoral::ToAttack(CPlayerX* pPlayer)
{
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

//�U�����̃X�e�[�g
void State_Attack::Attack(CPlayerX* pPlayer)
{
	pPlayer->ToEnemyAttack();
	pPlayer->PAttackInfo();

}
void State_Attack::Parry(CPlayerX* pPlayer) {

}
void State_Attack::Move(CPlayerX* pPlayer) {
	//�U�����͈ړ��s�̂��߈ړ��̋@�\���������Ȃ�
}
void State_Attack::ToAttack(CPlayerX* pPlayer) {

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

//�p���B���̃X�e�[�g
void State_Parry::Attack(CPlayerX* pPlayer) {

}
void State_Parry::Parry(CPlayerX* pPlayer)
{
	//�p���B��Ԃ̎��̂ݒʂ�����
	if (pPlayer->GetNowMotion() != CPlayerX::MOTION_PARRY && pPlayer->GetNowMotion() != CPlayerX::MOTION_PARRY_ATTACK && pPlayer->GetNextMotion() != CPlayerX::MOTION_PARRY_ATTACK)
	{
		pPlayer->CCharacter::SetNextMotion(CPlayerX::MOTION_PARRY_STAY);
	}
	pPlayer->SetParry();
	if (CManager::GetInstance()->GetJoypad()->GetRelease(CJoypad::JOYPAD_RIGHT_SHOULDER) ||
		CManager::GetInstance()->GetKeyboard()->GetRelease(DIK_L))
	{
		pPlayer->CCharacter::SetNextMotion(CPlayerX::MOTION_NUTORAL);
		pPlayer->SetState(std::make_shared<State_Nutoral>());
	}
}
void State_Parry::Move(CPlayerX* pPlayer) {

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
void State_Parry::ToParry(CPlayerX* pPlayer) {

}

//��_���[�W���̃X�e�[�g
void State_Damage::Attack(CPlayerX* pPlayer) {

}
void State_Damage::Parry(CPlayerX* pPlayer) {

}
void State_Damage::Move(CPlayerX* pPlayer) {

}
void State_Damage::ToAttack(CPlayerX* pPlayer) {

}
void State_Damage::ToParry(CPlayerX* pPlayer) {

}
//���b�N�I�����̃X�e�[�g
void LockEnable::Swicth(CPlayerX* pPlayer) {
	pPlayer->SetLockOnState(std::make_shared<LockDisable>());
}

void LockEnable::UpdateCam(CPlayerX* pPlayer)
{
	D3DXVECTOR3 SetPos{};
	D3DXVECTOR3 a{};
	D3DXVECTOR3 b{};

	for (int j = 0; j < SET_PRIORITY; ++j) {
		for (int i = 0; i < MAX_OBJECT; ++i) {
			CObject* pObj = CObject::GetObjects(j, i);
			if (pObj == nullptr) continue;

			CObject::TYPE type = pObj->GetType();
			if (type != CObject::TYPE::TYPE_3D_BOSS_1) continue;
			CG_Gorira* pTest = dynamic_cast<CG_Gorira>(pObj);
			if (pTest == nullptr) continue;

			CManager::GetInstance()->GetCamera()->UpdateLockOnCam(pPlayer->CCharacter::GetMatrix(), pTest->CCharacter::GetPos());
		}
	}
}

//�񃍃b�N�I�����̃X�e�[�g
void LockDisable::Swicth(CPlayerX pPlayer) {
	pPlayer->SetLockOnState(std::make_shared<LockEnable>());
}

void LockDisable::UpdateCam(CPlayerX* pPlayer)
{
	CManager::GetInstance()->GetCamera()->SetPlayerPos(pPlayer->CCharacter::GetPos());
}