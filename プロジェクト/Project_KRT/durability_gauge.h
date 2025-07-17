//=====================================================================================================================
//
//�ϋv�̓Q�[�W�̏���[durability_gauge.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _DURABILITY_GAUGE_H_
#define _DURABILITY_GAUGE_H_

#include "gauge.h"
#include "durability_fill.h"
#include "gauge_background.h"

//�ϋv�̓Q�[�W
class DurabilityGauge : public Gauge   //(�e)�Q�[�W
{
public:
	static const D3DXCOLOR COLOR_DURABILITY_FILL;   //�ϋv�͓h�蕔���̐F
	static const D3DXVECTOR2 ADD_SIZE_BACKGROUND;   //�w�i�̃T�C�Y�̉��Z�l

	//�R���X�g���N�^
	DurabilityGauge(int nDurability, D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size) : Gauge(v3Pos, v2Size)
	{
		//�����o�ϐ�������������
		this->m_pDurabilityFill = nullptr;   //�ϋv�͂̓h�蕔��
		this->m_pGaugeBackground = nullptr;   //�w�i
		this->m_nMaxDurability = nDurability;   //�ϋv�͂̍ő�l
	}

	//�f�X�g���N�^
	~DurabilityGauge()
	{
	}

	void Init() override;   //������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	void Draw() override;   //�`�揈��
	void ApplyDurability(int nDurability);   //�ϋv�͂̓K�p����

	static DurabilityGauge* Create(int nDurability, D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size);   //��������

private:
	DurabilityFill* m_pDurabilityFill;   //�ϋv�͂̓h�蕔��
	GaugeBackground* m_pGaugeBackground;   //�w�i����
	int m_nMaxDurability;   //�ϋv�͂̍ő�l
};

#endif // !_DURABILITY_GAUGE_H_
