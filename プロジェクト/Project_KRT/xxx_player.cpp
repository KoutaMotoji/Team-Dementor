//===============================================================================
//
//  プレイヤー処理(playerX.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "xxx_player.h"
#include "character.h"
#include "player_keyUI.h"
#include "floor_stone.h"
#include "stage1_boss.h"

#include "inimanager.h"
#include "game.h"

namespace
{
	const float _WORLD_WALL = 1300.0f;
	const float Damage_Ratio = 0.2f;
	const float _GRAVITY = 4.0f;
	const float _MOVE_SPEED = 1.2f;
	const float _JUMP_HEIGHT = 120.0f;
	const int _GAUGE_CTVALUE = 60;
	std::vector<D3DXVECTOR3>SetButtonUIpos = {
		{220.0f - 220.0f / 3,250.0f,0.0f},
		{220.0f,250.0f,0.0f},
		{220.0f + 220.0f / 3,250.0f,0.0f}
	};
	struct _FILENAME
	{
		std::string config;
		std::string section;
		std::string keyword;
	};
	_FILENAME st_filename = {
		"data\\TEXT\\Config.ini",
		 "ModelData",
		 "PlayerMotion"
	};
	std::vector<D3DXVECTOR3> RayPos = {
		{0.0f,10.0f,0.0f},
		{0.0f,50.0f,0.0f}
	};
};

//==========================================================================================
//コンストラクタ
//==========================================================================================
CPlayerX::CPlayerX(int nPriority) :CCharacter(nPriority), m_bAttackCt(false), m_nPushedKey(0), m_bParryWait(false)
{
	m_pCctBarUI = nullptr;
	m_vButtonUI = { nullptr,nullptr,nullptr };
}

//==========================================================================================
//デストラクタ
//==========================================================================================
CPlayerX::~CPlayerX()
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
void CPlayerX::Init()
{
	CObject::SetType(TYPE_3D_PLAYER);						//オブジェクト一括管理用のタイプを設定
	CCharacter::Init();
	CCharacter::MotionDataLoad(CiniManager::GetInstance()->GetINIData(st_filename.config, st_filename.section, st_filename.keyword));
}

//==========================================================================================
//終了処理
//==========================================================================================
void CPlayerX::Uninit()
{
	CCharacter::Uninit();
}

//==========================================================================================
//更新処理
//==========================================================================================
void CPlayerX::Update()
{
	D3DXVECTOR3 CameraPos;		//カメラの座標移動用ローカル変数
	m_OldPos = CCharacter::GetPos();

	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_X))
	{
		CCharacter::SetNextMotion(MOTION_ATTACK);
	}
	if (CCharacter::GetNextMotion() != MOTION_ATTACK && CCharacter::GetNextMotion() != MOTION_PARRY_ATTACK)
	{
		if (CManager::GetInstance()->GetJoypad()->GetRelease(CJoypad::JOYPAD_RIGHT_SHOULDER))
		{
			CCharacter::SetNextMotion(MOTION_NUTORAL);
			m_bParryWait = false;
		}
		if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_RIGHT_SHOULDER))
		{
			CCharacter::SetNextMotion(MOTION_PARRY);
			m_bParryWait = true;
		}
		if (CManager::GetInstance()->GetJoypad()->GetRepeat(CJoypad::JOYPAD_RIGHT_SHOULDER)&& CCharacter::GetNextMotion() != MOTION_PARRY)
		{
			CCharacter::SetNextMotion(MOTION_PARRY_STAY);
		}
	}

	if (CCharacter::GetNextMotion() != MOTION_ATTACK && CCharacter::GetNextMotion() != MOTION_PARRY && CCharacter::GetNextMotion() != MOTION_PARRY_STAY && CCharacter::GetNextMotion() != MOTION_PARRY_ATTACK)
	{
		PMove(CManager::GetInstance()->GetCamera()->GetRotZ());	//プレイヤー移動関連の処理
	}
	FloorCollision();	//プレイヤー移動制限の当たり判定

	if (m_bParryWait)
	{
		SetParry();
	}
	PAttackInfo();

	CCharacter::AddPos(m_move);
	
	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.14f;
	m_move.y += (0.0f - m_move.y) * 0.14f;
	m_move.z += (0.0f - m_move.z) * 0.17f;
	CManager::GetInstance()->GetCamera()->SetPlayerPos(CCharacter::GetPos());
	CCharacter::Update();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CPlayerX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	CCharacter::Draw();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);


	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

}

//==========================================================================================
//生成処理
//==========================================================================================
CPlayerX* CPlayerX::Create(D3DXVECTOR3 pos)
{
	CPlayerX* player = new CPlayerX;
	player->Init();
	player->m_move = { 0.0f,0.0f,0.0f };
	player->m_OldPos = pos;
	return player;
}

//==========================================================================================
//移動処理
//==========================================================================================
bool CPlayerX::PMove(float fCamRotZ)
{
	D3DXVECTOR3 moveDir{};
	float moveYrot{},dashValue{};
	bool bKeyFrag = false;

	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
	{
		moveDir.z += _MOVE_SPEED;
		bKeyFrag = true;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
	{
		moveDir.z -= _MOVE_SPEED;
		bKeyFrag = true;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_A))
	{
		moveDir.x -= _MOVE_SPEED;
		bKeyFrag = true;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_D))
	{
		moveDir.x += _MOVE_SPEED;
		bKeyFrag = true;
	}
	if (!bKeyFrag)
	{
		moveDir.x = CManager::GetInstance()->GetJoypad()->GetJoyStickVecL().x;
		moveDir.z = CManager::GetInstance()->GetJoypad()->GetJoyStickVecL().y;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_SPACE) || CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_A))
	{
		m_move.y += _JUMP_HEIGHT;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetRepeat(DIK_LSHIFT) || CManager::GetInstance()->GetJoypad()->GetRepeat(CJoypad::JOYPAD_B))
	{
		dashValue = 2.0f;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_LSHIFT) || CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_B))
	{
		dashValue = 15.0f;
	}

	moveYrot = atan2f(moveDir.x, moveDir.z) + fCamRotZ;
	
	if (moveDir.x == 0.0f && moveDir.z == 0.0f)
	{
		m_move.y -= _GRAVITY;
		CCharacter::SetNextMotion(MOTION_NUTORAL);
		return true;
	}

	CCharacter::SetRot({ 0.0f,moveYrot + D3DX_PI,0.0f });
	m_move.x += sinf(moveYrot) * _MOVE_SPEED;
	m_move.z += cosf(moveYrot) * _MOVE_SPEED;

	m_move.y -= _GRAVITY;

	CCharacter::SetNextMotion(MOTION_WALK);
	

	return true;
}

//==========================================================================================
// プレイヤーの移動制限判定
//==========================================================================================
void CPlayerX::FloorCollision()
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
								FloorbumpyMesh(pMesh);
								return;
							}
						}
					}
				}
			}
		}
	}
}

//==========================================================================================
// プレイヤーの地形の起伏移動
//==========================================================================================
bool CPlayerX::FloorbumpyMesh(LPD3DXMESH pMesh)
{
	struct RayInfo
	{
		// 地形判定
		BOOL  bIsHit = false;
		float fLandDistance{};
		DWORD dwHitIndex = 0U;
		float fHitU{};
		float fHitV{};
	};
	D3DXVECTOR3 pos[2]{}, rot{};
	rot.x = m_move.x;
	rot.z = m_move.z;
	rot.y = 0.0f;

	D3DXVec3Normalize(&rot, &rot);
	for (int i = 0; i < 2; ++i)
	{
		pos[i] = CCharacter::GetPos();
		pos[i] += RayPos[i];
	}
	std::vector<RayInfo>RI(2);
	for (int i = 0; i < 2; ++i)
	{
		D3DXIntersect(pMesh, &pos[i], &rot, &RI[i].bIsHit, &RI[i].dwHitIndex, &RI[i].fHitU, &RI[i].fHitV, &RI[i].fLandDistance, nullptr, nullptr);
	}
	if (RI[0].bIsHit && RI[1].bIsHit)
	{
		if ((RI[1].fLandDistance - RI[0].fLandDistance) < 100.0f && RI[0].fLandDistance < 20.0f)
		{
			CCharacter::SetPos({ CCharacter::GetPos().x - m_move.x,CCharacter::GetPos().y,CCharacter::GetPos().z - m_move.z});
			return true;
		}
	}
	return false;
}


//==========================================================================================
// プレイヤーの攻撃入力
//==========================================================================================
bool CPlayerX::PAttackInfo()
{
	bool pushed = false;
	if(m_nPushedKey <= 2){
		if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_X))
		{
			m_vButtonUI[m_nPushedKey] = CButtonUI::Create(SetButtonUIpos[m_nPushedKey],9);
			++m_nPushedKey;
			pushed = true;
		}
		else if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_Y))
		{
			m_vButtonUI[m_nPushedKey] = CButtonUI::Create(SetButtonUIpos[m_nPushedKey]);
			++m_nPushedKey;
			pushed = true;
		}
	}
	if (pushed)
	{
		m_bAttackCt = true;
		if (m_pCctBarUI == nullptr)
		{
			m_pCctBarUI = CCTBarUI::Create(_GAUGE_CTVALUE);
		}
		else
		{
			m_pCctBarUI->ResetGauge();
		}
	}
	if (m_pCctBarUI != nullptr)
	{
		if (m_pCctBarUI->GetEndFrag())
		{
			m_pCctBarUI->Release();
			m_pCctBarUI = nullptr;
			m_bAttackCt = false;
			m_nPushedKey = 0;
		}
	}
	if (!m_bAttackCt)
	{
		for (auto& e : m_vButtonUI)
		{
			if (e != nullptr)
			{
				e->Release();
				e = nullptr;
			}
		}
	}
	return true;
}

//==========================================================================================
// プレイヤーの攻撃入力
//==========================================================================================
void CPlayerX::SetParry()
{
	std::unique_ptr<CCollision>pCollision = std::make_unique<CCollision>();
	std::vector < std::shared_ptr<CHitCircle>> apVecHitCircle = CCharacter::GetVecHitCircle();
	std::shared_ptr<CHitCircle> pParryCircle;
	std::shared_ptr<CHitCircle> pBossAttackCircle;

	for (auto& p : apVecHitCircle)
	{
		if (p->GetEnable())	{
			pParryCircle = p;
			break;
		}
	}
	if (pParryCircle == nullptr)
	{
		return;
	}
	apVecHitCircle.clear();
	for (int j = 0; j < SET_PRIORITY; ++j) {
		for (int i = 0; i < MAX_OBJECT; ++i) {
			CObject* pObj = CObject::GetObjects(j, i);
			if (pObj != nullptr) {
				CObject::TYPE type = pObj->GetType();
				if (type == CObject::TYPE::TYPE_3D_BOSS_1) {
					CG_Gorira* pTest = dynamic_cast<CG_Gorira*>(pObj);
					if (pTest != nullptr) {
						if (pTest != nullptr) {
							apVecHitCircle = pTest->CCharacter::GetVecHitCircle();
							for (auto& p : apVecHitCircle)
							{
								if (p->GetEnable() && p->GetMotionNum() == 2)
								{
									pBossAttackCircle = p;
								}
							}
							if (pBossAttackCircle == nullptr)
							{
								return;
							}
							D3DXVECTOR3 MainPos, SubPos;
							D3DXMATRIX MainMtx, SubMtx;
							int cnt = 0;
							for (auto& p : CCharacter::GetModelPartsVec())
							{
								if (pParryCircle != nullptr)
								{
									if (cnt == pParryCircle->GetParentNum())
									{
										MainMtx = p->GetWorldMatrix();
									}
								}
								++cnt;
							}
							cnt = 0;
							for (auto& p : pTest->CCharacter::GetModelPartsVec())
							{
								if (pBossAttackCircle != nullptr)
								{
									if (cnt == pBossAttackCircle->GetParentNum())
									{
										SubMtx = p->GetWorldMatrix();
									}
								}
								++cnt;
							}
							MainPos = pParryCircle->CalcMtxPos(MainMtx);
							SubPos = pParryCircle->CalcMtxPos(SubMtx);

							if(pCollision->CircleCollosion(MainPos, SubPos, pParryCircle->GetRadius(), pBossAttackCircle->GetRadius()))
							{
								CCharacter::SetNextMotion(MOTION_PARRY_ATTACK);
								m_bParryWait = false;
								pTest->SetNextMotion(3);
								return;
							}
						}
					}
				}
			}
		}
	}
}