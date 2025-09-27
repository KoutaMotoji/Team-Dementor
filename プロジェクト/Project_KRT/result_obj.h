//===============================================================================
//
//  ���U���g�I�u�W�F�N�g(result_obj.h)
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

class CR_Graound :public CObjectX
{
public:
	CR_Graound(int nPriority = 2);				//�R���X�g���N�^
	~CR_Graound()override;		//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//�`��
	static CR_Graound* Create();

protected:

private:
};
class CResultBG :public CObject2D
{
public:
	CResultBG(int nPriority = 3):CObject2D(nPriority)  {};		//�R���X�g���N�^
	~CResultBG()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//������

	static CResultBG* Create();
private:
};
class CResultBGBack :public CObject2D
{
public:
	CResultBGBack(int nPriority = 2) :CObject2D(nPriority) {};		//�R���X�g���N�^
	~CResultBGBack()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//������

	static CResultBGBack* Create();
private:
};
class CResultReview :public CObject2D
{
public:
	CResultReview(int nPriority = 2) :CObject2D(nPriority) {};		//�R���X�g���N�^
	~CResultReview()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//������

	static CResultReview* Create(bool bResult);
private:
};
class CResultRank :public CObject2D
{
public:
	CResultRank(int nPriority = 2) :CObject2D(nPriority) {};		//�R���X�g���N�^
	~CResultRank()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//������

	static CResultRank* Create(int nResult);
private:
};
#endif