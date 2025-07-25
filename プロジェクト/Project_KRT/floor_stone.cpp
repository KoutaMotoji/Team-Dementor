//===============================================================================
//
//  �n�`���b�V���̏���(mesh_ground.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "floor_stone.h"
#include "field_manager.h"

#include "manager.h"
#include "game.h"


CMeshGround::CMeshGround(int nPriority) :CObjectX(nPriority), m_mode(0)
{

}

CMeshGround::~CMeshGround()
{

}

//==========================================================================================
//����������
//==========================================================================================
void CMeshGround::Init()
{
	CObject::SetType(TYPE_3D_MESHOBJECT);
	CObjectX::Init();
	CField_Manager::GetInstance()->RegistObj(this);
}

//==========================================================================================
//�I������
//==========================================================================================
void CMeshGround::Uninit()
{
	CObjectX::Uninit();
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CMeshGround::Update()
{
	
	CObjectX::Update();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CMeshGround::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();;


	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	CObjectX::Draw();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	CObjectX::Draw();

}

//==========================================================================================
//��������
//==========================================================================================
CMeshGround* CMeshGround::Create(D3DXVECTOR3 pos)
{
	CMeshGround* enemy = new CMeshGround;
	enemy->BindModel("data\\MODEL\\Floor_box.x");
	enemy->SetModelParam(pos);
	enemy->Init();
	return enemy;
}

//==========================================================================================
//��������
//==========================================================================================
CMeshGround* CMeshGround::Create(D3DXVECTOR3 pos,int i)
{
	CMeshGround* enemy = new CMeshGround;
	enemy->BindModel("data\\MODEL\\boss_field000.x");
	enemy->SetModelParam(pos);
	enemy->Init();
	return enemy;
}

