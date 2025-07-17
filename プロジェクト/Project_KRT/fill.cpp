//=====================================================================================================================
//
//�h�蕔���̏���[fill.cpp]
// Author MurataShinnosuke
//
//=====================================================================================================================
#include "fill.h"
#include "manager.h"
#include "gauge.h"

//=====================================================================================================================
//����������
//=====================================================================================================================
void Fill::Init()
{
	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�𐶐�����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&this->m_pVtxBuffer,
		NULL);
}

//=====================================================================================================================
//�I������
//=====================================================================================================================
void Fill::Uninit()
{
	//���_�o�b�t�@���m�F����
	if (this->m_pVtxBuffer != nullptr)
	{//���_�o�b�t�@������ꍇ
		//���_�o�b�t�@��j������
		this->m_pVtxBuffer->Release();
		this->m_pVtxBuffer = nullptr;
	}
}

//=====================================================================================================================
//�X�V����
//=====================================================================================================================
void Fill::Update()
{
	//���_���W�����b�N���āA���_���ւ̃|�C���^���擾����
	VERTEX_2D* pVtx;   //���_���W
	this->m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W��ݒ肷��
	D3DXVECTOR3 v3Pos = this->m_pGauge->GetPos();   //�ʒu�̎擾
	D3DXVECTOR2 v2Size = this->m_pGauge->GetSize();   //�T�C�Y�̎擾
	pVtx[0].pos = { v3Pos.x - (v2Size.x * 0.5f), v3Pos.y - (v2Size.y * 0.5f), 0.0f };
	pVtx[1].pos = { v3Pos.x + (v2Size.x * 0.5f * this->m_fRatio), v3Pos.y - (v2Size.y * 0.5f), 0.0f };
	pVtx[2].pos = { v3Pos.x - (v2Size.x * 0.5f), v3Pos.y + (v2Size.y * 0.5f), 0.0f };
	pVtx[3].pos = { v3Pos.x + (v2Size.x * 0.5f * this->m_fRatio), v3Pos.y + (v2Size.y * 0.5f), 0.0f };

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[��ݒ肷��
	pVtx[0].col = this->m_color;
	pVtx[1].col = this->m_color;
	pVtx[2].col = this->m_color;
	pVtx[3].col = this->m_color;

	//�e�N�X�`�����W��ݒ肷��
	pVtx[0].tex = { 0.0f, 0.0f };
	pVtx[1].tex = { 1.0f, 0.0f };
	pVtx[2].tex = { 0.0f, 1.0f };
	pVtx[3].tex = { 1.0f, 1.0f };

	//���_�o�b�t�@���A�����b�N����
	this->m_pVtxBuffer->Unlock();
}

//=====================================================================================================================
//�`�揈��
//=====================================================================================================================
void Fill::Draw()
{
	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ肷��
	pDevice->SetStreamSource(0, this->m_pVtxBuffer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g��ݒ肷��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`����ݒ肷��
	pDevice->SetTexture(0, nullptr);

	//�|���S����`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}