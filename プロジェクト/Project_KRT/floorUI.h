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
	CBaseFloorUI() {};					//�R���X�g���N�^
	~CBaseFloorUI()override = default;	//�f�X�g���N�^
	void Init()override;				//������
	void Update()override;				//�X�V

	static CBaseFloorUI* Create(D3DXVECTOR3 pos);
private:
};

class CFloorUI : public CBaseFloorUI
{
public:
	CFloorUI() {};						//�R���X�g���N�^
	~CFloorUI()override = default;		//�f�X�g���N�^
	void Init()override;				//������
	void Update()override;				//�X�V
	void Draw()override;				//�`��

	static CFloorUI* Create(D3DXVECTOR3 pos);
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
	
	void SetFloorNumberUI(int nfloornumber);
	void AddFloorNumber(int addnumber) { m_FloorNumber + addnumber; }
	void SetTexPos(int ntexpos) { m_nTexPos = ntexpos; }

	static CFloorNumberUI* Create(D3DXVECTOR3 pos);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFloorNumberUI;
	int  m_nTexPos;
	int m_FloorNumber;
};

class CFloorTypeUI : public CBaseFloorUI
{
public:
	CFloorTypeUI() {};						//�R���X�g���N�^
	~CFloorTypeUI()override = default;		//�f�X�g���N�^
	void Init()override;					//������
	void Update()override;					//�X�V
	void Draw()override;					//�`��
		
	static CFloorTypeUI* Create(D3DXVECTOR3 pos);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFloorTypeUI;
	int  m_nTexPos;
};

#endif