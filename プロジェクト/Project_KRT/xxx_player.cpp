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
#include "player_armState.h"
#include "player_behavior.h"
#include "player_UI.h"

#include "inimanager.h"
#include "json.hpp"
#include "game.h"

using json = nlohmann::json;

namespace
{
	const float _WORLD_WALL = 1300.0f;		//���E�̕�
	const float Damage_Ratio = 0.2f;		//�v���C���[�̃_���[�WCT(�g���ĂȂ�)
	const float _GRAVITY = 4.0f;			//�d��
	const float _MOVE_SPEED = 1.2f;			//�ړ����x
	const int _GAUGE_CTVALUE = 120;			//�U���̓��͗P�\���ԗp�̃Q�[�W�e��
	const float _BODY_RADIUS = 50.0f;
	std::vector<D3DXVECTOR3>SetButtonUIpos = {	//�{�^��UI�̍��W
		{220.0f - 220.0f / 3,250.0f,0.0f},
		{220.0f,250.0f,0.0f},
		{220.0f + 220.0f / 3,250.0f,0.0f},
		{220.0f + (220.0f / 3)*2,250.0f,0.0f},
		{220.0f + (220.0f / 3)*3,250.0f,0.0f},
		{220.0f + (220.0f / 3)*4,250.0f,0.0f},
		{220.0f + (220.0f / 3)*5,250.0f,0.0f},

	};
	struct _FILENAME	//�t�@�C���̃p�X�Ǘ��\����
	{
		std::string config;		//�t�@�C���̃p�X
		std::string section;	//�Z�N�V������
		std::string keyword;	//�L�[���[�h��
	};
	_FILENAME st_filename = {				//�v���C���[�̃��f���E���[�V�����p�t�@�C���p�X
		"data\\TEXT\\Config.ini",
		 "ModelData",
		 "PlayerMotion"
	};
	std::vector<D3DXVECTOR3> RayPos = {		//�n�`����p���C�̔�΂����W
		{0.0f,10.0f,0.0f},
		{0.0f,50.0f,0.0f}
	};
	std::string G_ARM_JSONNAME = "data\\JSON\\MAPDATA1.json";
	std::string N_ARM_JSONNAME = "data\\JSON\\MAPDATA2.json";

};

//==========================================================================================
//�R���X�g���N�^
//==========================================================================================
CPlayerX::CPlayerX(int nPriority) :CCharacter(nPriority), m_bAttackCt(false), m_nPushedKey(0), m_LastCamDis(0.0f)
{
	m_pLifeGauge = nullptr;
	m_pCctBarUI = nullptr;
	m_vButtonUI = {};
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
	CCharacter::MotionDataLoad(CiniManager::GetInstance()->GetINIData(st_filename.config, st_filename.section, st_filename.keyword));	//ini�t�@�C������ݒ肳��Ă�v���C���[�̓ǂݍ���
	CCharacter::SetRadius(_BODY_RADIUS);										//�����蔻���ݒ�(�~��)
	m_LastCamDis = CManager::GetInstance()->GetCamera()->GetCameraDistance();	//�J���������ݒ�
	m_pDebugLine = CDebugLineCylinder::Create(CCharacter::GetRadius().x);		//�f�o�b�O�p���̐���
	SetState(std::make_shared<State_Nutoral>());								//�X�e�[�g���j���[�g�����ɐݒ�
	SetAttackBehavior(std::make_shared<Attack_None>());
	SetLockOnState(std::make_shared<LockDisable>());
	SetArmState(std::make_shared<Arm_Normal>());
	m_AttackBehavior->SetExState(std::make_shared<ExAttack_Normal>());
	m_pLifeGauge = CGaugeLife::Create(MAX_LIFE);
	CCharacter::SetLife(MAX_LIFE);
	m_pWeaponIcon = CWeaponUI_Main::Create();
}

//==========================================================================================
//�I������
//==========================================================================================
void CPlayerX::Uninit()
{
	if (m_pLifeGauge != nullptr)
	{
		m_pLifeGauge->Release();
		m_pLifeGauge = nullptr;
	}
	if (m_pWeaponIcon != nullptr)
	{
		m_pWeaponIcon->Release();
		m_pWeaponIcon = nullptr;
	}
	CCharacter::Uninit();
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CPlayerX::Update()
{
	D3DXVECTOR3 CameraPos;		//�J�����̍��W�ړ��p���[�J���ϐ�
	m_OldPos = CCharacter::GetPos();	//�ߋ��̈ʒu���W��ۑ�
	m_PlayerState->ToAttack(this);		//�U���ւ̈ڍs���Ǘ�
	m_PlayerState->ToParry(this);		//�p���B�ւ̈ڍs���Ǘ�

	m_PlayerState->Move(this);			//�ړ��𐧌�

	FloorCollision();	//�v���C���[�ړ������̓����蔻��

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_M) ||
		CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_RIGHT_THUMB))
	{
		m_LockOnState->Swicth(this);
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_9) == true)
	{
		CCharacter::SetLife(CCharacter::GetLife() - 100);
	}

	m_LockOnState->UpdateCam(this);

	m_PlayerState->Parry(this);			//�p���B���̐���

	m_PlayerState->Attack(this);		//�U�����̐���

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F4))
	{
		SetArmParts(G_ARM_JSONNAME);
		m_pWeaponIcon->Release();
		m_pWeaponIcon = nullptr;
		m_pWeaponIcon = CWeaponUI_Main_Gorira::Create();
		SetArmState(std::make_shared<Arm_Gorira>());
		m_AttackBehavior->SetExState(std::make_shared<ExAttack_Gorira>());
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F6))
	{
		SetArmParts(N_ARM_JSONNAME);
		m_pWeaponIcon->Release();
		m_pWeaponIcon = nullptr;
		m_pWeaponIcon = CWeaponUI_Main::Create();
		SetArmState(std::make_shared<Arm_Normal>());
		m_AttackBehavior->SetExState(std::make_shared<ExAttack_Normal>());
	}

	CCharacter::Update();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CPlayerX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	
	//�X�e���V���o�b�t�@���g�p�����V���G�b�g�`��p�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	CCharacter::Draw();

	//�X�e���V���o�b�t�@�ւ̏������݂𖳌���
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

	//==========================
	//�L�[�{�[�h����
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
	//==========================
	//�W���C�p�b�h����
	if (!bKeyFrag)
	{
		moveDir.x = CManager::GetInstance()->GetJoypad()->GetJoyStickVecL().x;
		moveDir.z = CManager::GetInstance()->GetJoypad()->GetJoyStickVecL().y;
	}
	//==========================
	
	//��]������move�l�ƃJ�����̉�]�l����Z�o
	moveYrot = atan2f(moveDir.x, moveDir.z) + fCamRotZ;
	
	if (moveDir.x == 0.0f && moveDir.z == 0.0f)
	{
		CCharacter::AddMove({ 0.0f,-_GRAVITY,0.0f });
		CCharacter::SetNextMotion(MOTION_NUTORAL);
		return true;
	}

	CCharacter::SetRot({ 0.0f,moveYrot + D3DX_PI,0.0f });	//	�ړ������ɉ�]�����킹��

	CCharacter::AddMove({ sinf(moveYrot) * _MOVE_SPEED,-_GRAVITY,cosf(moveYrot) * _MOVE_SPEED });

	m_ArmState->WalkMotion(this);
	return true;
}

//==========================================================================================
// �v���C���[�̈ړ���������
//==========================================================================================
void CPlayerX::FloorCollision()
{
	//�e�����̐��E�̕�
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
			if (pObj == nullptr) continue; 
			CObject::TYPE type = pObj->GetType();
			if (type != CObject::TYPE::TYPE_3D_MESHOBJECT) continue; 
			CMeshGround* pTest = dynamic_cast<CMeshGround*>(pObj);
			if (pTest == nullptr) continue; 
			// �n�`����
			pMesh = pTest->GetMesh();
			D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 objpos = CCharacter::GetPos() - pTest->GetPos();
			D3DXIntersect(pMesh, &objpos, &dir, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, nullptr, nullptr);

			// ----- �ڒn������ -----
			if (bIsHit)
			{
				CCharacter::AddPos({ 0.0f, fLandDistance - CCharacter::GetMove().y - _GRAVITY,0.0f });
				FloorbumpyMesh(pMesh);
				return;
			}
		}
	}
}

//==========================================================================================
// ���[�V�����I�����ɌĂ΂��֐�(�I�[�o�[���C�h)
//==========================================================================================
bool  CPlayerX::EndMotion()
{
	if (CCharacter::GetNowMotion() == MOTION_PARRY_ATTACK)
	{
		SetState(std::make_shared<State_Nutoral>());
	}
	m_AttackBehavior->UseDisable();
	return true;
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

	if(m_nPushedKey < 7){
		m_AttackBehavior->NextAttack(this);
		if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_X)||
			CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_J))
		{
			m_vButtonUI.push_back(CButtonUI::Create(SetButtonUIpos[m_nPushedKey],9));
			++m_nPushedKey;
			pushed = true;
		}
		else if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_Y) ||
				CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_K))
		{
			m_vButtonUI.push_back(CButtonUI::Create(SetButtonUIpos[m_nPushedKey]));
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
	

	
	if (!m_AttackBehavior->GetUse())
	{
		if (GetMoveInput())
		{
			for (auto& e : m_vButtonUI)
			{
				if (e == nullptr)continue;
				e->Release();
				e = nullptr;
			}
			if (m_pCctBarUI != nullptr)
			{
				m_pCctBarUI->Release();
				m_pCctBarUI = nullptr;
			}
			m_bAttackCt = false;
			m_nPushedKey = 0;
			SetState(std::make_shared<State_Nutoral>());
			SetAttackBehavior(std::make_shared<Attack_None>());
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
		SetAttackBehavior(std::make_shared<Attack_None>());
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

	for (auto& e : apVecHitCircle)
	{
		if (e->GetEnable())	{
			pParryCircle = e;
			break;
		}
	}
	if (pParryCircle == nullptr)return;
	apVecHitCircle.clear();
	for (int j = 0; j < SET_PRIORITY; ++j) {
		for (int i = 0; i < MAX_OBJECT; ++i) {
			CObject* pObj = CObject::GetObjects(j, i);
			if (pObj == nullptr) continue; 

			CObject::TYPE type = pObj->GetType();
			if (type != CObject::TYPE::TYPE_3D_BOSS_1) continue;
			
			CG_Gorira* pTest = dynamic_cast<CG_Gorira*>(pObj);
			if (pTest == nullptr) continue;
			
			apVecHitCircle = pTest->CCharacter::GetVecHitCircle();
			for (auto& e1 : apVecHitCircle)
			{
				if (e1->GetEnable() && e1->GetMotionNum() == 2)
				{
					pBossAttackCircle = e1;
				}
			}
			if (pBossAttackCircle == nullptr) continue;
			
			D3DXVECTOR3 MainPos, SubPos;
			D3DXMATRIX MainMtx, SubMtx;
			int cnt = 0;
			for (auto& e2 : CCharacter::GetModelPartsVec())
			{
				if (pParryCircle != nullptr)
				{
					if (cnt == pParryCircle->GetParentNum())
					{
						MainMtx = e2->GetWorldMatrix();
					}
				}
				++cnt;
			}
			cnt = 0;
			for (auto& e3 : pTest->CCharacter::GetModelPartsVec())
			{
				if (pBossAttackCircle != nullptr)
				{
					if (cnt == pBossAttackCircle->GetParentNum())
					{
						SubMtx = e3->GetWorldMatrix();
					}
				}
				++cnt;
			}
			MainPos = pParryCircle->CalcMtxPos(MainMtx);
			SubPos = pParryCircle->CalcMtxPos(SubMtx);

			if(pCollision->SphireCollosion(MainPos, SubPos, pParryCircle->GetRadius(), pBossAttackCircle->GetRadius()))
			{
				CCharacter::SetNextMotion(MOTION_PARRY_ATTACK);
				pTest->SetNextMotion(3);
				CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_PARRY);
				SetState(std::make_shared<State_ParryAttack>());
				return;
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
			if (pObj == nullptr) continue;
			
			CObject::TYPE type = pObj->GetType();
			if (type != CObject::TYPE::TYPE_3D_BOSS_1) continue;
			CG_Gorira* pTest = dynamic_cast<CG_Gorira*>(pObj);
			if (pTest == nullptr) continue;

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

void CPlayerX::ToEnemyAttack()
{
	//�����蔻��N���X�𐶐�
	std::shared_ptr<CCollision>pCollision = std::make_shared<CCollision>();
	std::vector < std::shared_ptr<CHitCircle>> apVecHitCircle = CCharacter::GetVecHitCircle();
	std::shared_ptr<CHitCircle> pAttackCircle;
	for (auto& e : apVecHitCircle)
	{
		if (e->GetEnable()) {
			pAttackCircle = e;
			break;
		}
	}
	if (pAttackCircle == nullptr)return;

	for (int j = 0; j < SET_PRIORITY; ++j) {
		for (int i = 0; i < MAX_OBJECT; ++i) {
			CObject* pObj = CObject::GetObjects(j, i);
			if (pObj == nullptr) continue;
			
			CObject::TYPE type = pObj->GetType();
			if (type != CObject::TYPE::TYPE_3D_BOSS_1) continue;
		
			CG_Gorira* pTest = dynamic_cast<CG_Gorira*>(pObj);
			if (pTest == nullptr) continue;
			
			std::vector<std::shared_ptr<CHitCircle>> BHC = pTest->GetBodyHitCircle();
			for (auto& e : BHC)
			{
				if (!e->GetEnable())continue;
						
				D3DXVECTOR3 MainPos, SubPos;
				D3DXMATRIX MainMtx, SubMtx;
				int cnt = 0;
				for (auto& e1 : CCharacter::GetModelPartsVec())
				{
					if (pAttackCircle != nullptr)
					{
						if (cnt == pAttackCircle->GetParentNum())
						{
							MainMtx = e1->GetWorldMatrix();
						}
					}
					++cnt;
				}
				cnt = 0;
				for (auto& e2 : pTest->CCharacter::GetModelPartsVec())
				{
					if (e2 != nullptr)
					{
						if (cnt == e->GetParentNum())
						{
							SubMtx = e2->GetWorldMatrix();
						}
					}
					++cnt;
				}
				MainPos = pAttackCircle->CalcMtxPos(MainMtx);
				SubPos = pAttackCircle->CalcMtxPos(SubMtx);

				if (pCollision->SphireCollosion(MainPos, SubPos, pAttackCircle->GetRadius(), e->GetRadius()))
				{
					pTest->SetNextMotion(4);
					pAttackCircle->SetInvincible(true);
					pTest->BeDamaged();
					return;
				}
			}	
		}
	}
}

//==========================================================================================
// �r�p�[�c�̕t���ւ�����
//==========================================================================================
void CPlayerX::SetArmParts(std::string filename)
{
	std::string fName = filename;

	std::ifstream ifs(fName);
	if (!ifs) {
		std::cerr << "�t�@�C�����J���܂���: " << fName << std::endl;
		return;
	}
	json j;
	ifs >> j;

	for (auto& [key, value] : j.items()) {
		D3DXVECTOR3 pos = { value.at("POS").at("X").get<float>(),  value.at("POS").at("Y").get<float>(), value.at("POS").at("Z").get<float>() };
		D3DXVECTOR3 rot = { value.at("ROT").at("X").get<float>(),  value.at("ROT").at("Y").get<float>(), value.at("ROT").at("Z").get<float>() };
		std::string s_filename = value.at("FILENAME").get<std::string>();
		int Parent = value.at("PARENT").get<int>();
		int index = value.at("INDEX").get<int>();

		CModelParts* instance = CModelParts::Create({0.0f,0.0f,0.0f}, s_filename.c_str());
		instance->SetPos(pos);
		instance->SetRot(rot);

		instance->SetDefault();
		instance->SetIndex(index);
		instance->SetParentNum(Parent);
		CCharacter::ChangeModelParts(instance);
	}
	CCharacter::SetAllPartsParent();
}