//===============================================================================
//
//  �I�u�W�F�N�g���N���X(object.h)
//								����F���n�O��
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
		TYPE_3D_BLOCK,
		TYPE_3D_STAGE_BG,
		TYPE_3D_S_MARKER,
		TYPE_3D_G_MARKER,
		TYPE_3D_WEAPON,
		TYPE_3D_ENEMY,
		TYPE_3D_ENEMY_WEAPON,
		TYPE_BILLBOARD,
		TYPE_3D_ITEMS,
		TYPE_3D_MESHOBJECT,
		TYPE_3D_OBSTACLE,
		TYPE_3D_BOSSTERRA,
		TYPE_3D_MADEMESH,
		TYPE_3D_TITLEOBJ,
		TYPE_3D_TUTORIALOBJ,
		TYPE_3D_RESULTOBJ,
		TYPE_3D_GAMEOVEROBJ,

		TYPE_3D_BOSSWEAPONS,
		TYPE_3D_BOSSBULLET
	}TYPE;

	CObject(int nPriority = 3);		//�R���X�g���N�^
	virtual ~CObject();				//�f�X�g���N�^
	virtual void Init() = 0;		//������
	virtual void Uninit() = 0;		//�I��
	virtual void Update() = 0;		//�X�V
	virtual void Draw() = 0;		//�`��

	static void ReleaseAll();		//���ׂă����[�X
	static void UpdateAll();		//���ׂčX�V
	static void DrawAll();			//���ׂĕ`��
	
	void Release();					//�����[�X

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
	//bool m_bDeath;					//true�ł���Δj��
};

#endif