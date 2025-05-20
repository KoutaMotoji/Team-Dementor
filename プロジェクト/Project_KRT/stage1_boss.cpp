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

#include "inimanager.h"
#include "game.h"

namespace
{
	float _WORLD_WALL = 1300.0f;
	float Damage_Ratio = 0.2f;
	float _GRAVITY = 4.0f;
	float _MOVE_SPEED = 1.5f;
	int _GAUGE_CTVALUE = 60;

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
CG_Gorira::CG_Gorira() : m_bAttackCt(false)
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
void CG_Gorira::Init()
{
	CObject::SetType(TYPE_3D_ENEMY);						//オブジェクト一括管理用のタイプを設定
	CCharacter::Init();
	CCharacter::MotionDataLoad(CiniManager::GetInstance()->GetINIData(st_filename.config, st_filename.section, st_filename.keyword));
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
	CCharacter::AddPos({ 0.0f,-_GRAVITY,0.0f });
	FloorCollision();	//プレイヤー移動制限の当たり判定
	CCharacter::SetPos(CPlayerObserver::GetInstance()->GetPlayerPos());
	CCharacter::SetRot({ 0.0f,0.0f,0.0f });
	CCharacter::Update();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CG_Gorira::Draw()
{
	int odss = CCharacter::GetNowMotion();
	CCharacter::Draw();
}

//==========================================================================================
//生成処理
//==========================================================================================
CG_Gorira* CG_Gorira::Create(D3DXVECTOR3 pos)
{
	CG_Gorira* gorira = new CG_Gorira;
	gorira->m_move = { 0.0f,0.0f,0.0f };
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
								CCharacter::AddPos({ 0.0f, fLandDistance - m_move.y - _GRAVITY,0.0f });
								return;
							}
						}
					}
				}
			}
		}
	}
}


