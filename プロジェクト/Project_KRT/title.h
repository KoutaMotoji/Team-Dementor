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
	void Draw()override;		//初期化

	static CTitleBG* Create();
private:
};
class CTitleButton :public CObject2D
{
public:
	CTitleButton() :m_LocalCol({ 1.0f,1.0f,1.0f,1.0f }), m_bSpeed(false), m_bColSwitch(false) {};		//コンストラクタ
	~CTitleButton()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//初期化

	static CTitleButton* Create();
private:
	bool m_bSpeed, m_bColSwitch;
	D3DXCOLOR m_LocalCol;
};

#endif