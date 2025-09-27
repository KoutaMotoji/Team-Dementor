//===============================================================================
//
//  �^�C�g���I�u�W�F�N�g(title_obj.h)
//								����F���n�O��
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

//�O���錾

class CT_Player :public CCharacter
{
public:
	CT_Player(int nPriority = 1);					//�R���X�g���N�^
	~CT_Player()override;		//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��

	bool EndMotion()override;
	static CT_Player* Create();

	enum
	{
		MOTION_NUTORAL = 0,
		MOTION_ACTION,
	};
private:
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

	//========================			�N�I�[�^�j�I���p		====================================
	D3DXMATRIX m_mtxRot;		//��]�}�g���b�N�X(�ۑ��p)
	D3DXQUATERNION m_quat;		//�N�I�[�^�j�I��
	D3DXVECTOR3 m_vecAxis;		//��]���̃x�N�g��
	float m_fValueRot;			//��]��
};

class CT_Graound :public CObjectX
{
public:
	CT_Graound(int nPriority = 2);				//�R���X�g���N�^
	~CT_Graound()override;		//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//�`��
	static CT_Graound* Create();

protected:

private:
};

class CTreeBillboard :public CBillboard
{
public:
	CTreeBillboard(int nPriority = 2);	//�R���X�g���N�^
	~CTreeBillboard()override;			//�f�X�g���N�^
	void Init()override;				//������
	void Uninit()override;				//�I��
	void Update()override;				//�X�V
	void Draw()override;		//�`��

	static CTreeBillboard* Create(D3DXVECTOR3 pos);
	void SetPosGround(float HalfRadius);
private:
};

#endif