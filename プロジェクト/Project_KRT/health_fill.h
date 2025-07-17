//=====================================================================================================================
//
//体力の処理[health_fill.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _HEALTH_FILL_H_
#define _HEALTH_FILL_H_

#include "fill.h"

//体力部分
class HealthFill : public Fill   //(親)塗り部分
{
public:
	//コンストラクタ
	HealthFill(Gauge* pGauge, D3DXCOLOR color) : Fill(pGauge, color)
	{
	}

	//デストラクタ
	~HealthFill()
	{
	}

	

private:
};

#endif // !_HEALTH_FILL_H_