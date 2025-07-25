//===============================================================================
//
//  オブジェクト基底クラス(object.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

#define MAX_OBJECT	(1024)
#define SET_PRIORITY	(10)

class CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_BG,
		TYPE_PLAYER,
		TYPE_BULLET,
		TYPE_EXPLOSON,
		TYPE_ENEMY,
		TYPE_PARTICLE,
		TYPE_BLOCK,
		TYPE_2D_UI,
		TYPE_3D_FIELD,
		TYPE_3D_PLAYER,
		TYPE_3D_CHARACTER,
		TYPE_3D_BLOCK,
		TYPE_BILLBOARD,
		TYPE_3D_ITEMS,
		TYPE_3D_MESHOBJECT,
		TYPE_3D_OBSTACLE,
		TYPE_AREAGATE,
		TYPE_3D_BOSS_1,
		TYPE_3D_TITLEOBJ,
		TYPE_3D_TUTORIALOBJ,
		TYPE_3D_RESULTOBJ,
		TYPE_3D_GAMEOVEROBJ,

		TYPE_3D_TITLEMESH,
		TYPE_3D_BOSSBULLET
	}TYPE;

	CObject(int nPriority = 3);		//コンストラクタ
	virtual ~CObject();				//デストラクタ
	virtual void Init() = 0;		//初期化
	virtual void Uninit() = 0;		//終了
	virtual void Update() = 0;		//更新
	virtual void Draw() = 0;		//描画

	static void ReleaseAll();		//すべてリリース
	static void UpdateAll();		//すべて更新
	static void DrawAll();			//すべて描画
	
	void Release();					//リリース

	static CObject* GetObjects(int nPriority,int nIdx);
	
	TYPE GetType();
	void SetType(TYPE type);

	//inline int GetPriority() { return m_nPriority; }
	//inline int GetID() { return m_nID; }
	//inline void WillDelete() { m_bDeleteFrag = true; }
	//inline bool GetDelFrag() { return m_bDeleteFrag; }
protected:							
private:
	static CObject* m_apObject[SET_PRIORITY][MAX_OBJECT];
	int m_nID;
	int m_nPriority;
	//bool m_bDeleteFrag;
	static int m_nNumAll;
	TYPE m_type;
	//bool m_bDeath;					//trueであれば破棄
};

#endif