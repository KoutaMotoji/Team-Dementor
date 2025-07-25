//===============================================================================
//
//  プレイヤーの状態管理(player_state.cpp)
//								制作：元地弘汰
// 
//===============================================================================

#include "xxx_player.h"
#include "stage1_boss.h"
#include "player_armState.h"
#include "collision.h"

//通常時のステート
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

//攻撃時のステート
void State_Attack::Attack([[maybe_unused]]CPlayerX* pPlayer)
{
	pPlayer->ToEnemyAttack();
	pPlayer->PAttackInfo();

}
void State_Attack::Parry([[maybe_unused]]CPlayerX* pPlayer) {

}
void State_Attack::Move([[maybe_unused]]CPlayerX* pPlayer) {
	//攻撃時は移動不可のため移動の機能を実装しない
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

//パリィ時のステート
void State_Parry::Attack([[maybe_unused]]CPlayerX* pPlayer) {

}
void State_Parry::Parry([[maybe_unused]]CPlayerX* pPlayer)
{
	//パリィ状態の時のみ通す処理
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

//被ダメージ時のステート
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

//ロックオン時のステート
void LockEnable::Swicth([[maybe_unused]]CPlayerX* pPlayer) {
	pPlayer->SetLockOnState(std::make_shared<LockDisable>());
}

void LockEnable::UpdateCam([[maybe_unused]]CPlayerX* pPlayer)
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
			CG_Gorira* pTest = dynamic_cast<CG_Gorira*>(pObj);
			if (pTest == nullptr) continue;

			D3DXMATRIX mat = pPlayer->CCharacter::GetMatrix();
			D3DXVECTOR3 posEnemy = pTest->CCharacter::GetPos();

			D3DXMATRIX SetMtx{}, mtxTrans{}, mtxRot{};

			D3DXVECTOR3 pos = { 0.0f,200.0f,-700.0f };
			D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };

			//マトリックスから位置を抽出
			D3DXVECTOR3 mtxPos1 = {
			mat._41,
			mat._42,
			mat._43
			};

			D3DXVECTOR3 PlayerPos = { mtxPos1.x,0.0f,mtxPos1.z };
			D3DXVECTOR3 EnemyPos = { posEnemy.x,0.0f,posEnemy.z };

			D3DXVECTOR3 dir = EnemyPos - PlayerPos;
			D3DXVec3Normalize(&dir, &dir);

			float Yaw = atan2f(dir.x, dir.z);

			D3DXMATRIX RotY;
			D3DXVECTOR3 RotateOffset;

			D3DXMatrixRotationY(&RotY, Yaw);
			D3DXVec3TransformCoord(&RotateOffset, &pos, &RotY);

			D3DXVECTOR3 CamPos = mtxPos1 + RotateOffset;

			CManager::GetInstance()->GetCamera()->SetRotz(Yaw);

			CManager::GetInstance()->GetCamera()->SetPlayerPos(PlayerPos);
			CManager::GetInstance()->GetCamera()->SetEnemyPos(EnemyPos);
			CManager::GetInstance()->GetCamera()->UpdateLockOnCam(CamPos, EnemyPos);
		}
	}
}

//非ロックオン時のステート
void LockDisable::Swicth([[maybe_unused]]CPlayerX* pPlayer) {
	for (int j = 0; j < SET_PRIORITY; ++j) {
		for (int i = 0; i < MAX_OBJECT; ++i) {
			CObject* pObj = CObject::GetObjects(j, i);
			if (pObj == nullptr) continue;

			CObject::TYPE type = pObj->GetType();
			if (type != CObject::TYPE::TYPE_3D_BOSS_1) continue;
			CG_Gorira* pTest = dynamic_cast<CG_Gorira*>(pObj);
			if (pTest == nullptr) continue;

			D3DXMATRIX mat = pPlayer->CCharacter::GetMatrix();
			D3DXMATRIX matEnemy = pTest->CCharacter::GetMatrix();
			D3DXVECTOR3 posEnemy = pTest->CCharacter::GetPos();
			D3DXVECTOR3 posPlayer = pPlayer->CCharacter::GetPos();

			//マトリックスから位置を抽出
			D3DXVECTOR3 mtxPos1 = {
			mat._41,
			mat._42,
			mat._43
			};

			//マトリックスから位置を抽出
			D3DXVECTOR3 mtxPos21 = {
			matEnemy._41,
			matEnemy._42,
			matEnemy._43
			};

			D3DXVECTOR3 PlayerPos = { mtxPos1.x,0.0f,mtxPos1.z };
			D3DXVECTOR3 EnemyPos = { mtxPos21.x,0.0f,mtxPos21.z };

			D3DXMATRIX SetMtx{}, mtxTrans{}, mtxRot{};

			D3DXVECTOR3 pos = { 0.0f,200.0f,-700.0f };

			D3DXVECTOR3 dir = EnemyPos - PlayerPos;
			D3DXVec3Normalize(&dir, &dir);

			float Yaw = atan2f(dir.x, dir.z);

			D3DXMATRIX RotY;
			D3DXVECTOR3 RotateOffset;

			D3DXMatrixRotationY(&RotY, Yaw);
			D3DXVec3TransformCoord(&RotateOffset, &pos, &RotY);

			D3DXVECTOR3 CamPos = mtxPos1 + RotateOffset;

			CManager::GetInstance()->GetCamera()->SetPlayerPos(PlayerPos);
			CManager::GetInstance()->GetCamera()->SetEnemyPos(EnemyPos);
			CManager::GetInstance()->GetCamera()->SetFreeCam(&CamPos, &EnemyPos, 40);
		}
	}
	pPlayer->SetLockOnState(std::make_shared<LockEnable>());
}

void LockDisable::UpdateCam([[maybe_unused]]CPlayerX* pPlayer)
{
	CManager::GetInstance()->GetCamera()->SetPlayerPos(pPlayer->CCharacter::GetPos());
}

