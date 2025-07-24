//===============================================================================
//
//		�v���C���[�pUI(player_UI.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _STAGE1BOSS_UI_H_
#define _STAGE1BOSS_UI_H_

#include "main.h"
#include "object2D.h"

//�v���C���[HP�Q�[�W�{��
class CStage1BossGaugeLife :public CObject2D
{
public:
	CStage1BossGaugeLife(int nPriority = 7);		//�R���X�g���N�^
	~CStage1BossGaugeLife()override;				//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��
	static CStage1BossGaugeLife* Create(int nMaxStage1BossGauge);
private:
	void SetStage1BossGauge(int nLife);
	int m_nMaxLife;
};

//�v���C���[HP�Q�[�W�̊O���t���[��
class CStage1BossGaugeLiFrame :public CObject2D
{
public:
	CStage1BossGaugeLiFrame(int nPriority = 7) :CObject2D(nPriority) {};		//�R���X�g���N�^
	~CStage1BossGaugeLiFrame()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//�`��

	static CStage1BossGaugeLiFrame* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
private:
};

//�v���C���[HP�Q�[�W�̗���
class CStage1BossGaugeLiBack :public CObject2D
{
public:
	CStage1BossGaugeLiBack(int nPriority = 6) : CObject2D(nPriority) {};		//�R���X�g���N�^
	~CStage1BossGaugeLiBack()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//�`��

	static CStage1BossGaugeLiBack* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
private:
};

//�v���C���[HP�Q�[�W�̑���
class CStage1BossGaugeLiDeco :public CObject2D
{
public:
	CStage1BossGaugeLiDeco(int nPriority = 5) : CObject2D(nPriority) {};		//�R���X�g���N�^
	~CStage1BossGaugeLiDeco()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//�`��

	static CStage1BossGaugeLiDeco* Create();
private:
};

#endif