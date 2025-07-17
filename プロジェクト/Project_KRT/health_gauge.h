//=====================================================================================================================
//
//�̗̓Q�[�W�̏���[health_gauge.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _HEALTH_GAUGE_H_
#define _HEALTH_GAUGE_H_

#include "gauge.h"
#include "gauge_background.h"
#include "health_fill.h"
#include "damage_fill.h"

//�̗̓Q�[�W
class HealthGauge : public Gauge   //(�e)�Q�[�W
{
public:
	static const float SUB_DAMAGE_RATIO;   //�_���[�W�����̌��Z��
	static const D3DXCOLOR COLOR_HEALTH_FILL;   //�̗͓h�蕔���̐F
	static const D3DXCOLOR COLOR_DAMAGE_FILL;   //�_���[�W�h�蕔���̐F
	static const D3DXVECTOR2 ADD_SIZE_BACKGROUND;   //�w�i�̃T�C�Y�̉��Z�l

	//�R���X�g���N�^
	HealthGauge(int nHp, D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size) : Gauge(v3Pos, v2Size)
	{
		//�����o�ϐ�������������
		this->m_pHealthFill = nullptr;   //�̗�
		this->m_pDamageFill = nullptr;   //�_���[�W
		this->m_pGaugeBackground = nullptr;   //�w�i
		this->m_nMaxHp = nHp;   //�q�b�g�|�C���g�̍ő�l
	}

	//�f�X�g���N�^
	~HealthGauge()
	{
	}

	void Init() override;   //������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	void Draw() override;   //�`�揈��
	void ApplyHp(int nHp);   //�q�b�g�|�C���g�̓K�p����

	static HealthGauge* Create(int nHp, D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size);   //��������

private:
	HealthFill* m_pHealthFill;   //�̗͕���
	DamageFill* m_pDamageFill;   //�_���[�W����
	GaugeBackground* m_pGaugeBackground;   //�w�i����
	int m_nMaxHp;   //�q�b�g�|�C���g�̍ő�l
};

#endif // !_HEALTH_GAUGE_H_
