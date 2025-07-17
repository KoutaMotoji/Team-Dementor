//=====================================================================================================================
//
//ダメージの処理[damage_fill.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _DAMAGE_FILL_H_
#define _DAMAGE_FILL_H_

#include "fill.h"

//ダメージ部分
class DamageFill : public Fill   //(親)塗り部分
{
public:
	//コンストラクタ
	DamageFill(Gauge* pGauge, D3DXCOLOR color) : Fill(pGauge, color)
	{
	}

	//デストラクタ
	~DamageFill()
	{
	}

private:
};

#endif // !_DAMAGE_FILL_H_