//===============================================================================
//
//  �U���̓����蔻��(�\��)�̉���(attack_range.cpp)
//	����F��|�
// 
//===============================================================================

#include "attack_range.h"
#include "manager.h"

namespace
{
	const int MAX_VERTEX = 4;
	const int MAX_VERTEX_FAN = 3;
	const int MAX_POLYGON = 2;
};

CAttackRange::CAttackRange() :m_pos{}, m_size{} {

}

CAttackRange::~CAttackRange(){
    Uninit();
}

//==========================================================================================
//����������
//==========================================================================================
void CAttackRange::Init()
{
    CObject3D::Init();
}

//==========================================================================================
//�I������
//==========================================================================================
void CAttackRange::Uninit(){
    CObject3D::Uninit();
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CAttackRange::Update(){
    CObject3D::Update();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CAttackRange::Draw()
{
    CObject3D::Draw();
}

//==========================================================================================
//��������
//==========================================================================================
CAttackRange* CAttackRange::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CAttackRange* attackrange = new CAttackRange;
    attackrange->m_pos = pos;
    attackrange->SetPolygonParam(pos, size.x, size.y);

    attackrange->Init();
    return attackrange;
}

CDrawFan::CDrawFan() :m_pos{}, m_size{} {

}

CDrawFan::~CDrawFan(){
    Uninit();
}

//==========================================================================================
//����������
//==========================================================================================
void CDrawFan::Init()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX_FAN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffObject3D,
		NULL);
	VERTEX_3D* pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuffObject3D->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, 0.0f, m_fHeight);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, 0.0f, m_fHeight);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, 0.0f, -m_fHeight);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, 0.0f, -m_fHeight);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffObject3D->Unlock();

}

//==========================================================================================
//�I������
//==========================================================================================
void CDrawFan::Uninit(){
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuffObject3D != NULL)
	{
		m_pVtxBuffObject3D->Release();
		m_pVtxBuffObject3D = NULL;
	}
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CDrawFan::Update(){

}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CDrawFan::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;
	//���[���h�}�g���b�N�X
	D3DXMatrixIdentity(&m_mtxWorld);
	//�傫���𔽉f(�����ݒ肳�ꂽ�傫��x,z����l1.0�Ƃ����T�C�Y�X�P�[�����O)
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
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffObject3D, 0, sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureObject3D);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN,
		0,
		MAX_POLYGON);

}

//==========================================================================================
//�������̏����ݒ菈��
//==========================================================================================
void CDrawFan::SetPolygonParam(D3DXVECTOR3 pos, float fHeight, float fWidth)
{
	m_pos = pos;
	m_fHeight = fHeight;
	m_fWidth = fWidth;
	m_size = { 1.0f,1.0f,1.0f };
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//�Ίp���̒������Z�o
	m_fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) / 2.0f;
	//�Ίp���̊p�x���Z�o
	m_fAngle = atan2f(m_fWidth, m_fHeight);
}

//==========================================================================================
//��������
//==========================================================================================
CDrawFan* CDrawFan::Create(D3DXVECTOR3 pos)
{
    CDrawFan* drawFan = new CDrawFan;
    drawFan->m_pos = pos;
	drawFan->SetPolygonParam(pos, 500.0f, 500.0f);
    drawFan->Init();
    return drawFan;
}