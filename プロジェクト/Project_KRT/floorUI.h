//===============================================================================
//
//  �t���AUI����(floorUI.h)
//					����F��|�
// 
//===============================================================================

#ifndef _FLOORUI_H_
#define _FLOORUI_H_

#include "object2D.h"

class CBaseFloorUI : public CObject2D
{
public:
	CBaseFloorUI(int nPriority = 3):CObject2D(nPriority) {};					//�R���X�g���N�^
	~CBaseFloorUI()override = default;	//�f�X�g���N�^
	void Init()override;				//������
	void Update()override;				//�X�V

	void SetFloorNumberUI();

	void AddScore(int ntexpos) { m_nTexPos += ntexpos; SetFloorNumberUI(); SaveScore = m_nTexPos; }
	void SetTexPos(int ntexpos) { m_nTexPos = ntexpos; }

	static CBaseFloorUI* Create(D3DXVECTOR3 pos);
private:
	int  m_nTexPos;
	static int SaveScore;
};

class CFloorUI : public CBaseFloorUI
{
public:
	CFloorUI() {};						//�R���X�g���N�^
	~CFloorUI()override = default;		//�f�X�g���N�^
	void Init()override;				//������
	void Update()override;				//�X�V
	void Draw()override;				//�`��

	static CFloorUI* Create();
private:
};

class CFloorNumberUI : public CBaseFloorUI
{
public:
	CFloorNumberUI() {};						//�R���X�g���N�^
	~CFloorNumberUI()override = default;		//�f�X�g���N�^
	void Init()override;				//������
	void Update()override;				//�X�V
	void Draw()override;				//�`��

	static CFloorNumberUI* Create(int number);
private:
};



#endif