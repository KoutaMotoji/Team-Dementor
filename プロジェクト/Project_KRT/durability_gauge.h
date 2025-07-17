//=====================================================================================================================
//
//‘Ï‹v—ÍƒQ[ƒW‚Ìˆ—[durability_gauge.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _DURABILITY_GAUGE_H_
#define _DURABILITY_GAUGE_H_

#include "gauge.h"
#include "durability_fill.h"
#include "gauge_background.h"

//‘Ï‹v—ÍƒQ[ƒW
class DurabilityGauge : public Gauge   //(e)ƒQ[ƒW
{
public:
	static const D3DXCOLOR COLOR_DURABILITY_FILL;   //‘Ï‹v—Í“h‚è•”•ª‚ÌF
	static const D3DXVECTOR2 ADD_SIZE_BACKGROUND;   //”wŒi‚ÌƒTƒCƒY‚Ì‰ÁZ’l

	//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	DurabilityGauge(int nDurability, D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size) : Gauge(v3Pos, v2Size)
	{
		//ƒƒ“ƒo•Ï”‚ğ‰Šú‰»‚·‚é
		this->m_pDurabilityFill = nullptr;   //‘Ï‹v—Í‚Ì“h‚è•”•ª
		this->m_pGaugeBackground = nullptr;   //”wŒi
		this->m_nMaxDurability = nDurability;   //‘Ï‹v—Í‚ÌÅ‘å’l
	}

	//ƒfƒXƒgƒ‰ƒNƒ^
	~DurabilityGauge()
	{
	}

	void Init() override;   //‰Šú‰»
	void Uninit() override;   //I—¹ˆ—
	void Update() override;   //XVˆ—
	void Draw() override;   //•`‰æˆ—
	void ApplyDurability(int nDurability);   //‘Ï‹v—Í‚Ì“K—pˆ—

	static DurabilityGauge* Create(int nDurability, D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size);   //¶¬ˆ—

private:
	DurabilityFill* m_pDurabilityFill;   //‘Ï‹v—Í‚Ì“h‚è•”•ª
	GaugeBackground* m_pGaugeBackground;   //”wŒi•”•ª
	int m_nMaxDurability;   //‘Ï‹v—Í‚ÌÅ‘å’l
};

#endif // !_DURABILITY_GAUGE_H_
