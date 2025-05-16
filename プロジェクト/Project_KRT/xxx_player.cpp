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

#include "inimanager.h"
#include "game.h"

namespace
{
	float _WORLD_WALL = 1300.0f;
	float Damage_Ratio = 0.2f;
	float _GRAVITY = 4.0f;
	float _MOVE_SPEED = 1.5f;
	float _JUMP_HEIGHT = 120.0f;
	int _GAUGE_CTVALUE = 60;
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
};

//==========================================================================================
//�R���X�g���N�^
//==========================================================================================
CPlayerX::CPlayerX() : m_bAttackCt(false), m_nPushedKey(0), m_pModel(nullptr)
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
	m_pModel = CCharacter::Create({0.0f,0.0f,0.0f});
	m_pModel->MotionDataLoad(CiniManager::GetInstance()->GetINIData(st_filename.config, st_filename.section, st_filename.keyword));
}

//==========================================================================================
//�I������
//==========================================================================================
void CPlayerX::Uninit()
{
	m_pModel->Uninit();
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CPlayerX::Update()
{
	D3DXVECTOR3 CameraPos;		//�J�����̍��W�ړ��p���[�J���ϐ�
	m_OldPos = CObjectX::GetPos();

	FloorCollision();	//�v���C���[�ړ������̓����蔻��
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_X))
	{
		m_pModel->SetNextMotion(MOTION_ATTACK);
	}
	if (CManager::GetInstance()->GetJoypad()->GetRelease(CJoypad::JOYPAD_RIGHT_SHOULDER))
	{
		m_pModel->SetNextMotion(MOTION_NUTORAL);
	}
	if (CManager::GetInstance()->GetJoypad()->GetRepeat(CJoypad::JOYPAD_RIGHT_SHOULDER))
	{
		m_pModel->SetNextMotion(MOTION_PARRY);
	}

	if (m_pModel->GetNextMotion() != MOTION_ATTACK && m_pModel->GetNextMotion() != MOTION_PARRY)
	{
		PMove(CManager::GetInstance()->GetCamera()->GetRotZ());	//�v���C���[�ړ��֘A�̏���
	}
	PAttackInfo();

	CObjectX::AddPos(m_move);
	
	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * 0.14f;
	m_move.y += (0.0f - m_move.y) * 0.14f;
	m_move.z += (0.0f - m_move.z) * 0.17f;
	CManager::GetInstance()->GetCamera()->SetPlayerPos(CObjectX::GetPos());
	D3DXVECTOR3 MODELPOS = CObjectX::GetPos();
	MODELPOS.y += 10.0f;
	m_pModel->SetPos(MODELPOS);
	m_pModel->SetRot(CObjectX::GetRot());
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CPlayerX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;

	//�N�I�[�^�j�I�����쐬
	D3DXQuaternionRotationAxis(
		&m_quat,
		&m_vecAxis,
		m_fValueRot);

	//�N�I�[�^�j�I�������]�}�g���b�N�X���쐬
	D3DXMatrixRotationQuaternion(
		&mtxRot,
		&m_quat);
	m_mtxRot = mtxRot;		//��]�}�g���b�N�X��ۑ�

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�傫���𔽉f
	D3DXMatrixScaling(&mtxSize,
		m_size.y,
		m_size.x,
		m_size.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxSize);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&m_mtxRot);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,
		&m_mtxWorld);
	//CObjectX::Draw();
	m_pModel->Draw();
}

//==========================================================================================
//��������
//==========================================================================================
CPlayerX* CPlayerX::Create(D3DXVECTOR3 pos)
{
	CPlayerX* player = new CPlayerX;
	player->Init();
	player->BindModel("data\\MODEL\\P_Model.x");
	player->SetModelParam(pos);
	player->m_move = { 0.0f,0.0f,0.0f };
	player->m_size = { 1.0f,1.0f,1.0f };
	player->m_OldPos = pos;
	return player;
}

//==========================================================================================
//�ړ�����
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
		m_pModel->SetNextMotion(MOTION_NUTORAL);
		return true;
	}

	CObjectX::SetRot({ 0.0f,moveYrot + D3DX_PI,0.0f });
	m_move.x += sinf(moveYrot) * _MOVE_SPEED;
	m_move.z += cosf(moveYrot) * _MOVE_SPEED;

	m_move.y -= _GRAVITY;

	m_pModel->SetNextMotion(MOTION_WALK);
	

	return true;
}

//==========================================================================================
// �v���C���[�̈ړ���������
//==========================================================================================
void CPlayerX::FloorCollision()
{
	if (CObjectX::GetPos().z < -_WORLD_WALL)
	{
		CObjectX::SetPos({ CObjectX::GetPos().x, CObjectX::GetPos().y, -_WORLD_WALL });
	}
	else if (CObjectX::GetPos().z > _WORLD_WALL)
	{
		CObjectX::SetPos({ CObjectX::GetPos().x, CObjectX::GetPos().y, _WORLD_WALL });
	}
	if (CObjectX::GetPos().x < -_WORLD_WALL)
	{
		CObjectX::SetPos({ -_WORLD_WALL, CObjectX::GetPos().y, CObjectX::GetPos().z });
	}
	else if (CObjectX::GetPos().x > _WORLD_WALL)
	{
		CObjectX::SetPos({ _WORLD_WALL, CObjectX::GetPos().y, CObjectX::GetPos().z });
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
						if (pTest != nullptr) {
							// �n�`����
							pMesh = pTest->GetMesh();
							D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
							D3DXVECTOR3 objpos = CObjectX::GetPos() - pTest->GetPos();
							D3DXIntersect(pMesh, &objpos, &dir, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, nullptr, nullptr);

							// ----- �ڒn������ -----
							if (bIsHit)
							{
								CObjectX::AddPos({ 0.0f, fLandDistance - m_move.y - _GRAVITY,0.0f });
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
// �v���C���[�̒n�`�̋N���ړ�
//==========================================================================================
bool FloorbumpyMesh(LPD3DXMESH pMesh)
{
	struct RayInfo
	{
		// �n�`����
		BOOL  bIsHit = false;
		float fLandDistance = {};
		DWORD dwHitIndex = 0U;
		float fHitU;
		float fHitV;
	};

	std::vector<RayInfo>RI();
	return true;
}


//==========================================================================================
// �v���C���[�̍U������
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