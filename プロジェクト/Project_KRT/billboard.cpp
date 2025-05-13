//===============================================================================
//
//  �r���{�[�h���N���X(billboard.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "billboard.h"
#include "manager.h"


//�ÓI�����o������
const float CBillboard::MAX_OBJ3DHEIGHT = 500.0f;
const float CBillboard::MAX_OBJ3DWIDTH = 500.0f;

const int CBillboard::MAX_VERTEX = 4;
const int CBillboard::MAX_POLYGON = 2;


CBillboard::CBillboard(int nPriority) :CObject(nPriority), 
			m_fWidth(0),
			m_fHeight(0)
{
	m_pVtxBuffBillboard = nullptr;
	m_pTextureBillboard = nullptr;
}

CBillboard::~CBillboard()
{
}

//==========================================================================================
//����������
//==========================================================================================
void CBillboard::Init()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffBillboard,
		NULL);
	VERTEX_3D* pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth,+m_fHeight,+10.0f );
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth,+m_fHeight,+10.0f );
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth,-m_fHeight,+10.0f );
	pVtx[3].pos = D3DXVECTOR3(+m_fWidth,-m_fHeight,+10.0f );

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
	pVtx[0].tex = D3DXVECTOR2((0.0f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / m_Slice.x), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, (1.0f / m_Slice.y));
	pVtx[3].tex = D3DXVECTOR2((1.0f / m_Slice.x), (1.0f / m_Slice.y));

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffBillboard->Unlock();

	m_Anim = {0,0};
}

//==========================================================================================
//�I������
//==========================================================================================
void CBillboard::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuffBillboard != NULL)
	{
		m_pVtxBuffBillboard->Release();
		m_pVtxBuffBillboard = NULL;
	}
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CBillboard::Update()
{
	if (m_Type == TYPE::TYPE_GAUGE)
	{
		UpdateGauge();
	}
	else
	{
		UpdateNormal();
	}
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CBillboard::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;
	D3DXMATRIX mtxView;

	//�A���t�@�e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	
	//���[���h�}�g���b�N�X
	D3DXMatrixIdentity(&m_mtxWorld);


	//�r���[�}�g���b�N�X�̎擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂ�������
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);//�t�s������߂�
		m_mtxWorld._41 = 0.0f;
		m_mtxWorld._42 = 0.0f;
		m_mtxWorld._43 = 0.0f;

	//�傫���𔽉f(�����ݒ肳�ꂽ�傫��x,z����l1.0�Ƃ����T�C�Y�X�P�[�����O)
	D3DXMatrixScaling(&mtxSize,
		m_scale.y,
		m_scale.x,
		m_scale.z);
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
	pDevice->SetStreamSource(0, m_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureBillboard);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		MAX_POLYGON);

	//Z�A���t�@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//==========================================================================================
//��������
//==========================================================================================
CBillboard* CBillboard::Create(D3DXVECTOR3 pos)
{
	CBillboard* object3D = new CBillboard;
	object3D->m_pos = pos;
	object3D->SetPolygonParam(pos, MAX_OBJ3DHEIGHT, MAX_OBJ3DWIDTH);
	object3D->Init();
	return object3D;
}

//==========================================================================================
//�������̏����ݒ菈��
//==========================================================================================
void CBillboard::SetPolygonParam(D3DXVECTOR3 pos, float fHeight, float fWidth)
{
	m_pos = pos;
	m_fHeight = fHeight;
	m_fWidth = fWidth;
	m_scale = { 1.0f,1.0f,1.0f };
	m_col = {1.0f,1.0f,1.0f,1.0f};
	//�Ίp���̒������Z�o
	m_fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) / 2.0f;
	//�Ίp���̊p�x���Z�o
	m_fAngle = atan2f(m_fWidth, m_fHeight);
	m_Type = CBillboard::TYPE::TYPE_NORMAL;
}

//==========================================================================================
//�������̏����ݒ菈��
//==========================================================================================
void CBillboard::SetPolygonParam(D3DXVECTOR3 pos, float fHeight, float fWidth, D3DXCOLOR col)
{
	m_pos = pos;
	m_fHeight = fHeight;
	m_fWidth = fWidth;
	m_scale = { 1.0f,1.0f,1.0f };
	m_col = col;
	//�Ίp���̒������Z�o
	m_fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) / 2.0f;
	//�Ίp���̊p�x���Z�o
	m_fAngle = atan2f(m_fWidth, m_fHeight);
	m_Type = CBillboard::TYPE::TYPE_NORMAL;

}

//==========================================================================================
//�������̏����ݒ菈�� (�Q�[�W�^�C�v�p�I�[�o�[���[�h)
//==========================================================================================
void CBillboard::SetPolygonParam(D3DXVECTOR3 pos, float fHeight, float fWidth, D3DXCOLOR col,int nMaxValue)
{
	m_pos = pos;
	m_fHeight = fHeight;
	m_fWidth = fWidth;
	m_scale = { 1.0f,1.0f,1.0f };
	m_col = col;
	m_nMaxValue = nMaxValue;
	m_nNowValue = nMaxValue;
	//�Ίp���̒������Z�o
	m_fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) / 2.0f;
	//�Ίp���̊p�x���Z�o
	m_fAngle = atan2f(m_fWidth, m_fHeight);
	m_Type = CBillboard::TYPE::TYPE_GAUGE;
}

//==========================================================================================
//�������̏����ݒ菈��
//==========================================================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTextureBillboard = pTex;
	m_Slice = { 1.0f,1.0f };
}

//==========================================================================================
//�������̏����ݒ菈��(�I�[�o�[���[�h)
//==========================================================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTex,D3DXVECTOR2 Slice)
{
	m_pTextureBillboard = pTex;
	m_Slice = Slice;
}

//==========================================================================================
//�Q�[�W�̒����v�Z
//==========================================================================================
float CBillboard::CalcGaugeValue()
{
	float fval = 0;
	fval = (m_fWidth / m_nMaxValue) * m_nNowValue;
	
	return fval;
}

//==========================================================================================
//�ʏ�^�C�v�̍X�V����
//==========================================================================================
void CBillboard::UpdateNormal()
{
	VERTEX_3D* pVtx;	//���_���̃|�C���^

//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + ((1.0f / m_Slice.x) * m_Anim.x), 0.0f + ((1.0f / m_Slice.y) * m_Anim.y));
	pVtx[1].tex = D3DXVECTOR2((1.0f / m_Slice.x) + ((1.0f / m_Slice.x) * m_Anim.x), 0.0f + ((1.0f / m_Slice.y) * m_Anim.y));
	pVtx[2].tex = D3DXVECTOR2(0.0f + ((1.0f / m_Slice.x) * m_Anim.x), (1.0f / m_Slice.y) + ((1.0f / m_Slice.y) * m_Anim.y));
	pVtx[3].tex = D3DXVECTOR2((1.0f / m_Slice.x) + ((1.0f / m_Slice.x) * m_Anim.x), (1.0f / m_Slice.y) + ((1.0f / m_Slice.y) * m_Anim.y));
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffBillboard->Unlock();
}

//==========================================================================================
//�Q�[�W�^�C�v�̍X�V����
//==========================================================================================
void CBillboard::UpdateGauge()
{
	float fWidth;
	fWidth = CalcGaugeValue();
	float fGauge;
	fGauge = (1.0f / m_nMaxValue) * m_nNowValue;

	VERTEX_3D* pVtx;	//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);
	
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-fWidth, +m_fHeight, +10.0f);
	pVtx[1].pos = D3DXVECTOR3(+fWidth, +m_fHeight, +10.0f);
	pVtx[2].pos = D3DXVECTOR3(-fWidth, -m_fHeight, +10.0f);
	pVtx[3].pos = D3DXVECTOR3(+fWidth, -m_fHeight, +10.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fGauge, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f - fGauge, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fGauge, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f - fGauge, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffBillboard->Unlock();
}