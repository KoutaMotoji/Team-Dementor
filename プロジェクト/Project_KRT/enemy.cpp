//===============================================================================
//
//  エネミー処理(enemy.cpp)
//								制作：大竹熙
// 
//===============================================================================

#pragma comment(lib,"winmm.lib")		//ランダムに必要

#include "enemy.h"
#include "character.h"
#include "floor_stone.h"
#include "player_observer.h"
#include "enemy_attack_state.h"
#include "enemy_ai.h"
#include "inimanager.h"
#include "weapon.h"
#include "field_manager.h"

// 移動方向と回転角をまとめたテーブル
struct MoveDir
{
	D3DXVECTOR3 move;   // 移動ベクトル
	D3DXVECTOR3 rot;    // 回転角
};

namespace
{
	const MoveDir g_MoveTable[] =
	{
		// 直線方向
		{ {  0.0f, 0.0f, -1.0f }, { 0.0f,  0.0f,          0.0f } }, // 前
		{ {  0.0f, 0.0f,  1.0f }, { 0.0f,  D3DX_PI,       0.0f } }, // 後
		{ { -1.0f, 0.0f,  0.0f }, { 0.0f,  D3DX_PI * 0.5f,0.0f } }, // 左
		{ {  1.0f, 0.0f,  0.0f }, { 0.0f, -D3DX_PI * 0.5f,0.0f } }, // 右

		// 斜め方向
		{ { -1.0f, 0.0f, -1.0f }, { 0.0f, -D3DX_PI * 0.25f,0.0f } }, // 左前
		{ {  1.0f, 0.0f, -1.0f }, { 0.0f,  D3DX_PI * 0.25f,0.0f } }, // 右前
		{ { -1.0f, 0.0f,  1.0f }, { 0.0f,  D3DX_PI * 0.75f,0.0f } }, // 左後
		{ {  1.0f, 0.0f,  1.0f }, { 0.0f, -D3DX_PI * 0.75f,0.0f } }  // 右後
	};
	const int MOVE_DIR_COUNT = sizeof(g_MoveTable) / sizeof(g_MoveTable[0]);
}

namespace
{
	int _MAX_LIFE = 30;
	float _WORLD_WALL = 1300.0f;
	float Damage_Ratio = 0.2f;
	float _GRAVITY = 4.0f;
	float _MOVE_SPEED = 3.0f;
	int _GAUGE_CTVALUE = 60;
	float _SETSIZE = 1.0f;
	struct _FILENAME
	{
		std::string config;
		std::string section;
		std::string keyword;
	};
	_FILENAME st_filename = {
		"data\\TEXT\\Config.ini",
		 "ModelData",
		 "Enemy"
	};
};

// 静的変数定義
int CEnemy::s_nWeaponCount = 0;
const int CEnemy::MAX_WEAPON = 1;

//==========================================================================================
//コンストラクタ
//==========================================================================================
CEnemy::CEnemy(): m_bAttackCt(false), m_nAttackcnt(0), m_moveFlag(true), m_nLife(0), m_bDying(false), m_bHidden(false), m_bDeathAnimFinished(false)
, m_bStunned(false), m_StunTimer(0), m_RespawnTimerFrames(0), m_RespawnDelayFrames(120), m_RespawnPos({ 0.0f,-1000.0f,0.0f })
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
void CEnemy::Init()
{
	CObject::SetType(TYPE_ENEMY);						//オブジェクト一括管理用のタイプを設定
	CCharacter::Init();
	CCharacter::MotionDataLoad(CiniManager::GetInstance()->GetINIData(st_filename.config, st_filename.section, st_filename.keyword));
	CCharacter::SetSize({ _SETSIZE,_SETSIZE,_SETSIZE });
	CCharacter::SetRadius(100.0f);
	CCharacter::SetLife(_MAX_LIFE);

	// AI
	m_pEnemyAI = std::make_shared<EnemyAI>();
	m_pEnemyAI->Init();
	m_bEnemyAI = std::make_shared<Enemy_AI>();
	m_bEnemyAI->AI_Init();

	// ステート初期化
	SetState(std::make_shared<Enemy_Nutoral>());
	SetAttackState(std::make_shared<E_Attack_None>());

	// デバッグライン等
	m_pDebugLine = CDebugLineCylinder::Create(CCharacter::GetRadius().x);

	// ヒットサークル作成
	m_pHC_BodyCollision.clear();
	m_pDL_BodyCollision.clear();
	for (const auto& e : CCharacter::GetModelPartsVec())
	{
		D3DXVECTOR3 radius = *e->GetRadius();
		m_pHC_BodyCollision.push_back(CHitCircle::Create(radius, e->GetPos(), e->GetIndex(), 0, 2, 0));
		m_pDL_BodyCollision.push_back(CDebugLineSphire::Create(radius.x, { 0.1f,1.0f,0.1f,1.0f }));
	}
	for (const auto& e : m_pHC_BodyCollision)
	{
		e->SetEnable();
	}

	// 敵状態フラグを初期化
	m_bDying = false;
	m_bHidden = false;
	m_bDeathAnimFinished = false;
	m_bStunned = false;
	m_StunTimer = 0;
	m_RespawnTimerFrames = 0;
}

//==========================================================================================
//終了処理
//==========================================================================================
void CEnemy::Uninit()
{
	CCharacter::Uninit();
}

//==========================================================================================
//更新処理
//==========================================================================================
void CEnemy::Update()
{
	FloorCollision();	//プレイヤー移動制限の当たり判定
	m_OldPos = CCharacter::GetPos();

	if (m_pEnemyAI) m_pEnemyAI->Update(this);
	if (m_bEnemyAI) m_bEnemyAI->AI_Update(this);

	// --- 行動制御 ---
	if (m_bDying)
	{
		// 死亡中は行動停止。
	}
	else if (m_bStunned)
	{
		// のけぞり中は行動できない
		if (--m_StunTimer <= 0)
		{
			m_bStunned = false;
			CCharacter::SetNextMotion(0); // 待機に戻す
		}
	}
	else
	{
		// 正常時の行動（非隠蔽・非死亡時のみ）
		if (!m_bHidden)
		{
			m_State->Move(this);
			m_State->Attack(this);

			if (m_AttackState)
				m_AttackState->AttackUpdate(this);
		}
	}

	// 物理・アニメ更新
	CCharacter::AddPos({ 0.0f, -_GRAVITY, 0.0f });
	CCharacter::Update();

	// ヒットサークルの有効/無効
	for (auto& hit : m_pHC_BodyCollision)
	{
		if (m_bHidden) hit->SetDisable();
		else           hit->SetEnable();
	}

	// --- 死亡開始判定（ライフ <=0） ---
	if (!m_bDying && CCharacter::GetLife() <= 0)
	{
		// 死亡開始
		m_bDying = true;
		m_bDeathAnimFinished = false;
		m_RespawnTimerFrames = 0;

		// 見た目の死亡モーション
		SetAttackState(std::make_shared<E_Attack_None>()); // 攻撃停止
		CCharacter::SetNextMotion(MOTION_DIE);

		// 攻撃や AI を停止させたいならここでフラグを使ってブロック（既に行動分岐済）
	}

	// --- 死亡アニメ終了で非表示にする（EndMotion() により m_bDeathAnimFinished が true になる） ---
	if (m_bDying && !m_bHidden && m_bDeathAnimFinished)
	{
		m_bHidden = true;
		for (auto& hit : m_pHC_BodyCollision) hit->SetDisable();
	}

	// --- フェールセーフ：時間で非表示→リスポーンする（EndMotion が呼ばれない場合も復活可能にする） ---
	if (m_bDying)
	{
		++m_RespawnTimerFrames;

		// 1秒（約60フレーム）で表示オフ（倒れている演出は見せる）
		if (m_RespawnTimerFrames == 120)
		{
			m_bHidden = true;
			for (auto& hit : m_pHC_BodyCollision) hit->SetDisable();
		}

		// 2秒（約120フレーム）でリスポーン
		if (m_RespawnTimerFrames >= m_RespawnDelayFrames)
		{
			Respawn();
		}
	}

	if (m_bPendingDropWeapon)
	{
		// 武器の上限チェック
		if (s_nWeaponCount < MAX_WEAPON)
		{
			CWeapon* weapon = CWeapon::Create(m_WeaponDropPos);
			CField_Manager::GetInstance()->RegistObj(weapon);
			s_nWeaponCount++;      // カウント増
		}
		m_bPendingDropWeapon = false;
	}
}

//==========================================================================================
//描画処理
//==========================================================================================
void CEnemy::Draw()
{
	if (m_bHidden) return; // 非表示中は描画をスキップ

	// 既存の描画処理をそのまま
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	CCharacter::Draw();

	// 法線の自動正規化を無効に
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	std::vector<CModelParts*> model = CCharacter::GetModelPartsVec();
	m_pDebugLine->Draw(CCharacter::GetPos());
	int cnt{};

	for (const auto& e : m_pDL_BodyCollision)
	{
		e->Draw({ model[cnt]->GetWorldMatrix()._41,model[cnt]->GetWorldMatrix()._42,model[cnt]->GetWorldMatrix()._43 });
		++cnt;
	}
}

void CEnemy::Respawn()
{
	// フラグリセット
	m_bDying = false;
	m_bHidden = false;
	m_bDeathAnimFinished = false;
	m_bStunned = false;
	m_StunTimer = 0;
	m_RespawnTimerFrames = 0;

	// HP・モーション初期化
	CCharacter::SetLife(_MAX_LIFE);
	CCharacter::SetMove({ 0.0f, 0.0f, 0.0f });
	CCharacter::SetNextMotion(0);

	// ランダムリスポーン座標を設定
	float randX = static_cast<float>(rand()) / RAND_MAX * 2.0f * _WORLD_WALL - _WORLD_WALL; // -_WORLD_WALL～+_WORLD_WALL
	float randZ = static_cast<float>(rand()) / RAND_MAX * 2.0f * _WORLD_WALL - _WORLD_WALL;
	m_RespawnPos = D3DXVECTOR3(randX, 0.0f, randZ); // Yは0に設定、地形判定で修正される

	CCharacter::SetPos(m_RespawnPos);

	// AI / 攻撃ステートを初期化
	SetAttackState(std::make_shared<E_Attack_None>());
	SetState(std::make_shared<Enemy_Nutoral>());

	// AI タイマー等初期化
	if (m_pEnemyAI) m_pEnemyAI->Init();
	if (m_bEnemyAI) m_bEnemyAI->AI_Init();

	// ヒットサークル復活
	for (auto& hit : m_pHC_BodyCollision) hit->SetEnable();
}

// 武器が拾われたら呼ぶ関数
void CEnemy::OnWeaponPicked()
{
	if (s_nWeaponCount > 0)
		s_nWeaponCount--;
}

//==========================================================================================
//生成処理
//==========================================================================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy* enemy = new CEnemy;
	enemy->SetMove({ 0.0f,0.0f,0.0f });
	enemy->m_OldPos = pos;
	enemy->Init();
	enemy->SetPos(pos);
	return enemy;
}

//==========================================================================================
// モーション終了時に呼ばれる関数(オーバーライド)
//==========================================================================================
bool  CEnemy::EndMotion()
{
	// モーション終了コールバック（エンジンから呼ばれる）
	int curMotion = CCharacter::GetNextMotion();
	if (curMotion == MOTION_DIE)
	{
		// 死亡モーションが終わったことを記録
		m_bDeathAnimFinished = true;
	}

	// 既存の AttackFinish 呼び出し（保持）
	if (m_AttackState)
		m_AttackState->AttackFinish(this);

	return true;
}

//==========================================================================================
// キャラクターの移動制限判定
//==========================================================================================
void CEnemy::FloorCollision()
{
	if (CCharacter::GetPos().z < -_WORLD_WALL)
	{
		CCharacter::SetPos({ CCharacter::GetPos().x, CCharacter::GetPos().y, -_WORLD_WALL });
	}
	else if (CCharacter::GetPos().z > _WORLD_WALL)
	{
		CCharacter::SetPos({ CCharacter::GetPos().x, CCharacter::GetPos().y, _WORLD_WALL });
	}
	if (CCharacter::GetPos().x < -_WORLD_WALL)
	{
		CCharacter::SetPos({ -_WORLD_WALL, CCharacter::GetPos().y, CCharacter::GetPos().z });
	}
	else if (CCharacter::GetPos().x > _WORLD_WALL)
	{
		CCharacter::SetPos({ _WORLD_WALL, CCharacter::GetPos().y, CCharacter::GetPos().z });
	}

	// 地形判定
	BOOL  bIsHit = false;
	float fLandDistance;
	DWORD dwHitIndex = 0U;
	float fHitU;
	float fHitV;
	LPD3DXMESH pMesh = nullptr;
	for (int j = 0; j < SET_PRIORITY; ++j) {
		for (int i = 0; i < MAX_OBJECT; ++i) {
			CObject* pObj = CObject::GetObjects(j, i);
			if (pObj == nullptr) continue;
			CObject::TYPE type = pObj->GetType();
			if (type != CObject::TYPE::TYPE_3D_MESHOBJECT) continue;
			CMeshGround* pTest = dynamic_cast<CMeshGround*>(pObj);
			if (pTest == nullptr) continue;
			// 地形判定
			pMesh = pTest->GetMesh();
			D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 objpos = CCharacter::GetPos() - pTest->GetPos();
			D3DXIntersect(pMesh, &objpos, &dir, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, nullptr, nullptr);

			// ----- 接地時処理 -----
			if (bIsHit)
			{
				CCharacter::AddPos({ 0.0f, fLandDistance - CCharacter::GetMove().y - _GRAVITY,0.0f });
				return;
			}
		}
	}
}

//==========================================================================================
// キャラクターの移動
//==========================================================================================
void CEnemy::Move()
{
	// 攻撃中は動かない
	if (CCharacter::GetNextMotion() >= 2 && CCharacter::GetNextMotion() <= 5)
		return;

	// 一定フレームごとに方向決定
	m_nTime++;
	if (m_nTime >= 180)
	{
		m_nTime = 0;
		m_Direction = rand() % MOVE_DIR_COUNT;
	}

	// 移動処理
	const MoveDir& dir = g_MoveTable[m_Direction];

	D3DXVECTOR3 normMove;
	D3DXVec3Normalize(&normMove, &dir.move);
	normMove *= _MOVE_SPEED;

	CCharacter::AddMove(normMove);
	CCharacter::SetNextMotion(1);

	// 進行方向から回転角を計算
	float angle = atan2f(normMove.x, normMove.z) + D3DX_PI; // モデル正面がZ-なら+π
	CCharacter::SetRot({ 0.0f, angle, 0.0f });

	// 重力処理
	CCharacter::AddPos({ 0.0f, -_GRAVITY, 0.0f });

	// 移動量を位置に反映 → リセット
	CCharacter::AddPos(CCharacter::GetMove());
	CCharacter::SetMove({ 0.0f, 0.0f, 0.0f });
}

//==========================================================================================
// キャラクターの攻撃を制御
//==========================================================================================
void CEnemy::DoAttack()
{
	// 死亡中 or 被弾中なら攻撃しない
	if (m_bDying || m_bStunned) return;

	if (m_nAttackcnt >= 720)
	{
		CCharacter::SetNextMotion(2);
		m_nAttackcnt = 0;
	}
	else
	{
		++m_nAttackcnt;
	}
}

//==========================================================================================
// キャラクターの被ダメ状態
//==========================================================================================
void CEnemy::BeDamaged()
{
	// 死亡中や非表示中は無効化
	if (m_bDying || m_bHidden) return;

	m_State->Damage(this);
}

//==========================================================================================
// キャラクターの被ダメ処理
//==========================================================================================
void CEnemy::Damaged()
{
	// 死亡中や非表示中は無効化
	if (m_bDying || m_bHidden) return;

	int life = CCharacter::GetLife() - 10;
	CCharacter::SetLife(life);

	if (life <= 0)
	{
		if (!m_bWeaponDropped)
		{
			m_bPendingDropWeapon = true;
			m_WeaponDropPos = CCharacter::GetPos();
			m_bWeaponDropped = true;
		}

		// ライフが0以下なら無条件で死亡開始
		m_bDying = true;
		m_bDeathAnimFinished = false;
		m_RespawnTimerFrames = 0;

		SetAttackState(std::make_shared<E_Attack_None>());
		CCharacter::SetNextMotion(MOTION_DIE);
	}
	else
	{
		// のけぞり状態にする
		m_bStunned = true;
		m_StunTimer = 30;
		CCharacter::SetNextMotion(MOTION_DAMAGE_SMALL);
	}
}

void CEnemy::SetAttackState(std::shared_ptr<E_AttackBehavior>pState) {
	if (m_AttackState != nullptr) {
		m_AttackState = nullptr;
	}
	m_AttackState = pState;
	m_AttackState->AttackInit(this);
}