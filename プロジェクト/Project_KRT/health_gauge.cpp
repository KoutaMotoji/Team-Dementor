//=====================================================================================================================
//
//�̗̓Q�[�W�̏���[health_gauge.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#include "health_gauge.h"
#include "manager.h"

//�ÓI�����o�ϐ�
const float HealthGauge::SUB_DAMAGE_RATIO = 0.001f;
const D3DXCOLOR HealthGauge::COLOR_HEALTH_FILL = { 0.25f, 1.0f, 0.25f, 1.0f };   //�̗͓h�蕔���̐F
const D3DXCOLOR HealthGauge::COLOR_DAMAGE_FILL = { 1.0f, 0.25f, 0.25f, 1.0f };   //�_���[�W�h�蕔���̐F
const D3DXVECTOR2 HealthGauge::ADD_SIZE_BACKGROUND = { 20.0f, 15.0f };   //�w�i�̃T�C�Y�̉��Z�l

//=====================================================================================================================
//����������
//=====================================================================================================================
void HealthGauge::Init()
{
	//�Q�[�W�̔w�i�̃C���X�^���X�𐶐�����
	this->m_pGaugeBackground = new GaugeBackground(this);
	this->m_pGaugeBackground->Init();   //����������
	this->m_pGaugeBackground->SetAddSize(HealthGauge::ADD_SIZE_BACKGROUND);   //�T�C�Y�̉��Z�l��ݒ肷��

	//�_���[�W�����̃C���X�^���X�𐶐�����
	this->m_pDamageFill = new DamageFill(this, HealthGauge::COLOR_DAMAGE_FILL);
	this->m_pDamageFill->Init();   //����������

	//�̗͕����̃C���X�^���X�𐶐�����
	this->m_pHealthFill = new HealthFill(this, HealthGauge::COLOR_HEALTH_FILL);
	this->m_pHealthFill->Init();   //����������

	//�w�i�Ƀe�N�X�`����ݒ肷��
	LPDIRECT3DTEXTURE9 pTexture = nullptr;   //�ݒ肷��e�N�X�`��
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();   //�f�o�C�X���擾
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\health_gauge_bg_00.png", &pTexture);   //�e�N�X�`����ǂݍ���
	this->m_pGaugeBackground->SetTexture(pTexture);
}

//=====================================================================================================================
//�I������
//=====================================================================================================================
void HealthGauge::Uninit()
{
	//�̗͂��m�F����
	if (this->m_pHealthFill != nullptr)
	{//�̗͂���������Ă���ꍇ
		//�̗͂�j������
		this->m_pHealthFill->Uninit();   //�I������
		delete this->m_pHealthFill;
		this->m_pHealthFill = nullptr;
	}

	//�_���[�W���m�F����
	if (this->m_pDamageFill != nullptr)
	{//�_���[�W����������Ă���ꍇ
		//�_���[�W��j������
		this->m_pDamageFill->Uninit();   //�I������
		delete this->m_pDamageFill;
		this->m_pDamageFill = nullptr;
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
void HealthGauge::Update()
{
	//K�L�[�̓��͂��m�F����
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_K))
	{//K�L�[�������ꂽ��
		//HP��K�p����
		HealthGauge::ApplyHp(50);
	}

	//�̗͂̓h�蕔���̊����ƃ_���[�W�̓h�蕔���̊������m�F����
	float fRatioHealth = this->m_pHealthFill->GetRatio();   //�̗͂̓h�蕔���̊���
	float fRatioDamage = this->m_pDamageFill->GetRatio();   //�_���[�W�̓h�蕔���̊���
	if (fRatioHealth < fRatioDamage)
	{//�̗͂̊����̕����_���[�W�̊�����菬�����ꍇ
		//�_���[�W�̊��������炷
		this->m_pDamageFill->SetRatio(this->m_pDamageFill->GetRatio() - HealthGauge::SUB_DAMAGE_RATIO);
	}
	else if (fRatioHealth > fRatioDamage)
	{//�̗͂̊����̕����_���[�W�̊������傫���ꍇ
		//�_���[�W�̊�����̗͂̊����ɍ��킹��
		this->m_pDamageFill->SetRatio(fRatioHealth);
	}

	//�X�V�������s��
	this->m_pHealthFill->Update();   //�̗�
	this->m_pDamageFill->Update();   //�_���[�W
	this->m_pGaugeBackground->Update();   //�w�i
}

//=====================================================================================================================
//�`�揈��
//=====================================================================================================================
void HealthGauge::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�X�e���V���}�X�N�̐ݒ莞�ɖ���������Z�o�b�t�@�����Ƃɂ��ǂ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//�`�揈�����s��
	this->m_pHealthFill->Draw();   //�̗�
	this->m_pDamageFill->Draw();   //�_���[�W
	this->m_pGaugeBackground->Draw();   //�w�i
}

//=====================================================================================================================
//�q�b�g�|�C���g�̓K�p����
//=====================================================================================================================
void HealthGauge::ApplyHp(int nHp)
{
	//�̗͂Ɏc��HP�̊�����ݒ肷��
	this->m_pHealthFill->SetRatio((float)nHp / this->m_nMaxHp);
}

//=====================================================================================================================
//��������
//=====================================================================================================================
HealthGauge* HealthGauge::Create(int nHp, D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size)
{
	//�̗̓Q�[�W�̃C���X�^���X�𐶐�����
	HealthGauge* pHealthGauge = new HealthGauge(nHp, v3Pos, v2Size);
	pHealthGauge->Init();   //����������

	//�̗̓Q�[�W�̃C���X�^���X��Ԃ�
	return pHealthGauge;
}