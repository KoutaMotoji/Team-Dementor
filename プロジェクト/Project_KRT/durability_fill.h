//=====================================================================================================================
//
//�ϋv�͓h�蕔���̏���[durability.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _DURABILITY_FILL_H_
#define _DURABILITY_FILL_H_

#include "fill.h"

//�ϋv�͓h�蕔������
class DurabilityFill : public Fill   //(�e)�h�蕔��
{
public:
	//�R���X�g���N�^
	DurabilityFill(Gauge* pGauge, D3DXCOLOR color) : Fill(pGauge, color)
	{
	}

	//�f�X�g���N�^
	~DurabilityFill()
	{
	}

private:
};

#endif // !_DURABILITY_FILL_H_