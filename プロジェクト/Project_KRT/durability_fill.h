//=====================================================================================================================
//
//耐久力塗り部分の処理[durability.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _DURABILITY_FILL_H_
#define _DURABILITY_FILL_H_

#include "fill.h"

//耐久力塗り部分部分
class DurabilityFill : public Fill   //(親)塗り部分
{
public:
	//コンストラクタ
	DurabilityFill(Gauge* pGauge, D3DXCOLOR color) : Fill(pGauge, color)
	{
	}

	//デストラクタ
	~DurabilityFill()
	{
	}

private:
};

#endif // !_DURABILITY_FILL_H_