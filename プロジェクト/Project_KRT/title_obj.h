//===============================================================================
//
//  タイトルオブジェクト(title_obj.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _TITLEOBJ_H_
#define _TITLEOBJ_H_

#include "main.h"
#include "character.h"
#include "object2D.h"
#include "objectX.h"
#include "billboard.h"

#include "manager.h"

//前方宣言

class CT_Player :public CCharacter
{
public:
	CT_Player(int nPriority = 1);					//コンストラクタ
	~CT_Player()override;		//デストラクタ
	void Init()override;		//初期化
	void Uninit()override;		//終了
	void Update()override;		//更新
	void Draw()override;		//描画

	bool EndMotion()override;
	static CT_Player* Create();

	enum
	{
		MOTION_NUTORAL = 0,
		MOTION_ACTION,
	};
private:
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	//========================			クオータニオン用		====================================
	D3DXMATRIX m_mtxRot;		//回転マトリックス(保存用)
	D3DXQUATERNION m_quat;		//クオータニオン
	D3DXVECTOR3 m_vecAxis;		//回転軸のベクトル
	float m_fValueRot;			//回転量
};

class CT_Graound :public CObjectX
{
public:
	CT_Graound(int nPriority = 2);				//コンストラクタ
	~CT_Graound()override;		//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//描画
	static CT_Graound* Create();

protected:

private:
};

class CTreeBillboard :public CBillboard
{
public:
	CTreeBillboard(int nPriority = 2);	//コンストラクタ
	~CTreeBillboard()override;			//デストラクタ
	void Init()override;				//初期化
	void Uninit()override;				//終了
	void Update()override;				//更新
	void Draw()override;		//描画

	static CTreeBillboard* Create(D3DXVECTOR3 pos);
	void SetPosGround(float HalfRadius);
private:
};

#endif