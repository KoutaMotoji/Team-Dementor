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

D3DXVECTOR3 LockEnable::s_savedPosV = { 0,0,0 };
D3DXVECTOR3 LockEnable::s_savedPosR = { 0,0,0 };

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
	CCamera* cam = CManager::GetInstance()->GetCamera();

	// プレイヤー位置をセット（UpdateNormalCamに必要）
	cam->SetPlayerPos(pPlayer->CCharacter::GetPos());

	// 現在のカメラ座標を退避
	D3DXVECTOR3 currentV = cam->GetPosV();
	D3DXVECTOR3 currentR = cam->GetPosR();

	// 一時的に通常カメラの理想座標を計算
	cam->UpdateNormalCam();

	D3DXVECTOR3 followV = cam->GetPosV();
	D3DXVECTOR3 followR = cam->GetPosR();

	// 元の座標に戻す（計算だけ利用したので）
	cam->SetCamPos(currentV, currentR);

	// 通常カメラの理想座標に向かって補間
	cam->SetFreeCam(followV, followR, 30, false);

	// ステート切り替え
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

			// プレイヤーと敵の位置
			D3DXVECTOR3 playerPos = pPlayer->CCharacter::GetPos();
			D3DXVECTOR3 enemyPos = pEnemy->CCharacter::GetPos();

			// プレイヤーと敵の水平距離からYawを算出
			D3DXVECTOR3 dir = enemyPos - playerPos;
			dir.y = 0.0f;
			D3DXVec3Normalize(&dir, &dir);
			float yaw = atan2f(dir.x, dir.z);

			// 回転オフセットをYawに応じて回転
			D3DXVECTOR3 offset = { 0.0f, 200.0f, -700.0f };
			D3DXMATRIX rotY;
			D3DXMatrixRotationY(&rotY, yaw);
			D3DXVECTOR3 rotatedOffset;
			D3DXVec3TransformCoord(&rotatedOffset, &offset, &rotY);

			// カメラ位置と注視点を算出
			D3DXVECTOR3 camPos = playerPos + rotatedOffset;

			// カメラに位置をセット
			CCamera* cam = CManager::GetInstance()->GetCamera();
			cam->SetRotz(yaw);
			cam->SetPlayerPos(playerPos);
			cam->SetEnemyPos(enemyPos);
			cam->UpdateLockOnCam(camPos, enemyPos);
		}
	}
}

//非ロックオン時のステート
void LockDisable::Swicth([[maybe_unused]]CPlayerX* pPlayer) {
	CCamera* cam = CManager::GetInstance()->GetCamera();

	for (int j = 0; j < SET_PRIORITY; ++j) {
		for (int i = 0; i < MAX_OBJECT; ++i) {
			CObject* pObj = CObject::GetObjects(j, i);
			if (!pObj) continue;

			if (pObj->GetType() != CObject::TYPE::TYPE_3D_BOSS_1) continue;
			CG_Gorira* pEnemy = dynamic_cast<CG_Gorira*>(pObj);
			if (!pEnemy) continue;

			// プレイヤーと敵の位置
			D3DXVECTOR3 playerPos = pPlayer->CCharacter::GetPos();
			D3DXVECTOR3 enemyPos = pEnemy->CCharacter::GetPos();

			// 現在のカメラ位置を保存（解除時に戻す用）
			LockEnable::s_savedPosV = cam->GetPosV(); 
			LockEnable::s_savedPosR = cam->GetPosR();

			// Yaw計算
			D3DXVECTOR3 dir = enemyPos - playerPos;
			dir.y = 0.0f;
			D3DXVec3Normalize(&dir, &dir);
			float yaw = atan2f(dir.x, dir.z);

			// カメラオフセット回転
			D3DXVECTOR3 offset = { 0.0f, 200.0f, -700.0f };
			D3DXMATRIX rotY;
			D3DXMatrixRotationY(&rotY, yaw);
			D3DXVECTOR3 rotatedOffset;
			D3DXVec3TransformCoord(&rotatedOffset, &offset, &rotY);

			// 補間後のカメラ位置
			D3DXVECTOR3 targetCamPos = playerPos + rotatedOffset;

			// プレイヤーと敵の位置をセット
			cam->SetPlayerPos(playerPos);
			cam->SetEnemyPos(enemyPos);

			// 現在のカメラ位置から補間開始
			cam->SetFreeCam(targetCamPos, enemyPos, 30, true); // 40フレーム補間
		}
	}

	// ロックオンを有効化
	pPlayer->SetLockOnState(std::make_shared<LockEnable>());
}

void LockDisable::UpdateCam([[maybe_unused]]CPlayerX* pPlayer)
{
	CManager::GetInstance()->GetCamera()->SetPlayerPos(pPlayer->CCharacter::GetPos());
}

