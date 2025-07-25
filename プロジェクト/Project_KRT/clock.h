//===============================================================================
//
//		���vUI(Clock.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _CLOCK_UI_H_
#define _CLOCK_UI_H_

#include "main.h"
#include "object2D.h"
#include "objectCircleGauge.h"

class CClock
{
private:
	static std::shared_ptr<CClock>_instance;
	int m_LastCount;	//�c��J�E���g��
	int m_MaxCount;		//�ő�J�E���g��

	int m_FrameCnt;		//�t���[���v���p
	bool m_bCountedThisFrame;	//���݂̃t���[������2�x�ȏ�X�V����Ȃ��悤�ɂ���t���O
	bool m_bTimerStop;
public:
	CClock() :m_bCountedThisFrame(false), m_LastCount(0), m_FrameCnt(0), m_bTimerStop(false){}
	~CClock() = default;
	_inline static std::shared_ptr<CClock> GetInstance() {
		if (_instance == nullptr)
		{
			_instance = std::make_shared<CClock>();
			_instance->m_LastCount = 1;
			_instance->m_MaxCount = 1;
		}
		return _instance;
	}
	void Update()
	{
		if (m_bCountedThisFrame)return;
		if (m_bTimerStop)return;
		if (m_LastCount <= 0)return;
		if (m_FrameCnt >= 60)
		{
			m_FrameCnt = 0;
			--m_LastCount;
		}
		else ++m_FrameCnt;
		m_bCountedThisFrame = true;
	}

	void FrameFragDisable() { m_bCountedThisFrame = false; }	//���݂̃t���[�����ł̎g�p�t���O����
	int GetLastCount() { return m_LastCount; }					//���݂̎c�莞�Ԃ�Ԃ�
	int GetMaxCount() { return m_MaxCount; }					//���݂̎c�莞�Ԃ�Ԃ�

	bool GetTimeUped() { return m_LastCount <= 0; }				//���݂��������ԓ�����Ԃ�
	void SetTimerStop(bool bStop) { m_bTimerStop = bStop; }		//�^�C�}�[��~
	void SetClock(int Value) { m_LastCount = Value; m_MaxCount = Value; }
};


//====================================================================================================
//�ȉ�UI����

//�|�C���^�擾�p�O���錾
class CClockHands;
class CClockBack;

//���v�p�Q�[�W�{��
class CClockGauge :public CObjectCircleGauge
{
public:
	CClockGauge(int nPriority = 5) : CObjectCircleGauge(nPriority), m_pClockHands(nullptr){};		//�R���X�g���N�^
	~CClockGauge()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;
	void Update()override;		//�X�V

	void Draw()override;		//�`��

	static CClockGauge* Create();
private:
	void QuakeObj();
	CClockHands* m_pClockHands;
	CClockBack* m_pClockBack;
};

//���v�p�Q�[�W
class CClockBack :public CObject2D
{
public:
	CClockBack(int nPriority = 4) : CObject2D(nPriority) {};		//�R���X�g���N�^
	~CClockBack()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//�`��

	static CClockBack* Create();
private:
};

//���v�p�j
class CClockHands :public CObject2D
{
public:
	CClockHands(int nPriority = 6) : CObject2D(nPriority) {};		//�R���X�g���N�^
	~CClockHands()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Draw()override;		//�`��

	static CClockHands* Create();
private:
};

#endif