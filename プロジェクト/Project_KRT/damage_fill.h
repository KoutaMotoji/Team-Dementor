//=====================================================================================================================
//
//�_���[�W�̏���[damage_fill.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _DAMAGE_FILL_H_
#define _DAMAGE_FILL_H_

#include "fill.h"

//�_���[�W����
class DamageFill : public Fill   //(�e)�h�蕔��
{
public:
	//�R���X�g���N�^
	DamageFill(Gauge* pGauge, D3DXCOLOR color) : Fill(pGauge, color)
	{
	}

	//�f�X�g���N�^
	~DamageFill()
	{
	}

private:
};

#endif // !_DAMAGE_FILL_H_