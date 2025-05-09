//===============================================================================
//
//  C++�g����3D(modelparts.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "modelparts.h"
#include "manager.h"


//==========================================================================================
//�R���X�g���N�^
//==========================================================================================
CModelParts::CModelParts()
{

}

//==========================================================================================
//�f�X�g���N�^
//==========================================================================================
CModelParts::~CModelParts()
{

}

//==========================================================================================
//����������
//==========================================================================================
HRESULT CModelParts::Init()
{
	m_pParent = nullptr;

	for (int i = 0; i < MAX_MODEL_TEX; i++)
	{
		m_pTextureObjectX[i] = nullptr;
	}
	return S_OK;
}

//==========================================================================================
//�I������
//==========================================================================================
void CModelParts::Uninit()
{
	//���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	for (int i = 0; i < (int)m_dwNumMat; i++)
	{
		if (m_pTextureObjectX[i] != nullptr)
		{
			m_pTextureObjectX[i]->Release();
			m_pTextureObjectX[i] = nullptr;
		}
	}
}


//==========================================================================================
//�`�揈��
//==========================================================================================
void CModelParts::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL* pMat;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�傫���𔽉f
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
	//�e�̍s����擾����
	D3DXMATRIX mtxParent;
	if (m_pParent != nullptr)
	{
		//�e�̃��[���h�ϊ��s����擾
		mtxParent = m_pParent->GetWorldMatrix();
	}
	else
	{
		//�ŐV�̃��[���h�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	//���[���h�s���e�̍s��Ɋ|����
	D3DXMatrixMultiply(&m_mtxWorld,
						&m_mtxWorld,
						&mtxParent);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,
		&m_mtxWorld);
	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//pMat[nCntMat].MatD3D.Diffuse.a = 50.0f;
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTextureObjectX[nCntMat]);
		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==========================================================================================
//��������
//==========================================================================================
CModelParts* CModelParts::Create(D3DXVECTOR3 pos, const char* apFileName)
{
	CModelParts* ModelParts = new CModelParts;
	ModelParts->m_pos = pos;
	ModelParts->m_rot = { 0.0f,0.0f,0.0f };
	ModelParts->m_size = { 1.0f,1.0f,1.0f };
	ModelParts->BindModel(apFileName);
	ModelParts->Init();
	ModelParts->m_nIdx = -1;
	return ModelParts;
}

//==========================================================================================
//���f���̐e�ݒ�
//==========================================================================================
void CModelParts::SetParent(CModelParts* pParent)
{
	if (!(pParent->m_nIdx == -1))
	{
		m_pParent = pParent;
	}
}

//==========================================================================================
//���f����������
//==========================================================================================
void CModelParts::BindModel(const char* apFileName)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(apFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTextureObjectX[nCntMat]);
		}
	}
	SetModelSize();
}


//==========================================================================================
//�T�C�Y���擾
//==========================================================================================
void CModelParts::SetModelSize()
{
	int nNumVtx;
	DWORD sizeFVF;
	BYTE* pVtxBuff;

	//���_���̎擾
	nNumVtx = m_pMesh->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int i = 0; i < nNumVtx; i++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (vtx.x < m_vtxMinModel.x)
		{
			m_vtxMinModel.x = vtx.x;
		}
		if (vtx.y < m_vtxMinModel.y)
		{
			m_vtxMinModel.y = vtx.y;
		}
		if (vtx.z < m_vtxMinModel.z)
		{
			m_vtxMinModel.z = vtx.z;
		}
		if (vtx.x > m_vtxMaxModel.x)
		{
			m_vtxMaxModel.x = vtx.x;
		}
		if (vtx.y > m_vtxMaxModel.y)
		{
			m_vtxMaxModel.y = vtx.y;
		}
		if (vtx.z > m_vtxMaxModel.z)
		{
			m_vtxMaxModel.z = vtx.z;
		}
		//���_�t�H�[�}�b�g�̃T�C�Y���|�C������i�߂�
		pVtxBuff += sizeFVF;
	}
	//���a���Z�o
	m_radius = (m_vtxMaxModel - m_vtxMinModel);
}