//===============================================================================
//
//  �Q�[�������i�[�p(game_info.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _GAMEINFO_H_
#define _GAMEINFO_H_

//�C�����C���W�J�����ōςސ݌v�ɂ���̂�cpp�t�@�C���͂Ȃ��ł���

namespace
{
	int BOSSKILL_SCORE = 20000;
	int FRAME_DIGIT = 60;
	int MAX_MITITUS = 5 * 60 * 60;
	int PARRY_SCORE = 2000;
}

class CGameInfo 
{
public:
	CGameInfo():m_nEnemyKillCnt(0), m_nTime(0), m_ParryCnt(0), m_JustParryCnt(0){}
	~CGameInfo() {}

	int GetResultScore(bool BossKill)
	{
		int KillScore = BOSSKILL_SCORE * (int)BossKill;
		int ClearTime = MAX_MITITUS - m_nTime;
		int ParrySocre = PARRY_SCORE * m_ParryCnt;
		int JustParrySocre = (PARRY_SCORE *5)* m_JustParryCnt;

		return KillScore + ClearTime + ParrySocre + JustParrySocre;
	}

	void AllReset() {
		m_nEnemyKillCnt = 0;
		m_nTime = 0;
		m_nTimeMS = 0;
		m_ParryCnt = 0;
		m_JustParryCnt = 0;
	}
	void TimeUpdate() { ++m_nTime; }
	void AddEnemyKill() { ++m_nEnemyKillCnt; }
	void AddParryCnt() { ++m_ParryCnt; }
	void AddJustParryCnt() { ++m_JustParryCnt; }

	void TimeDigit()
	{
		int second;
		int minuts;
		int secondleft;
		second = m_nTime / FRAME_DIGIT;
		minuts = second / FRAME_DIGIT;
		secondleft = second % FRAME_DIGIT;
		m_nTimeMS = (minuts * 100) + secondleft;
	}
private:
	int m_nEnemyKillCnt;//�G�����j��
	int m_nTime;		//�t���[���P�ʂ̃N���A����
	int m_nTimeMS;		//���b�̃N���A����(�S�̈ʂ����A����ȉ����b��)
	int m_ParryCnt;		//�p���B������
	int m_JustParryCnt;	//�W���X�g�p���B������
};

#endif