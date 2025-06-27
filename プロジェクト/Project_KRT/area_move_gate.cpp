//===============================================================================
//
//  �G���A�ړ��p�Q�[�g�I�u�W�F�N�g(area_move_gate.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "area_move_gate.h"
#include "field_manager.h"
#include "player_observer.h"
#include "floor_stone.h"

namespace
{
	float _RADIUS = 100.0f;
}

//==========================================================================================
//����������
//==========================================================================================
void CAreaGate::Init()
{
	CObject::SetType(TYPE_AREAGATE);
	CObjectX::Init();
	SetFirstPosY();
	CField_Manager::GetInstance()->RegistObj(this);
	m_pDebugLine = CDebugLineCylinder::Create(_RADIUS, {0.0f,7.0f,7.0f,1.0f});		//�f�o�b�O�p���̐���
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CAreaGate::Update()
{
	CObjectX::Update();
	if (ToPlayerCollision())
	{
		if (!m_bPass)
		{
			m_bPass = true;
			CField_Manager::GetInstance()->SetField();
		}
	}
}


//==========================================================================================
//�`�揈��
//==========================================================================================
void CAreaGate::Draw()
{
	m_pDebugLine->Draw(CObjectX::GetPos());
	CObjectX::Draw();
}

//==========================================================================================
//��������
//==========================================================================================
CAreaGate* CAreaGate::Create(D3DXVECTOR3 pos)
{
	CAreaGate* enemy = new CAreaGate;

	enemy->BindModel("data\\MODEL\\AreaMove_obj.x");
	enemy->SetModelParam({ pos.x,-1000.0f,pos.z });
	enemy->Init();
	enemy->SetRot({ 0.0f,0.0f,0.0f });
	return enemy;
}

//==========================================================================================
//�v���C���[�������蔻����ɂ��邩�`�F�b�N
//==========================================================================================
bool CAreaGate::ToPlayerCollision()
{
	D3DXVECTOR3 PlayerPos = CPlayerObserver::GetInstance()->GetPlayerPos();

	float LengthX = CObjectX::GetPos().x - PlayerPos.x;
	float LengthZ = CObjectX::GetPos().z - PlayerPos.z;

	return (((LengthX * LengthX) + (LengthZ * LengthZ)) <= (_RADIUS * _RADIUS));
}

//==========================================================================================
//�������ꂽ���ɒn�`�Ɉʒu�����킹��
//==========================================================================================
void CAreaGate::SetFirstPosY()
{
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
			D3DXVECTOR3 objpos = CObjectX::GetPos() - pTest->GetPos();
			D3DXIntersect(pMesh, &objpos, &dir, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, nullptr, nullptr);

			// ----- �ڒn������ -----
			if (bIsHit)
			{
				CObjectX::AddPos({ 0.0f,fLandDistance,0.0f });
				return;
			}
		}
	}
}