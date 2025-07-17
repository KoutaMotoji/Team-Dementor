//=====================================================================================================================
//
//�ϋv�̓Q�[�W�̏���[durability_gauge.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#include "durability_gauge.h"
#include "manager.h"

//�ÓI�����o�ϐ�
const D3DXCOLOR DurabilityGauge::COLOR_DURABILITY_FILL = { 0.75f, 0.75f, 0.75f, 1.0f };   //�ϋv�͓h�蕔���̐F
const D3DXVECTOR2 DurabilityGauge::ADD_SIZE_BACKGROUND = { 7.0f, 15.0f };   //�w�i�̃T�C�Y�̉��Z�l

//=====================================================================================================================
//����������
//=====================================================================================================================
void DurabilityGauge::Init()
{
	//�Q�[�W�̔w�i�̃C���X�^���X�𐶐�����
	this->m_pGaugeBackground = new GaugeBackground(this);
	this->m_pGaugeBackground->Init();   //����������
	this->m_pGaugeBackground->SetAddSize(DurabilityGauge::ADD_SIZE_BACKGROUND);   //�T�C�Y�̉��Z�l��ݒ肷��

	//�ϋv�͂̓h�蕔���̃C���X�^���X�𐶐�����
	this->m_pDurabilityFill = new DurabilityFill(this, DurabilityGauge::COLOR_DURABILITY_FILL);
	this->m_pDurabilityFill->Init();   //����������

	//�w�i�Ƀe�N�X�`����ݒ肷��
	LPDIRECT3DTEXTURE9 pTexture = nullptr;   //�ݒ肷��e�N�X�`��
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();   //�f�o�C�X���擾
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\durability_gauge_bg_00.png", &pTexture);   //�e�N�X�`����ǂݍ���
	this->m_pGaugeBackground->SetTexture(pTexture);
}

//=====================================================================================================================
//�I������
//=====================================================================================================================
void DurabilityGauge::Uninit()
{
	//�ϋv�͂̓h�蕔�����m�F����
	if (this->m_pDurabilityFill != nullptr)
	{//�ϋv�͂̓h�蕔������������Ă���ꍇ
		//�ϋv�͂̓h�蕔����j������
		this->m_pDurabilityFill->Uninit();   //�I������
		delete this->m_pDurabilityFill;
		this->m_pDurabilityFill = nullptr;
	}

	//�w�i���m�F����
	if (this->m_pGaugeBackground != nullptr)
	{//�w�i����������Ă���ꍇ
		//�w�i��j������
		this->m_pGaugeBackground->Uninit();   //�I������
		delete this->m_pGaugeBackground;
		this->m_pGaugeBackground = nullptr;
	}
}

//=====================================================================================================================
//�X�V����
//=====================================================================================================================
void DurabilityGauge::Update()
{
	//�h�蕔���̍X�V�������s��
	this->m_pDurabilityFill->Update();   //�ϋv��
	this->m_pGaugeBackground->Update();   //�w�i
}

//=====================================================================================================================
//�`�揈��
//=====================================================================================================================
void DurabilityGauge::Draw()
{
	//�h�蕔���̕`�揈�����s��
	this->m_pDurabilityFill->Draw();   //�ϋv��
	this->m_pGaugeBackground->Draw();   //�w�i
}

//=====================================================================================================================
//�q�b�g�|�C���g�̓K�p����
//=====================================================================================================================
void DurabilityGauge::ApplyDurability(int nDurability)
{
	//�ϋv�͂̓h�蕔���Ɏc��ϋv�͂̊�����ݒ肷��
	this->m_pDurabilityFill->SetRatio((float)nDurability / this->m_nMaxDurability);
}

//=====================================================================================================================
//��������
//=====================================================================================================================
DurabilityGauge* DurabilityGauge::Create(int nDurability, D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size)
{
	//�ϋv�̓Q�[�W�̃C���X�^���X�𐶐�����
	DurabilityGauge* pDurabilityGauge = new DurabilityGauge(nDurability, v3Pos, v2Size);
	pDurabilityGauge->Init();   //����������

	//�ϋv�̓Q�[�W�̃C���X�^���X��Ԃ�
	return pDurabilityGauge;
}