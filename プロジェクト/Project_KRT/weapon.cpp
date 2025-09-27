//===============================================================================
//
//  �����̏���(weapom.cpp)
//					����F��|�
// 
//===============================================================================

#include "weapon.h"

#include "manager.h"
#include "game.h"

namespace 
{
	float ROTATE_SPEED = 0.05f;   // ��]���x�i���W�A�� / �t���[���j
	float FLOAT_SPEED = 0.05f;  // �㉺�ړ��̑���
	float FLOAT_RANGE = 0.5f;  // �㉺�ړ��̕�
}

CWeapon::CWeapon(int nPriority) :CObjectX(nPriority)
{

}

CWeapon::~CWeapon()
{

}

//==========================================================================================
//����������
//==========================================================================================
void CWeapon::Init()
{
	D3DXVECTOR3 pos = GetPos();
	pos.y = -600.0f;  // �n�ʂ̂��傢��ɌŒ�
	SetPos(pos);

	m_baseY = pos.y;

	CObject::SetType(TYPE_WEAPON);
	CObjectX::Init();
}

//==========================================================================================
//�I������
//==========================================================================================
void CWeapon::Uninit()
{
	CObjectX::Uninit();
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CWeapon::Update()
{
	if (m_bEquipped) return;

	CObjectX::Update();

	// ��]
	D3DXVECTOR3 rot = GetRot();
	rot.y += ROTATE_SPEED;
	if (rot.y > D3DX_PI * 2.0f) rot.y -= D3DX_PI * 2.0f;
	SetRot(rot);

	// �㉺�ړ�
	m_floatTime += FLOAT_SPEED;
	D3DXVECTOR3 pos = GetPos();
	pos.y = m_baseY + sinf(m_floatTime) * FLOAT_RANGE;
	SetPos(pos);
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CWeapon::Draw()
{
	if (m_bEquipped) return;

	CObjectX::Draw();
}

//==========================================================================================
//��������
//==========================================================================================
CWeapon* CWeapon::Create(D3DXVECTOR3 pos)
{
	CWeapon* weapon = new CWeapon;
	weapon->BindModel("data\\MODEL\\G_riraWeapon\\G_riraWeapon.x");
	weapon->SetModelParam(pos);
	weapon->Init();
	return weapon;
}