//===============================================================================
//
//  ゲーム内情報格納用(game_info.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _GAMEINFO_H_
#define _GAMEINFO_H_

//インライン展開だけで済む設計にするのでcppファイルはないですよ

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
	int m_nEnemyKillCnt;//雑魚撃破数
	int m_nTime;		//フレーム単位のクリア時間
	int m_nTimeMS;		//分秒のクリア時間(百の位が分、それ以下が秒数)
	int m_ParryCnt;		//パリィ成功数
	int m_JustParryCnt;	//ジャストパリィ成功数
};

#endif