
#include "title_obj.h"
#include "inimanager.h"
#include "collision.h"

namespace
{

	struct _FILENAME	//�t�@�C���̃p�X�Ǘ��\����
	{
		std::string config;		//�t�@�C���̃p�X
		std::string section;	//�Z�N�V������
		std::string keyword;	//�L�[���[�h��
	};
	_FILENAME st_filename = {				//�v���C���[�̃��f���E���[�V�����p�t�@�C���p�X
		"data\\TEXT\\Config.ini",
		 "ModelData",
		 "TitlePlayerMotion"
	};
	std::string GROUND_FILENAME = "data\\MODEL\\title_field.x";
	std::string TREE_FILENAME = "data\\TEXTURE\\Tree000.png";

	D3DXVECTOR3 T_PLAYER_POS = { 100.0f,-110.0f,0.0f };
	D3DXVECTOR3 T_FIELD_POS = { 0.0f,500.0f,0.0f };
	float TREE_RADIUS = 200.0f;
};

//==========================================================================================
//�R���X�g���N�^
//==========================================================================================
CT_Player::CT_Player(int nPriority) :CCharacter(nPriority)
{

}

//==========================================================================================
//�f�X�g���N�^
//==========================================================================================
CT_Player::~CT_Player()
{

}

//==========================================================================================
//����������
//==========================================================================================
void CT_Player::Init()
{
	CObject::SetType(TYPE_3D_TITLEOBJ);						//�I�u�W�F�N�g�ꊇ�Ǘ��p�̃^�C�v��ݒ�
	CCharacter::Init();
	CCharacter::MotionDataLoad(CiniManager::GetInstance()->GetINIData(st_filename.config, st_filename.section, st_filename.keyword));	//ini�t�@�C������ݒ肳��Ă�v���C���[�̓ǂݍ���
	CCharacter::SetPos(T_PLAYER_POS);
	CCharacter::AddRot({ 0.0f,-1.56,0.0f });
}

//==========================================================================================
//�I������
//==========================================================================================
void CT_Player::Uninit()
{

	CCharacter::Uninit();
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CT_Player::Update()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN) ||
		CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_A))
	{
		CCharacter::SetNextMotion(MOTION_ACTION);
	}
	CCharacter::Update();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CT_Player::Draw()
{
	CCharacter::Draw();
}

//==========================================================================================
//��������
//==========================================================================================
CT_Player* CT_Player::Create()
{
	CT_Player* player = new CT_Player;
	player->Init();
	player->SetMove({ 0.0f,0.0f,0.0f });
	return player;
}

//==========================================================================================
// ���[�V�����I�����ɌĂ΂��֐�(�I�[�o�[���C�h)
//==========================================================================================
bool  CT_Player::EndMotion()
{

	return true;
}

CT_Graound::CT_Graound(int nPriority) :CObjectX(nPriority)
{

}

CT_Graound::~CT_Graound()
{

}

//==========================================================================================
//����������
//==========================================================================================
void CT_Graound::Init()
{
	CObject::SetType(TYPE_3D_TITLEMESH);
	CObjectX::Init();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CT_Graound::Draw()
{
	CObjectX::Draw();
}

//==========================================================================================
//��������
//==========================================================================================
CT_Graound* CT_Graound::Create()
{
	CT_Graound* enemy = new CT_Graound;
	enemy->BindModel(GROUND_FILENAME.c_str());
	enemy->SetModelParam(T_FIELD_POS);
	enemy->Init();
	return enemy;
}

CTreeBillboard::CTreeBillboard(int nPriority) :CBillboard(nPriority)
{
}

CTreeBillboard::~CTreeBillboard()
{

}

//==========================================================================================
//����������
//==========================================================================================
void CTreeBillboard::Init()
{
	CObject::SetType(TYPE_BILLBOARD);
	CBillboard::Init();
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(TREE_FILENAME.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), { 1,1 });		//��5�A�c3�ɕ���
}

//==========================================================================================
//�I������
//==========================================================================================
void CTreeBillboard::Uninit()
{
	CBillboard::Uninit();
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CTreeBillboard::Update()
{

	CBillboard::Update();
}

void CTreeBillboard::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�A���t�@�e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CBillboard::Draw();

	//�ʏ�̍����ɖ߂��ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


//==========================================================================================
//��������
//==========================================================================================
CTreeBillboard* CTreeBillboard::Create(D3DXVECTOR3 pos)
{
	CTreeBillboard* tree = new CTreeBillboard();

	tree->SetPolygonParam(pos, TREE_RADIUS, TREE_RADIUS, { 1.0f,1.0f,1.0f,1.0f });
	tree->Init();
	tree->AddPos({ 0.0f,-1000.0f,0.0f });
	tree->SetPosGround(TREE_RADIUS);
	return tree;
}

//==========================================================================================
//�n�`���b�V���ɉ����Ĉʒu�����킹�鏈��
//==========================================================================================
void CTreeBillboard::SetPosGround(float HalfRadius)
{
	std::shared_ptr<CCollision> pCollision = std::make_shared<CCollision>();
	D3DXVECTOR3 dir = { 0.0f,1.0f,0.0f };
	float Distance = 0;

	LPD3DXMESH pMesh = nullptr;
	for (int j = 0; j < SET_PRIORITY; j++) {
		for (int i = 0; i < MAX_OBJECT; i++) {
			CObject* pObj = CObject::GetObjects(j, i);
			if (pObj == nullptr) continue;
			CObject::TYPE type = pObj->GetType();
			if (type != CObject::TYPE::TYPE_3D_TITLEMESH) continue;
			CT_Graound* pTest = dynamic_cast<CT_Graound*>(pObj);
			if (pTest == nullptr) continue;
			pMesh = pTest->GetMesh();
			D3DXVECTOR3 pos = CBillboard::GetPos();

			D3DXVECTOR3 objpos = pos - pTest->GetPos();
			float ChedkDis = 2000.0f;
			// ----- �ڒn������ -----
			if (pCollision->MeshToIntersectCollision(&Distance, pMesh, objpos, dir, ChedkDis))
			{
				CBillboard::AddPos({ 0.0f,Distance + HalfRadius,0.0f });
				return;
			}
		}
	}

}