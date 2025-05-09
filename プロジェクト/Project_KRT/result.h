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
};

class CResultBG :public CObject2D
{
public:
	CResultBG() {};		//コンストラクタ
	~CResultBG()override = default;				//デストラクタ
	void Init()override;		//初期化

	static CResultBG* Create();
private:
};

#endif