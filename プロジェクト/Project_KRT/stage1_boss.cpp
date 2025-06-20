//===============================================================================
//
//  プレイヤー処理(playerX.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "stage1_boss.h"
#include "character.h"
#include "floor_stone.h"
#include "player_observer.h"
#include "attack_range.h"

#include "inimanager.h"
#include "game.h"

namespace
{
	float _WORLD_WALL = 1300.0f;
	float Damage_Ratio = 0.2f;
	float _GRAVITY = 4.0f;
	float _MOVE_SPEED = 1.5f;
	int _GAUGE_CTVALUE = 60;
	float _SETSIZE = 3.0f;
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
CG_Gorira::CG_Gorira() : m_bAttackCt(false), m_nAttackcnt(0), m_moveFlag(true)
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

	m_pDebugLine = CDebugLineCylinder::Create(CCharacter::GetRadius().x);
	for (const auto& e : CCharacter::GetModelPartsVec())
	{
		D3DXVECTOR3 radius = *e->GetRadius();
		radius.x = radius.y = radius.z *= 3;
		m_pHC_BodyCollision.push_back(CHitCircle::Create(radius, e->GetPos(), e->GetIndex(), 0, 2, 0));
		m_pDL_BodyCollision.push_back(CDebugLineSphire::Create(radius.x, { 0.1f,1.0f,0.1f,1.0f }));
	}
	for (const auto& e : m_pHC_BodyCollision)
	{
		e->SetEnable();
	}
}

//==========================================================================================
//終了処理
//==========================================================================================
void CG_Gorira::Uninit()
{
	CCharacter::Uninit();
}

//==========================================================================================
//更新処理
//==========================================================================================
void CG_Gorira::Update()
{
	m_OldPos = CCharacter::GetPos();
	if (m_nAttackcnt >= 720)
	{
		CDrawFan::Create({ 0.0f,0.0f,0.0f });
		CCharacter::SetNextMotion(2);
		m_nAttackcnt = 0;
	}
	else
	{
		++m_nAttackcnt;
	}
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
	FloorCollision();	//プレイヤー移動制限の当たり判定

	//CCharacter::SetRot({ 0.0f,0.0f,0.0f });

	if (m_OldPos.z + CCharacter::GetMove().z > 800.0f || m_OldPos.z + CCharacter::GetMove().z < -800.0f)
	{
		CCharacter::AddPos({ 0.0f,0.0f,-CCharacter::GetMove().z});
		m_moveFlag = (!m_moveFlag);
	}
	std::vector<std::shared_ptr<CHitCircle>> phc = CCharacter::GetVecHitCircle();

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
			if (pObj != nullptr) {
				CObject::TYPE type = pObj->GetType();
				if (type == CObject::TYPE::TYPE_3D_MESHOBJECT) {
					CMeshGround* pTest = dynamic_cast<CMeshGround*>(pObj);
					if (pTest != nullptr) {
						pMesh = pTest->GetMesh();
						if (pTest != nullptr) {
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
			}
		}
	}
}


