//===============================================================================
//
//  ���U���g�V�[��(result.h)
//								����F���n�O��
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
	bool m_bSelect;
};

#endif