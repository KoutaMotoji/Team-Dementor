//===============================================================================
//
//  �v���C���[����(playerX.cpp)
//								����F���n�O��
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
	struct _FILENAME	//�t�@�C���̃p�X�Ǘ��\����
	{
		std::string config;		//�t�@�C���̃p�X
		std::string section;	//�Z�N�V������
		std::string keyword;	//�L�[���[�h��
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
//�R���X�g���N�^
//==========================================================================================
CPlayerX::CPlayerX(int nPriority) :CCharacter(nPriority), m_bAttackCt(false), m_nPushedKey(0), m_bParryWait(false), m_LastCamDis(0.0f)
{
	m_pCctBarUI = nullptr;
	m_vButtonUI = { nullptr,nullptr,nullptr };
}

//==========================================================================================
//�f�X�g���N�^
//==========================================================================================
CPlayerX::~CPlayerX()
{

}

//==========================================================================================
//����������
//==========================================================================================
void CPlayerX::Init()
{
	CObject::SetType(TYPE_3D_PLAYER);						//�I�u�W�F�N�g�ꊇ�Ǘ��p�̃^�C�v��ݒ�
	CCharacter::Init();
	CCharacter::MotionDataLoad(CiniManager::GetInstance()->GetINIData(st_filename.config, st_filename.section, st_filename.keyword));
	CCharacter::SetRadius(50.0f);
	m_LastCamDis = CManager::GetInstance()->GetCamera()->GetCameraDistance();
	m_pDebugLine = CDebugLineCylinder::Create(CCharacter::GetRadius().x);
	SetState(std::make_shared<State_Nutoral>());	//�X�e�[�g���j���[�g�����ɐݒ�

}

//==========================================================================================
//�I������
//==========================================================================================
void CPlayerX::Uninit()
{
	CCharacter::Uninit();
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CPlayerX::Update()
{
	D3DXVECTOR3 CameraPos;		//�J�����̍��W�ړ��p���[�J���ϐ�
	m_OldPos = CCharacter::GetPos();

	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_X)||
		CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_J))
	{
		CCharacter::SetNextMotion(MOTION_ATTACK);

		SetState(std::make_shared<State_Attack>());

	}
	if (CCharacter::GetNextMotion() != MOTION_ATTACK && CCharacter::GetNextMotion() != MOTION_PARRY_ATTACK)
	{


		if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_RIGHT_SHOULDER) ||
			CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_L))
		{
			CCharacter::SetNextMotion(MOTION_PARRY);

			SetState(std::make_shared<State_Parry>());

		}
	}
	m_PlayerState->Move(this);

	FloorCollision();	//�v���C���[�ړ������̓����蔻��

	m_PlayerState->Parry(this);

	m_PlayerState->Attack(this);

	CManager::GetInstance()->GetCamera()->SetPlayerPos(CCharacter::GetPos());

	CCharacter::Update();
}

//==========================================================================================
//�`�揈��
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
	m_pDebugLine->Draw(CCharacter::GetPos());

}

//==========================================================================================
//��������
//==========================================================================================
CPlayerX* CPlayerX::Create(D3DXVECTOR3 pos)
{
	CPlayerX* player = new CPlayerX;
	player->Init();
	player->SetMove( { 0.0f,0.0f,0.0f });
	player->m_OldPos = pos;
	return player;
}

//==========================================================================================
//�ړ�����
//==========================================================================================
bool CPlayerX::PMove(float fCamRotZ)
{
	D3DXVECTOR3 moveDir= {0.0f,0.0f,0.0f};
	float moveYrot{},dashValue{};
	bool bKeyFrag = false;

	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
	{
		moveDir.z = 1;
		bKeyFrag = true;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
	{
		moveDir.z = -1;
		bKeyFrag = true;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_A))
	{
		moveDir.x = -1;
		bKeyFrag = true;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_D))
	{
		moveDir.x = 1;
		bKeyFrag = true;
	}
	if (!bKeyFrag)
	{
		moveDir.x = CManager::GetInstance()->GetJoypad()->GetJoyStickVecL().x;
		moveDir.z = CManager::GetInstance()->GetJoypad()->GetJoyStickVecL().y;
	}

	moveYrot = atan2f(moveDir.x, moveDir.z) + fCamRotZ;
	
	if (moveDir.x == 0.0f && moveDir.z == 0.0f)
	{
		CCharacter::AddMove({ 0.0f,-_GRAVITY,0.0f });
		CCharacter::SetNextMotion(MOTION_NUTORAL);
		return true;
	}

	CCharacter::SetRot({ 0.0f,moveYrot + D3DX_PI,0.0f });

	CCharacter::AddMove({ sinf(moveYrot) * _MOVE_SPEED,-_GRAVITY,cosf(moveYrot) * _MOVE_SPEED });

	CCharacter::SetNextMotion(MOTION_WALK);
	

	return true;
}

//==========================================================================================
// �v���C���[�̈ړ���������
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

	// �n�`����
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
						// �n�`����
						pMesh = pTest->GetMesh();
						D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
						D3DXVECTOR3 objpos = CCharacter::GetPos() - pTest->GetPos();
						D3DXIntersect(pMesh, &objpos, &dir, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, nullptr, nullptr);

						// ----- �ڒn������ -----
						if (bIsHit)
						{
							CamFloorCollision(pMesh);
							CCharacter::AddPos({ 0.0f, fLandDistance - CCharacter::GetMove().y - _GRAVITY,0.0f });
							FloorbumpyMesh(pMesh);
							return;
						}
						
					}
				}
			}
		}
	}
}

//==========================================================================================
// �v���C���[�̒n�`�̋N���ړ�
//==========================================================================================
bool CPlayerX::FloorbumpyMesh(LPD3DXMESH pMesh)
{
	struct RayInfo
	{
		// �n�`����
		BOOL  bIsHit = false;
		float fLandDistance{};
		DWORD dwHitIndex = 0U;
		float fHitU{};
		float fHitV{};
	};
	D3DXVECTOR3 pos[2]{}, rot{};
	rot.x = CCharacter::GetMove().x;
	rot.z = CCharacter::GetMove().z;
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
			CCharacter::SetPos({ CCharacter::GetPos().x - CCharacter::GetMove().x,CCharacter::GetPos().y,CCharacter::GetPos().z - CCharacter::GetMove().z});
			return true;
		}
	}
	return false;
}


//==========================================================================================
// �v���C���[�̍U������
//==========================================================================================
bool CPlayerX::PAttackInfo()
{
	bool pushed = false;
	if(m_nPushedKey <= 2){
		if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_X)||
			CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_J))
		{
			m_vButtonUI[m_nPushedKey] = CButtonUI::Create(SetButtonUIpos[m_nPushedKey],9);
			++m_nPushedKey;
			pushed = true;
		}
		else if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_Y) ||
				CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_K))
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
		SetState(std::make_shared<State_Nutoral>());
	}
	return true;
}

//==========================================================================================
// �v���C���[�̃p���B
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

						if(pCollision->SphireCollosion(MainPos, SubPos, pParryCircle->GetRadius(), pBossAttackCircle->GetRadius()))
						{
							CCharacter::SetNextMotion(MOTION_PARRY_ATTACK);
							m_bParryWait = false;
							pTest->SetNextMotion(3);
							CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_PARRY);
							return;
						}
						
					}
				}
			}
		}
	}
}
void CPlayerX::EnemyCollision()
{
	std::shared_ptr<CCollision>pCollision = std::make_shared<CCollision>();
	for (int j = 0; j < SET_PRIORITY; ++j) {
		for (int i = 0; i < MAX_OBJECT; ++i) {
			CObject* pObj = CObject::GetObjects(j, i);
			if (pObj != nullptr) {
				CObject::TYPE type = pObj->GetType();
				if (type == CObject::TYPE::TYPE_3D_BOSS_1) {
					CG_Gorira* pTest = dynamic_cast<CG_Gorira*>(pObj);
					if (pTest != nullptr) {
						if (pCollision->CylinderCollosion(CCharacter::GetPos(), pTest->GetPos(), CCharacter::GetRadius(), pTest->GetRadius()))
						{
							D3DXVECTOR3 a = CCharacter::GetPos()-pTest->GetPos();
							D3DXVECTOR3 AditionPos = -(CCharacter::GetMove() + pTest->GetMove()) + a;
							AditionPos.y = 0;
							CCharacter::AddPos(a);
						}
					}
				}
			}
		}
	}
}

//==========================================================================================
// �n�`�ƃJ�����̓����蔻��
//==========================================================================================
void CPlayerX::CamFloorCollision(LPD3DXMESH pMesh)
{
	D3DXVECTOR3 HeadPos;
	CModelParts* HeadModel = nullptr;
	for (auto& e : CCharacter::GetModelPartsVec())
	{
		if (e != nullptr)
		{
			if (e->GetIndex() == 2)
			{
				HeadModel = e;
			}
		}
	}
	HeadPos = {
		HeadModel->GetWorldMatrix()._41,
		HeadModel->GetWorldMatrix()._42,
		HeadModel->GetWorldMatrix()._43
	};

	// �n�`����
	BOOL  bIsHit = false;
	float fLandDistance{};
	DWORD dwHitIndex = 0U;
	float fHitU{};
	float fHitV{};
	
	D3DXVECTOR3 dir{};
	dir = CManager::GetInstance()->GetCamera()->GetPosV() - HeadPos;

	D3DXVec3Normalize(&dir, &dir);

	D3DXIntersect(pMesh, &HeadPos, &dir, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, nullptr, nullptr);
	
	if (bIsHit)
	{
		CManager::GetInstance()->GetCamera()->SetCameraDistance(fLandDistance);
		return;
	}
	CManager::GetInstance()->GetCamera()->SetCameraDistance(m_LastCamDis);
}