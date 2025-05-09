//===============================================================================
//
//  タイトルシーン(title.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"
#include "object2D.h"
#include "objectX.h"

class CStarter;
class CTitleButton;
class CTitleUI;

class CTitle : public CScene
{
public:
	CTitle();
	~CTitle()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	void UpdateAnim(int m);
	int m_AnimTimer;
	bool m_bNowAnim;
	int m_nSelect;
	CStarter* m_tSt;
	CTitleButton* m_tBut;
	CTitleUI* m_tUI;

	enum
	{
		SELECT_GAME = 0,
		SELECT_TUTORIAL,
		SELECT_FINISH
	};
};
class CTitleBG :public CObject2D
{
public:
	CTitleBG() {};		//コンストラクタ
	~CTitleBG()override = default;				//デストラクタ
	void Init()override;		//初期化

	static CTitleBG* Create();
private:
};
#endif