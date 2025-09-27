//===============================================================================
//
//  リザルトシーン(result.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "scene.h"
#include "object2D.h"
#include "score.h"


class CResult : public CScene
{
public:
	CResult();
	~CResult()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	bool m_bSelect;
	CScore* m_pScore;

};

#endif