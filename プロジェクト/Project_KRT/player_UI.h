//===============================================================================
//
//		�v���C���[�pUI(player_UI.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _PLAYER_UI_H_
#define _PLAYER_UI_H_

#include "main.h"
#include "object2D.h"
#include "objectCircleGauge.h"

class CGaugeLife :public CObject2D
{
public:
	CGaugeLife(int nPriority = 7) ;		//�R���X�g���N�^
	~CGaugeLife()override;				//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��
	static CGaugeLife* Create(int nMaxGauge);
private:
	void SetGauge();
};

class CGaugeLiFrame :public CObject2D
{
public:
	CGaugeLiFrame(int nPriority = 7) :CObject2D(nPriority) {};		//�R���X�g���N�^
	~CGaugeLiFrame()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//�`��

	static CGaugeLiFrame* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
private:
};

class CGaugeLiBack :public CObject2D
{
public:
	CGaugeLiBack(int nPriority = 6) : CObject2D(nPriority) {};		//�R���X�g���N�^
	~CGaugeLiBack()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//�`��

	static CGaugeLiBack* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
private:
};

class CGaugeLiDeco :public CObject2D
{
public:
	CGaugeLiDeco(int nPriority = 5) : CObject2D(nPriority) {};		//�R���X�g���N�^
	~CGaugeLiDeco()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//�`��

	static CGaugeLiDeco* Create();
private:
};

class CGaugeCircle :public CObjectCircleGauge
{
public:
	CGaugeCircle(int nPriority = 5) : CObjectCircleGauge(nPriority) {};		//�R���X�g���N�^
	~CGaugeCircle()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Update()override;		//�X�V
	void Draw()override;		//�`��

	static CGaugeCircle* Create();
private:
};

class CGaugeCircleDeco :public CObject2D
{
public:
	CGaugeCircleDeco(int nPriority = 4) : CObject2D(nPriority) {};		//�R���X�g���N�^
	~CGaugeCircleDeco()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//�`��

	static CGaugeCircleDeco* Create();
private:
};

#endif