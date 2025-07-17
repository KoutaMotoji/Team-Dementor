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

//�v���C���[HP�Q�[�W�{��
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

//�v���C���[HP�Q�[�W�̊O���t���[��
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

//�v���C���[HP�Q�[�W�̗���
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

//�v���C���[HP�Q�[�W�̑���
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

//�~�`�Q�[�W(�p�r����)
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

//�~�`�Q�[�W����
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

//�r�p�[�cUI-����
class CWeaponUI_Sub :public CObject2D
{
public:
	CWeaponUI_Sub(int nPriority = 4) : CObject2D(nPriority) {};		//�R���X�g���N�^
	~CWeaponUI_Sub()override = default;				//�f�X�g���N�^
	void Init()override;		//������

	static CWeaponUI_Sub* Create();
private:
};
//�r�p�[�cUI-�w�i
class CWeaponUI_Back :public CObject2D
{
public:
	CWeaponUI_Back(int nPriority = 3) : CObject2D(nPriority) {};		//�R���X�g���N�^
	~CWeaponUI_Back()override = default;				//�f�X�g���N�^
	void Init()override;		//������

	static CWeaponUI_Back* Create();
private:
};

//�r�p�[�cUI-�Ȃɂ��Ȃ�
class CWeaponUI_Main :public CObject2D
{
public:
	CWeaponUI_Main(int nPriority = 4) : CObject2D(nPriority) {};		//�R���X�g���N�^
	~CWeaponUI_Main()override = default;				//�f�X�g���N�^
	void Init()override;		//������

	static CWeaponUI_Main* Create();
private:
};
//�r�p�[�cUI-�S����
class CWeaponUI_Main_Gorira :public CWeaponUI_Main
{
public:
	CWeaponUI_Main_Gorira()  {};		//�R���X�g���N�^
	~CWeaponUI_Main_Gorira()override = default;				//�f�X�g���N�^
	void Init()override;		//������

	static CWeaponUI_Main_Gorira* Create();
private:
};

#endif