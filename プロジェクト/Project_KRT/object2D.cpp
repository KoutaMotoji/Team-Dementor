//===============================================================================
//
//  2D�I�u�W�F�N�g���N���X(object2D.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "object2D.h"
#include "manager.h"

const int CObject2D::MAX_VERTEX = 4;
const int CObject2D::MAX_POLYGON = 2;


CObject2D::CObject2D(int nPriority):CObject(nPriority), m_fWidth(0), m_fHeight(0),m_AnimU(0),m_AnimV(0),m_fZoom(1),m_GaugeAnim(0.0f,0.0f)
{
	m_pVtxBuffObject2D = nullptr;
	m_pTextureObject2D = nullptr;
}

CObject2D::~CObject2D()
{
}

//==========================================================================================
//����������
//==========================================================================================
void CObject2D::Init()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffObject2D,
		NULL);
	
	VERTEX_2D* pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuffObject2D->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	
		//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * (m_fLength * m_fZoom);
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * (m_fLength * m_fZoom);
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * (m_fLength * m_fZoom);
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * (m_fLength * m_fZoom);
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((0.0f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / m_TexSliceU), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, (1.0f / m_TexSliceV));
	pVtx[3].tex = D3DXVECTOR2((1.0f / m_TexSliceU), (1.0f / m_TexSliceV));

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffObject2D->Unlock();
}

//==========================================================================================
//�I������
//==========================================================================================
void CObject2D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuffObject2D != NULL)
	{
		m_pVtxBuffObject2D->Release();
		m_pVtxBuffObject2D = NULL;
	}
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CObject2D::Update()
{
	if (m_type == TYPE_NORMAL)
	{
		UpdateNormal();
	}
	else if (m_type == TYPE_GAUGE)
	{
		if (m_bGaugeReverse)
		{
			UpdateGaugeRight();
		}
		else
		{
			UpdateGaugeLeft();
		}
	}
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffObject2D, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureObject2D);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		MAX_POLYGON);
}


//==========================================================================================
//��������
//==========================================================================================
CObject2D* CObject2D::Create(D3DXVECTOR3 pos)
{
	CObject2D* object2D = new CObject2D;
	object2D->m_pos = pos;
	return object2D;
}

//==========================================================================================
//�������̏����ݒ菈��
//==========================================================================================
void CObject2D::SetPolygonParam(D3DXVECTOR3 pos, float fHeight, float fWidth)
{
	m_type = TYPE_NORMAL;
	m_pos = pos;
	m_fHeight = fHeight;
	m_fWidth = fWidth;
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//�Ίp���̒������Z�o
	m_fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) / 2.0f;
	//�Ίp���̊p�x���Z�o
	m_fAngle = atan2f(m_fWidth, m_fHeight);
}

//==========================================================================================
//�������̏����ݒ菈��(�F�ύX�ǉ�)
//==========================================================================================
void CObject2D::SetPolygonParam(D3DXVECTOR3 pos, float fHeight, float fWidth, D3DXCOLOR col)
{
	m_type = TYPE_NORMAL;
	m_pos = pos;
	m_fHeight = fHeight;
	m_fWidth = fWidth;
	m_col = col;
	//�Ίp���̒������Z�o
	m_fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) / 2.0f;
	//�Ίp���̊p�x���Z�o
	m_fAngle = atan2f(m_fWidth, m_fHeight);
}

//==========================================================================================
//�������̏����ݒ菈��(�Q�[�W�p�ݒ�ǉ�)
//==========================================================================================
void CObject2D::SetPolygonParam(D3DXVECTOR3 pos, float fHeight, float fWidth, int nMaxGauge,bool Reverse)
{
	m_type = TYPE_GAUGE;
	m_pos = pos;
	m_fHeight = fHeight;
	m_fWidth = fWidth;
	m_nMaxGauge = nMaxGauge;
	m_nCharge = nMaxGauge;
	m_bGaugeReverse = Reverse;
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	float fSetWidth = CalcWidth();
	//�Ίp���̒������Z�o
	m_fLength = sqrtf(fSetWidth * fSetWidth + m_fHeight * m_fHeight) / 2.0f;
	//�Ίp���̊p�x���Z�o
	m_fAngle = atan2f(fSetWidth, m_fHeight);
}

//==========================================================================================
//�e�N�X�`���̐ݒ�(�e�N�X�`���̃|�C���^�@/ �c������ / ��������)
//==========================================================================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex, int AnimU, int AnimV)
{
	m_pTextureObject2D = pTex;
	
	m_TexSliceU = AnimU;
	m_TexSliceV = AnimV;
}

//==========================================================================================
//�Q�[�W�����v�Z
//==========================================================================================
float CObject2D::CalcWidth()
{
	float fVar;

	fVar = (m_fWidth / m_nMaxGauge) * m_nCharge;

	return fVar;
}

//==========================================================================================
//�X�V����(���ʂ�2D�I�u�W�F�N�g)
//==========================================================================================
void CObject2D::UpdateNormal()
{
	VERTEX_2D* pVtx;	//���_���̃|�C���^

		//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuffObject2D->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�

		//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * (m_fLength * m_fZoom);
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * (m_fLength * m_fZoom);
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * (m_fLength * m_fZoom);
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * (m_fLength * m_fZoom);
	pVtx[3].pos.z = 0.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + ((1.0f / m_TexSliceU) * m_AnimU), 0.0f + ((1.0f / m_TexSliceV) * m_AnimV));
	pVtx[1].tex = D3DXVECTOR2((1.0f / m_TexSliceU) + ((1.0f / m_TexSliceU) * m_AnimU), 0.0f + ((1.0f / m_TexSliceV) * m_AnimV));
	pVtx[2].tex = D3DXVECTOR2(0.0f + ((1.0f / m_TexSliceU) * m_AnimU), (1.0f / m_TexSliceV) + ((1.0f / m_TexSliceV) * m_AnimV));
	pVtx[3].tex = D3DXVECTOR2((1.0f / m_TexSliceU) + ((1.0f / m_TexSliceU) * m_AnimU), (1.0f / m_TexSliceV) + ((1.0f / m_TexSliceV) * m_AnimV));
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffObject2D->Unlock();
}

//==========================================================================================
//�X�V����(�Q�[�W�^�C�v�̃I�u�W�F�N�g�����ɏk���^�C�v)
//==========================================================================================
void CObject2D::UpdateGaugeLeft()
{
	float fWidth = CalcWidth();
	//�Ίp���̒������Z�o
	m_fLength = sqrtf(fWidth * fWidth + m_fHeight * m_fHeight) / 2.0f;
	//�Ίp���̊p�x���Z�o
	m_fAngle = atan2f(fWidth, m_fHeight);

	//�e�N�X�`���̒[���Z�o
	float fGaugeTex = ((1.0f / m_nMaxGauge) * m_nCharge);
	float SetPos = m_pos.x + (fWidth * 0.5f) - m_fWidth * 0.5f;

	VERTEX_2D* pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuffObject2D->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�

	//���_���W�̐ݒ�
	pVtx[0].pos.x = SetPos + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = SetPos + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = SetPos + sinf(m_rot.z - m_fAngle) * (m_fLength * m_fZoom);
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * (m_fLength * m_fZoom);
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = SetPos + sinf(m_rot.z + m_fAngle) * (m_fLength * m_fZoom);
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * (m_fLength * m_fZoom);
	pVtx[3].pos.z = 0.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + m_GaugeAnim.x, 0.0f + m_GaugeAnim.y);
	pVtx[1].tex = D3DXVECTOR2(fGaugeTex + m_GaugeAnim.x, 0.0f + m_GaugeAnim.y);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_GaugeAnim.x, 1.0f + m_GaugeAnim.y);
	pVtx[3].tex = D3DXVECTOR2(fGaugeTex + m_GaugeAnim.x, 1.0f + m_GaugeAnim.y);
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffObject2D->Unlock();
}

//==========================================================================================
//�X�V����(�Q�[�W�^�C�v�̃I�u�W�F�N�g�E���ɏk���^�C�v)
//==========================================================================================
void CObject2D::UpdateGaugeRight()
{
	float fWidth = CalcWidth();
	//�Ίp���̒������Z�o
	m_fLength = sqrtf(fWidth * fWidth + m_fHeight * m_fHeight) / 2.0f;
	//�Ίp���̊p�x���Z�o
	m_fAngle = atan2f(fWidth, m_fHeight);

	//�e�N�X�`���̒[���Z�o
	float fGaugeTex = ((1.0f / m_nMaxGauge) * m_nCharge);
	float SetPos = m_pos.x - (fWidth * 0.5f) + m_fWidth * 0.5f;

	VERTEX_2D* pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuffObject2D->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�

	//���_���W�̐ݒ�
	pVtx[0].pos.x = SetPos + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = SetPos + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * (m_fLength * m_fZoom);
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = SetPos + sinf(m_rot.z - m_fAngle) * (m_fLength * m_fZoom);
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * (m_fLength * m_fZoom);
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = SetPos + sinf(m_rot.z + m_fAngle) * (m_fLength * m_fZoom);
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * (m_fLength * m_fZoom);
	pVtx[3].pos.z = 0.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(( 1.0f - fGaugeTex) + m_GaugeAnim.x, 0.0f + m_GaugeAnim.y);
	pVtx[1].tex = D3DXVECTOR2(1.0f + m_GaugeAnim.x, 0.0f + m_GaugeAnim.y);
	pVtx[2].tex = D3DXVECTOR2((1.0f - fGaugeTex) + m_GaugeAnim.x, 1.0f + m_GaugeAnim.y);
	pVtx[3].tex = D3DXVECTOR2(1.0f + m_GaugeAnim.x, 1.0f + m_GaugeAnim.y);
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffObject2D->Unlock();
}