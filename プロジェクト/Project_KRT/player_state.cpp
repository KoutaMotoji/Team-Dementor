//===============================================================================
//
//  �v���C���[�̏�ԊǗ�(player_state.cpp)
//								����F���n�O��
// 
//===============================================================================

#include "xxx_player.h"
#include "stage1_boss.h"
#include "player_armState.h"
#include "collision.h"

D3DXVECTOR3 LockEnable::s_savedPosV = { 0,0,0 };
D3DXVECTOR3 LockEnable::s_savedPosR = { 0,0,0 };

//�ʏ펞�̃X�e�[�g
void State_Nutoral::Attack([[maybe_unused]]CPlayerX* pPlayer) {
	//pPlayer->PAttackInfo();
}
void State_Nutoral::Parry([[maybe_unused]]CPlayerX* pPlayer) {

}
void State_Nutoral::Move([[maybe_unused]]CPlayerX* pPlayer)
{
	pPlayer->PMove(CManager::GetInstance()->GetCamera()->GetRotZ());
	pPlayer->EnemyCollision();
}
void State_Nutoral::ToAttack([[maybe_unused]]CPlayerX* pPlayer)
{
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_X) ||
		CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_J))
	{
		pPlayer->CCharacter::SetNextMotion(CPlayerX::MOTION_ATTACK_N1);
		pPlayer->SetState(std::make_shared<State_Attack>());
	}
}
void State_Nutoral::ToParry([[maybe_unused]]CPlayerX* pPlayer)
{
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_RIGHT_SHOULDER) ||
		CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_L))
	{
		pPlayer->GetArmState()->ParryMotion(pPlayer);
		pPlayer->SetState(std::make_shared<State_Parry>());
	}
}

//�U�����̃X�e�[�g
void State_Attack::Attack([[maybe_unused]]CPlayerX* pPlayer)
{
	pPlayer->ToEnemyAttack();
	pPlayer->PAttackInfo();

}
void State_Attack::Parry([[maybe_unused]]CPlayerX* pPlayer) {

}
void State_Attack::Move([[maybe_unused]]CPlayerX* pPlayer) {
	//�U�����͈ړ��s�̂��߈ړ��̋@�\���������Ȃ�
}
void State_Attack::ToAttack([[maybe_unused]]CPlayerX* pPlayer) {

}
void State_Attack::ToParry([[maybe_unused]]CPlayerX* pPlayer)
{
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_RIGHT_SHOULDER) ||
		CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_L))
	{
		pPlayer->GetArmState()->ParryMotion(pPlayer);
		pPlayer->SetState(std::make_shared<State_Parry>());
	}
}

//�p���B���̃X�e�[�g
void State_Parry::Attack([[maybe_unused]]CPlayerX* pPlayer) {

}
void State_Parry::Parry([[maybe_unused]]CPlayerX* pPlayer)
{
	//�p���B��Ԃ̎��̂ݒʂ�����
	if (pPlayer->GetNowMotion() != CPlayerX::MOTION_PARRY && pPlayer->GetNowMotion() != CPlayerX::MOTION_PARRY_ATTACK && pPlayer->GetNextMotion() != CPlayerX::MOTION_PARRY_ATTACK)
	{
		pPlayer->GetArmState()->ParryStayMotion(pPlayer);

	}
	pPlayer->SetParry();
	if (CManager::GetInstance()->GetJoypad()->GetRelease(CJoypad::JOYPAD_RIGHT_SHOULDER) ||
		CManager::GetInstance()->GetKeyboard()->GetRelease(DIK_L))
	{
		pPlayer->GetArmState()->ParryMotion(pPlayer);
		pPlayer->SetState(std::make_shared<State_Nutoral>());
	}
}
void State_Parry::Move([[maybe_unused]]CPlayerX* pPlayer) {

}
void State_Parry::ToAttack([[maybe_unused]]CPlayerX* pPlayer)
{
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_X) ||
		CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_J))
	{
		pPlayer->CCharacter::SetNextMotion(CPlayerX::MOTION_ATTACK_N1);
		pPlayer->SetState(std::make_shared<State_Attack>());
	}
}
void State_Parry::ToParry([[maybe_unused]]CPlayerX* pPlayer) {

}

//��_���[�W���̃X�e�[�g
void State_Damage::Attack([[maybe_unused]]CPlayerX* pPlayer) {

}
void State_Damage::Parry([[maybe_unused]]CPlayerX* pPlayer) {

}
void State_Damage::Move([[maybe_unused]]CPlayerX* pPlayer) {

}
void State_Damage::ToAttack([[maybe_unused]]CPlayerX* pPlayer) {

}
void State_Damage::ToParry([[maybe_unused]]CPlayerX* pPlayer) {

}

//���b�N�I�����̃X�e�[�g
void LockEnable::Swicth([[maybe_unused]]CPlayerX* pPlayer) {
	CCamera* cam = CManager::GetInstance()->GetCamera();

	// �v���C���[�ʒu���Z�b�g�iUpdateNormalCam�ɕK�v�j
	cam->SetPlayerPos(pPlayer->CCharacter::GetPos());

	// ���݂̃J�������W��ޔ�
	D3DXVECTOR3 currentV = cam->GetPosV();
	D3DXVECTOR3 currentR = cam->GetPosR();

	// �ꎞ�I�ɒʏ�J�����̗��z���W���v�Z
	cam->UpdateNormalCam();

	D3DXVECTOR3 followV = cam->GetPosV();
	D3DXVECTOR3 followR = cam->GetPosR();

	// ���̍��W�ɖ߂��i�v�Z�������p�����̂Łj
	cam->SetCamPos(currentV, currentR);

	// �ʏ�J�����̗��z���W�Ɍ������ĕ��
	cam->SetFreeCam(followV, followR, 30, false);

	// �X�e�[�g�؂�ւ�
	pPlayer->SetLockOnState(std::make_shared<LockDisable>());
}

void LockEnable::UpdateCam([[maybe_unused]]CPlayerX* pPlayer)
{	
	for (int j = 0; j < SET_PRIORITY; ++j) {
		for (int i = 0; i < MAX_OBJECT; ++i) {
			CObject* pObj = CObject::GetObjects(j, i);
			if (pObj == nullptr) continue;

			if (pObj->GetType() != CObject::TYPE::TYPE_3D_BOSS_1) continue;
			CG_Gorira* pEnemy = dynamic_cast<CG_Gorira*>(pObj);
			if (!pEnemy) continue;

			// �v���C���[�ƓG�̈ʒu
			D3DXVECTOR3 playerPos = pPlayer->CCharacter::GetPos();
			D3DXVECTOR3 enemyPos = pEnemy->CCharacter::GetPos();

			// �v���C���[�ƓG�̐�����������Yaw���Z�o
			D3DXVECTOR3 dir = enemyPos - playerPos;
			dir.y = 0.0f;
			D3DXVec3Normalize(&dir, &dir);
			float yaw = atan2f(dir.x, dir.z);

			// ��]�I�t�Z�b�g��Yaw�ɉ����ĉ�]
			D3DXVECTOR3 offset = { 0.0f, 200.0f, -700.0f };
			D3DXMATRIX rotY;
			D3DXMatrixRotationY(&rotY, yaw);
			D3DXVECTOR3 rotatedOffset;
			D3DXVec3TransformCoord(&rotatedOffset, &offset, &rotY);

			// �J�����ʒu�ƒ����_���Z�o
			D3DXVECTOR3 camPos = playerPos + rotatedOffset;

			// �J�����Ɉʒu���Z�b�g
			CCamera* cam = CManager::GetInstance()->GetCamera();
			cam->SetRotz(yaw);
			cam->SetPlayerPos(playerPos);
			cam->SetEnemyPos(enemyPos);
			cam->UpdateLockOnCam(camPos, enemyPos);
		}
	}
}

//�񃍃b�N�I�����̃X�e�[�g
void LockDisable::Swicth([[maybe_unused]]CPlayerX* pPlayer) {
	CCamera* cam = CManager::GetInstance()->GetCamera();

	for (int j = 0; j < SET_PRIORITY; ++j) {
		for (int i = 0; i < MAX_OBJECT; ++i) {
			CObject* pObj = CObject::GetObjects(j, i);
			if (!pObj) continue;

			if (pObj->GetType() != CObject::TYPE::TYPE_3D_BOSS_1) continue;
			CG_Gorira* pEnemy = dynamic_cast<CG_Gorira*>(pObj);
			if (!pEnemy) continue;

			// �v���C���[�ƓG�̈ʒu
			D3DXVECTOR3 playerPos = pPlayer->CCharacter::GetPos();
			D3DXVECTOR3 enemyPos = pEnemy->CCharacter::GetPos();

			// ���݂̃J�����ʒu��ۑ��i�������ɖ߂��p�j
			LockEnable::s_savedPosV = cam->GetPosV(); 
			LockEnable::s_savedPosR = cam->GetPosR();

			// Yaw�v�Z
			D3DXVECTOR3 dir = enemyPos - playerPos;
			dir.y = 0.0f;
			D3DXVec3Normalize(&dir, &dir);
			float yaw = atan2f(dir.x, dir.z);

			// �J�����I�t�Z�b�g��]
			D3DXVECTOR3 offset = { 0.0f, 200.0f, -700.0f };
			D3DXMATRIX rotY;
			D3DXMatrixRotationY(&rotY, yaw);
			D3DXVECTOR3 rotatedOffset;
			D3DXVec3TransformCoord(&rotatedOffset, &offset, &rotY);

			// ��Ԍ�̃J�����ʒu
			D3DXVECTOR3 targetCamPos = playerPos + rotatedOffset;

			// �v���C���[�ƓG�̈ʒu���Z�b�g
			cam->SetPlayerPos(playerPos);
			cam->SetEnemyPos(enemyPos);

			// ���݂̃J�����ʒu�����ԊJ�n
			cam->SetFreeCam(targetCamPos, enemyPos, 30, true); // 40�t���[�����
		}
	}

	// ���b�N�I����L����
	pPlayer->SetLockOnState(std::make_shared<LockEnable>());
}

void LockDisable::UpdateCam([[maybe_unused]]CPlayerX* pPlayer)
{
	CManager::GetInstance()->GetCamera()->SetPlayerPos(pPlayer->CCharacter::GetPos());
}

