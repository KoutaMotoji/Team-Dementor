//=====================================================================================================================
//
//�̗͂̏���[health_fill.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _HEALTH_FILL_H_
#define _HEALTH_FILL_H_

#include "fill.h"

//�̗͕���
class HealthFill : public Fill   //(�e)�h�蕔��
{
public:
	//�R���X�g���N�^
	HealthFill(Gauge* pGauge, D3DXCOLOR color) : Fill(pGauge, color)
	{
	}

	//�f�X�g���N�^
	~HealthFill()
	{
	}

	

private:
};

#endif // !_HEALTH_FILL_H_