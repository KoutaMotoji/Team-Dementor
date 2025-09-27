//===============================================================================
//
//  リザルトシーン(result.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "scene.h"
#include "object2D.h"


class CGameover : public CScene
{
public:
	CGameover();
	~CGameover()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	CScore* m_pScore;
	CScore* m_ptime_m;
	CScore* m_ptime_s;
	CScore* m_pkill;
	bool m_bSelect;
};

#endif