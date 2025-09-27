//===============================================================================
//
//  ���b�V���V�����_�[�̏���(mesh_cylinder.cpp)
//								����F���n�O��
//
//===============================================================================
#include "mesh_cylinder.h"

#include "manager.h"

namespace
{
	float MAX_WIDTH = 6000.0f;
	float MAX_HEIGHT = 8000.0f;

	int MAX_CORNER = 8;

	int MAX_VTX = MAX_CORNER * 2;
	int MAX_INDEX = MAX_VTX + 2;
}



CMeshCylinder::CMeshCylinder(int nPriority) : CObject(nPriority),
m_pos({ 0.0f,0.0f,0.0f }),
m_rot({ 0.0f,0.0f,0.0f })
{

}


CMeshCylinder::~CMeshCylinder()
{

}

//==========================================================================================
//����������
//==========================================================================================
void CMeshCylinder::Init()
{
	//�e�|�C���^�̏�����
	m_apTexMeshCylinder = nullptr;
	m_pVtxBuffMeshCylinder = nullptr;
	m_pIdxBuffMeshCylinder = nullptr;

	CObject::SetType(TYPE_BG);

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();;
	SetTexture(pDevice, "data\\TEXTURE\\sky_bg001.png");
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffMeshCylinder,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuffMeshCylinder,
		NULL);

	VERTEX_3D* pVtx;	//���_���̃|�C���^

	m_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < MAX_CORNER; ++j) {
			float radian = (((float)j) / (float)MAX_CORNER);
			int nNum = ((i * MAX_CORNER) + j);
			pVtx[nNum].pos.x = m_pos.x + (cosf(radian * 2 * D3DX_PI) * MAX_WIDTH);
			pVtx[nNum].pos.z = m_pos.z + (sinf(radian * 2 * D3DX_PI) * MAX_WIDTH);
			pVtx[nNum].pos.y = m_pos.y + i * -MAX_HEIGHT;
		}
	}
	for (int i = 0; i < MAX_VTX; ++i)
	{
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[i].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < MAX_CORNER; ++j) {
			int nNum = ((i * MAX_CORNER) + j);

			pVtx[nNum].tex = {
				(float)((1.0f / (MAX_CORNER)) * j * 2),
				(float)(1.0f * i)
			};
		}
	}
	m_pVtxBuffMeshCylinder->Unlock();

	int nLoop = 0;

	WORD* pIdx;	//�C���f�b�N�X���̃|�C���^
	//�C���f�b�N�X�o�b�t�@�̃��b�N
	m_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	for (int X = 0; X < MAX_CORNER; ++X)
	{
		pIdx[nLoop] = (X + MAX_CORNER);
		++nLoop;

		pIdx[nLoop] = X;
		++nLoop;
	}

	pIdx[nLoop] = (MAX_CORNER)+1;

	++nLoop;

	pIdx[nLoop] = 1;

	m_pIdxBuffMeshCylinder->Unlock();
}


//==========================================================================================
//�I������
//==========================================================================================
void CMeshCylinder::Uninit()
{
	if (m_apTexMeshCylinder != nullptr)
	{
		m_apTexMeshCylinder->Release();
		m_apTexMeshCylinder = nullptr;
	}
	if (m_pIdxBuffMeshCylinder != nullptr)
	{
		m_pIdxBuffMeshCylinder->Release();
		m_pIdxBuffMeshCylinder = nullptr;
	}
	if (m_pVtxBuffMeshCylinder != nullptr)
	{
		m_pVtxBuffMeshCylinder->Release();
		m_pVtxBuffMeshCylinder = nullptr;
	}
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CMeshCylinder::Update()
{

}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CMeshCylinder::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���[���h�}�g���b�N�X
	D3DXMatrixIdentity(&m_mtx);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtx,
		&m_mtx,
		&mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);
	D3DXMatrixMultiply(&m_mtx,
		&m_mtx,
		&mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,
		&m_mtx);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuffMeshCylinder);
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_apTexMeshCylinder);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//�J�����O���ʂ�


	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		MAX_VTX,
		0,
		MAX_VTX);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//�J�����O�߂�
}


//==========================================================================================
//��������
//==========================================================================================
CMeshCylinder* CMeshCylinder::Create(D3DXVECTOR3 pos)
{
	CMeshCylinder* field = new CMeshCylinder;
	field->Init();
	field->m_pos = pos;
	field->m_pos.y += MAX_HEIGHT * 0.6;
	return field;
}

void CMeshCylinder::SetTexture(const LPDIRECT3DDEVICE9 pDevice, std::string filename)
{
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		filename.c_str(),
		&m_apTexMeshCylinder);
}