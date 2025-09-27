//===============================================================================
//
//  �G�l�~�[����(enemy.cpp)
//								����F��|�
// 
//===============================================================================

#pragma comment(lib,"winmm.lib")		//�����_���ɕK�v

#include "enemy.h"
#include "character.h"
#include "floor_stone.h"
#include "player_observer.h"
#include "enemy_attack_state.h"
#include "enemy_ai.h"
#include "inimanager.h"
#include "weapon.h"
#include "field_manager.h"

// �ړ������Ɖ�]�p���܂Ƃ߂��e�[�u��
struct MoveDir
{
	D3DXVECTOR3 move;   // �ړ��x�N�g��
	D3DXVECTOR3 rot;    // ��]�p
};

namespace
{
	const MoveDir g_MoveTable[] =
	{
		// ��������
		{ {  0.0f, 0.0f, -1.0f }, { 0.0f,  0.0f,          0.0f } }, // �O
		{ {  0.0f, 0.0f,  1.0f }, { 0.0f,  D3DX_PI,       0.0f } }, // ��
		{ { -1.0f, 0.0f,  0.0f }, { 0.0f,  D3DX_PI * 0.5f,0.0f } }, // ��
		{ {  1.0f, 0.0f,  0.0f }, { 0.0f, -D3DX_PI * 0.5f,0.0f } }, // �E

		// �΂ߕ���
		{ { -1.0f, 0.0f, -1.0f }, { 0.0f, -D3DX_PI * 0.25f,0.0f } }, // ���O
		{ {  1.0f, 0.0f, -1.0f }, { 0.0f,  D3DX_PI * 0.25f,0.0f } }, // �E�O
		{ { -1.0f, 0.0f,  1.0f }, { 0.0f,  D3DX_PI * 0.75f,0.0f } }, // ����
		{ {  1.0f, 0.0f,  1.0f }, { 0.0f, -D3DX_PI * 0.75f,0.0f } }  // �E��
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

// �ÓI�ϐ���`
int CEnemy::s_nWeaponCount = 0;
const int CEnemy::MAX_WEAPON = 1;

//==========================================================================================
//�R���X�g���N�^
//==========================================================================================
CEnemy::CEnemy(): m_bAttackCt(false), m_nAttackcnt(0), m_moveFlag(true), m_nLife(0), m_bDying(false), m_bHidden(false), m_bDeathAnimFinished(false)
, m_bStunned(false), m_StunTimer(0), m_RespawnTimerFrames(0), m_RespawnDelayFrames(120), m_RespawnPos({ 0.0f,-1000.0f,0.0f })
{

}

//==========================================================================================
//����������
//==========================================================================================
void CEnemy::Init()
{
	CObject::SetType(TYPE_ENEMY);						//�I�u�W�F�N�g�ꊇ�Ǘ��p�̃^�C�v��ݒ�
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

	// �X�e�[�g������
	SetState(std::make_shared<Enemy_Nutoral>());
	SetAttackState(std::make_shared<E_Attack_None>());

	// �f�o�b�O���C����
	m_pDebugLine = CDebugLineCylinder::Create(CCharacter::GetRadius().x);

	// �q�b�g�T�[�N���쐬
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

	// �G��ԃt���O��������
	m_bDying = false;
	m_bHidden = false;
	m_bDeathAnimFinished = false;
	m_bStunned = false;
	m_StunTimer = 0;
	m_RespawnTimerFrames = 0;
}

//==========================================================================================
//�I������
//==========================================================================================
void CEnemy::Uninit()
{
	CCharacter::Uninit();
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CEnemy::Update()
{
	FloorCollision();	//�v���C���[�ړ������̓����蔻��
	m_OldPos = CCharacter::GetPos();

	if (m_pEnemyAI) m_pEnemyAI->Update(this);
	if (m_bEnemyAI) m_bEnemyAI->AI_Update(this);

	// --- �s������ ---
	if (m_bDying)
	{
		// ���S���͍s����~�B
	}
	else if (m_bStunned)
	{
		// �̂����蒆�͍s���ł��Ȃ�
		if (--m_StunTimer <= 0)
		{
			m_bStunned = false;
			CCharacter::SetNextMotion(0); // �ҋ@�ɖ߂�
		}
	}
	else
	{
		// ���펞�̍s���i��B���E�񎀖S���̂݁j
		if (!m_bHidden)
		{
			m_State->Move(this);
			m_State->Attack(this);

			if (m_AttackState)
				m_AttackState->AttackUpdate(this);
		}
	}

	// �����E�A�j���X�V
	CCharacter::AddPos({ 0.0f, -_GRAVITY, 0.0f });
	CCharacter::Update();

	// �q�b�g�T�[�N���̗L��/����
	for (auto& hit : m_pHC_BodyCollision)
	{
		if (m_bHidden) hit->SetDisable();
		else           hit->SetEnable();
	}

	// --- ���S�J�n����i���C�t <=0�j ---
	if (!m_bDying && CCharacter::GetLife() <= 0)
	{
		// ���S�J�n
		m_bDying = true;
		m_bDeathAnimFinished = false;
		m_RespawnTimerFrames = 0;

		// �����ڂ̎��S���[�V����
		SetAttackState(std::make_shared<E_Attack_None>()); // �U����~
		CCharacter::SetNextMotion(MOTION_DIE);

		// �U���� AI ���~���������Ȃ炱���Ńt���O���g���ău���b�N�i���ɍs������ρj
	}

	// --- ���S�A�j���I���Ŕ�\���ɂ���iEndMotion() �ɂ�� m_bDeathAnimFinished �� true �ɂȂ�j ---
	if (m_bDying && !m_bHidden && m_bDeathAnimFinished)
	{
		m_bHidden = true;
		for (auto& hit : m_pHC_BodyCollision) hit->SetDisable();
	}

	// --- �t�F�[���Z�[�t�F���ԂŔ�\�������X�|�[������iEndMotion ���Ă΂�Ȃ��ꍇ�������\�ɂ���j ---
	if (m_bDying)
	{
		++m_RespawnTimerFrames;

		// 1�b�i��60�t���[���j�ŕ\���I�t�i�|��Ă��鉉�o�͌�����j
		if (m_RespawnTimerFrames == 120)
		{
			m_bHidden = true;
			for (auto& hit : m_pHC_BodyCollision) hit->SetDisable();
		}

		// 2�b�i��120�t���[���j�Ń��X�|�[��
		if (m_RespawnTimerFrames >= m_RespawnDelayFrames)
		{
			Respawn();
		}
	}

	if (m_bPendingDropWeapon)
	{
		// ����̏���`�F�b�N
		if (s_nWeaponCount < MAX_WEAPON)
		{
			CWeapon* weapon = CWeapon::Create(m_WeaponDropPos);
			CField_Manager::GetInstance()->RegistObj(weapon);
			s_nWeaponCount++;      // �J�E���g��
		}
		m_bPendingDropWeapon = false;
	}
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CEnemy::Draw()
{
	if (m_bHidden) return; // ��\�����͕`����X�L�b�v

	// �����̕`�揈�������̂܂�
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	CCharacter::Draw();

	// �@���̎������K���𖳌���
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
	// �t���O���Z�b�g
	m_bDying = false;
	m_bHidden = false;
	m_bDeathAnimFinished = false;
	m_bStunned = false;
	m_StunTimer = 0;
	m_RespawnTimerFrames = 0;

	// HP�E���[�V����������
	CCharacter::SetLife(_MAX_LIFE);
	CCharacter::SetMove({ 0.0f, 0.0f, 0.0f });
	CCharacter::SetNextMotion(0);

	// �����_�����X�|�[�����W��ݒ�
	float randX = static_cast<float>(rand()) / RAND_MAX * 2.0f * _WORLD_WALL - _WORLD_WALL; // -_WORLD_WALL�`+_WORLD_WALL
	float randZ = static_cast<float>(rand()) / RAND_MAX * 2.0f * _WORLD_WALL - _WORLD_WALL;
	m_RespawnPos = D3DXVECTOR3(randX, 0.0f, randZ); // Y��0�ɐݒ�A�n�`����ŏC�������

	CCharacter::SetPos(m_RespawnPos);

	// AI / �U���X�e�[�g��������
	SetAttackState(std::make_shared<E_Attack_None>());
	SetState(std::make_shared<Enemy_Nutoral>());

	// AI �^�C�}�[��������
	if (m_pEnemyAI) m_pEnemyAI->Init();
	if (m_bEnemyAI) m_bEnemyAI->AI_Init();

	// �q�b�g�T�[�N������
	for (auto& hit : m_pHC_BodyCollision) hit->SetEnable();
}

// ���킪�E��ꂽ��ĂԊ֐�
void CEnemy::OnWeaponPicked()
{
	if (s_nWeaponCount > 0)
		s_nWeaponCount--;
}

//==========================================================================================
//��������
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
// ���[�V�����I�����ɌĂ΂��֐�(�I�[�o�[���C�h)
//==========================================================================================
bool  CEnemy::EndMotion()
{
	// ���[�V�����I���R�[���o�b�N�i�G���W������Ă΂��j
	int curMotion = CCharacter::GetNextMotion();
	if (curMotion == MOTION_DIE)
	{
		// ���S���[�V�������I��������Ƃ��L�^
		m_bDeathAnimFinished = true;
	}

	// ������ AttackFinish �Ăяo���i�ێ��j
	if (m_AttackState)
		m_AttackState->AttackFinish(this);

	return true;
}

//==========================================================================================
// �L�����N�^�[�̈ړ���������
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
				return;
			}
		}
	}
}

//==========================================================================================
// �L�����N�^�[�̈ړ�
//==========================================================================================
void CEnemy::Move()
{
	// �U�����͓����Ȃ�
	if (CCharacter::GetNextMotion() >= 2 && CCharacter::GetNextMotion() <= 5)
		return;

	// ���t���[�����Ƃɕ�������
	m_nTime++;
	if (m_nTime >= 180)
	{
		m_nTime = 0;
		m_Direction = rand() % MOVE_DIR_COUNT;
	}

	// �ړ�����
	const MoveDir& dir = g_MoveTable[m_Direction];

	D3DXVECTOR3 normMove;
	D3DXVec3Normalize(&normMove, &dir.move);
	normMove *= _MOVE_SPEED;

	CCharacter::AddMove(normMove);
	CCharacter::SetNextMotion(1);

	// �i�s���������]�p���v�Z
	float angle = atan2f(normMove.x, normMove.z) + D3DX_PI; // ���f�����ʂ�Z-�Ȃ�+��
	CCharacter::SetRot({ 0.0f, angle, 0.0f });

	// �d�͏���
	CCharacter::AddPos({ 0.0f, -_GRAVITY, 0.0f });

	// �ړ��ʂ��ʒu�ɔ��f �� ���Z�b�g
	CCharacter::AddPos(CCharacter::GetMove());
	CCharacter::SetMove({ 0.0f, 0.0f, 0.0f });
}

//==========================================================================================
// �L�����N�^�[�̍U���𐧌�
//==========================================================================================
void CEnemy::DoAttack()
{
	// ���S�� or ��e���Ȃ�U�����Ȃ�
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
// �L�����N�^�[�̔�_�����
//==========================================================================================
void CEnemy::BeDamaged()
{
	// ���S�����\�����͖�����
	if (m_bDying || m_bHidden) return;

	m_State->Damage(this);
}

//==========================================================================================
// �L�����N�^�[�̔�_������
//==========================================================================================
void CEnemy::Damaged()
{
	// ���S�����\�����͖�����
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

		// ���C�t��0�ȉ��Ȃ疳�����Ŏ��S�J�n
		m_bDying = true;
		m_bDeathAnimFinished = false;
		m_RespawnTimerFrames = 0;

		SetAttackState(std::make_shared<E_Attack_None>());
		CCharacter::SetNextMotion(MOTION_DIE);
	}
	else
	{
		// �̂������Ԃɂ���
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