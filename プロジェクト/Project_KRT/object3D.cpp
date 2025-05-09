//===============================================================================
//
//  3D�I�u�W�F�N�g(object3D.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "object3D.h"
#include "manager.h"


//�ÓI�����o������
const float CObject3D::MAX_OBJ3DHEIGHT = 500.0f;
const float CObject3D::MAX_OBJ3DWIDTH = 500.0f;

const int CObject3D::MAX_VERTEX = 4;
const int CObject3D::MAX_POLYGON = 2;


CObject3D::CObject3D(int nPriority) : CObject(nPriority) ,m_fWidth(0), m_fHeight(0)
{
	m_pVtxBuffObject3D = nullptr;
	m_pTextureObject3D = nullptr;
}

CObject3D::~CObject3D()
{
}

//==========================================================================================
//����������
//==========================================================================================
void CObject3D::Init()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX,
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
void CObject3D::Uninit()
{
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
void CObject3D::Update()
{

}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CObject3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans,mtxSize;
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
	pDevice->SetTransform(D3DTS_WORLD,
		&m_mtxWorld);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffObject3D, 0, sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureObject3D);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		MAX_POLYGON);
}


//==========================================================================================
//��������
//==========================================================================================
CObject3D* CObject3D::Create(D3DXVECTOR3 pos)
{
	CObject3D* object3D = new CObject3D;
	object3D->m_pos = pos;
	object3D->SetPolygonParam(pos, MAX_OBJ3DHEIGHT, MAX_OBJ3DWIDTH);

	object3D->Init();
	return object3D;
}

//==========================================================================================
//�������̏����ݒ菈��
//==========================================================================================
void CObject3D::SetPolygonParam(D3DXVECTOR3 pos, float fHeight, float fWidth)
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
//�e�N�X�`���̐�������
//==========================================================================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTextureObject3D = pTex;
}

//==========================================================================================
//�T�C�Y�ύX����
//==========================================================================================
void CObject3D::AddSize(float Value)
{
	m_size.z += Value;
	m_size.y += Value;
	//m_size.x += Value;
}

//==========================================================================================
//�T�C�Y�ύX����
//==========================================================================================
void CObject3D::SetSize(float size)
{
	m_size.z = size;
	m_size.y = size;
}

//==========================================================================================
//�T�C�Y�ύX����
//==========================================================================================
float CObject3D::GetSize()
{
	return m_size.z;
}

//==========================================================================================
//��]�ݒ菈��
//==========================================================================================
void CObject3D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;

}
//==========================================================================================
//���W��Ԃ�
//==========================================================================================
D3DXVECTOR3 CObject3D::GetPos()
{
	return m_pos;
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CObject3D::Draw(D3DXMATRIX SetmtxRot)
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
		&SetmtxRot);
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
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffObject3D, 0, sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureObject3D);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		MAX_POLYGON);
}