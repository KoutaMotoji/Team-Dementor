//===============================================================================
//
//  プレイヤー処理(playerX.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "stage1_boss.h"
#include "character.h"
#include "floor_stone.h"
#include "stage1_bossUI.h"
#include "player_observer.h"
#include "stage1_boss_AttackState.h"

#include "inimanager.h"
#include "game.h"

namespace
{
	int _MAX_LIFE = 1000;
	float _WORLD_WALL = 1300.0f;
	float Damage_Ratio = 0.2f;
	float _GRAVITY = 4.0f;
	float _MOVE_SPEED = 1.5f;
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
		 "Stage1Boss"
	};
};

//==========================================================================================
//コンストラクタ
//==========================================================================================
CG_Gorira::CG_Gorira() : m_bAttackCt(false), m_nAttackcnt(0), m_moveFlag(true), m_nLife(0)
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
void CG_Gorira::Init()
{
	CObject::SetType(TYPE_3D_BOSS_1);						//オブジェクト一括管理用のタイプを設定
	CCharacter::Init();
	CCharacter::MotionDataLoad(CiniManager::GetInstance()->GetINIData(st_filename.config, st_filename.section, st_filename.keyword));
	CCharacter::SetSize({ _SETSIZE,_SETSIZE,_SETSIZE });
	CCharacter::SetRadius(100.0f);
	CCharacter::SetLife(_MAX_LIFE);
	m_bBossAI = std::make_shared<Gorira_AI>();
	SetState(std::make_shared<Stage1Boss_Nutoral>());
	SetAttackState(std::make_shared<G_Attack_None>());
	m_pDebugLine = CDebugLineCylinder::Create(CCharacter::GetRadius().x);
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
	m_HPGauge = CStage1BossGaugeLife::Create(_MAX_LIFE);
}

//==========================================================================================
//終了処理
//==========================================================================================
void CG_Gorira::Uninit()
{
	if (m_HPGauge != nullptr)
	{
		m_HPGauge->Release();
		m_HPGauge = nullptr;
	}
	CCharacter::Uninit();
}

//==========================================================================================
//更新処理
//==========================================================================================
void CG_Gorira::Update()
{
	m_OldPos = CCharacter::GetPos();
	/*m_State->Move(this);
	m_State->Attack(this);
	m_State->Wait(this);*/
	m_AttackState->G_AttackUpdate(this);
	FloorCollision();	//プレイヤー移動制限の当たり判定

	std::vector<std::shared_ptr<CHitCircle>> phc = CCharacter::GetVecHitCircle();

	if (CCharacter::GetLife() <= 0)
	{
		CManager::GetInstance()->GetFade()->SetFade(CFade::FADE_IN, CScene::MODE_RESULT);
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_6))
	{
		SetAttackState(std::make_shared<G_Attack_Dive>());
	}
	CCharacter::AddPos({ 0.0f,-_GRAVITY,0.0f });

	D3DXVECTOR3 pos = CCharacter::GetPos();
	m_HPGauge->SetGauge(CCharacter::GetLife());
	CCharacter::Update();

}

//==========================================================================================
//描画処理
//==========================================================================================
void CG_Gorira::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	// 法線の自動正規化を有効に
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

//==========================================================================================
//生成処理
//==========================================================================================
CG_Gorira* CG_Gorira::Create(D3DXVECTOR3 pos)
{
	CG_Gorira* gorira = new CG_Gorira;
	gorira->SetMove({ 0.0f,0.0f,0.0f });
	gorira->m_OldPos = pos;
	gorira->Init();
	gorira->SetPos(pos);
	return gorira;
}

//==========================================================================================
// モーション終了時に呼ばれる関数(オーバーライド)
//==========================================================================================
bool  CG_Gorira::EndMotion()
{
	m_AttackState->G_AttackFinish(this);

	return true;
}

//==========================================================================================
// キャラクターの移動制限判定
//==========================================================================================
void CG_Gorira::FloorCollision()
{
	if (CCharacter::GetPos().z < -_WORLD_WALL)
	{
		CCharacter::SetPos( { CCharacter::GetPos().x, CCharacter::GetPos().y, -_WORLD_WALL });
	}
	else if (CCharacter::GetPos().z > _WORLD_WALL)
	{
		CCharacter::SetPos( { CCharacter::GetPos().x, CCharacter::GetPos().y, _WORLD_WALL });
	}
	if (CCharacter::GetPos().x < -_WORLD_WALL)
	{
		CCharacter::SetPos( { -_WORLD_WALL, CCharacter::GetPos().y, CCharacter::GetPos().z });
	}
	else if (CCharacter::GetPos().x > _WORLD_WALL)
	{
		CCharacter::SetPos( { _WORLD_WALL, CCharacter::GetPos().y, CCharacter::GetPos().z });
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
				CCharacter::AddPos({ 0.0f, fLandDistance - CCharacter::GetMove().y - _GRAVITY,0.0f});
				return;
			}
		}
	}
}

//==========================================================================================
// キャラクターの移動
//==========================================================================================
void CG_Gorira::Move()
{
	if (CCharacter::GetNextMotion() != 2 && CCharacter::GetNextMotion() != 3 && CCharacter::GetNextMotion() != 4)
	{
		if (m_moveFlag)
		{
			CCharacter::AddMove({ 0.0f,0.0f,-1.0f });
			CCharacter::SetNextMotion(1);
			CCharacter::SetRot({ 0.0f,0.0f,0.0f });
		}
		else
		{
			CCharacter::AddMove({ 0.0f,0.0f,1.0f });
			CCharacter::SetNextMotion(1);
			CCharacter::SetRot({ 0.0f,D3DX_PI,0.0f });
		}
	}

	CCharacter::AddPos({ 0.0f,-_GRAVITY,0.0f });

	if (m_OldPos.z + CCharacter::GetMove().z > 800.0f || m_OldPos.z + CCharacter::GetMove().z < -800.0f)
	{
		CCharacter::AddPos({ 0.0f,0.0f,-CCharacter::GetMove().z });
		m_moveFlag = (!m_moveFlag);
	}
}

//==========================================================================================
// キャラクターの攻撃を制御
//==========================================================================================
void CG_Gorira::DoAttack()
{
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
void CG_Gorira::BeDamaged()
{
	m_State->Damage(this); 
}	

//==========================================================================================
// キャラクターの被ダメ処理
//==========================================================================================
void CG_Gorira::Damaged()
{
	CCharacter::SetLife(CCharacter::GetLife() - 10);
}	

void CG_Gorira::SetAttackState(std::shared_ptr<G_AttackBehavior>pState) {
	if (m_AttackState != nullptr) {
		m_AttackState = nullptr;
	}
	m_AttackState = pState;
	m_AttackState->G_AttackInit(this);
}