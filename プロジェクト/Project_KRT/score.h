//===============================================================================
//
//		スコア管理クラス(score.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "number.h"


class CScore
{
public:
	CScore();		//コンストラクタ
	~CScore();		//デストラクタ
	void Init();		//初期化
	void Init(D3DXVECTOR3 pos);		//初期化
	void Init(D3DXVECTOR3 pos, int i);		//初期化

	void Uninit();		//終了
	void Update();		//更新
	void Draw();		//描画
	static CScore* Create();
	static CScore* Create(D3DXVECTOR3 pos);
	static CScore* Create(D3DXVECTOR3 pos, int Digit, float Height, float Width);	//位置、桁数、高さ、幅用のオーバーロード


	inline void LoadLastScore() { m_Score = SaveScore; GetLastNum(); }
	inline void ResetSaveScore() { SaveScore = 0; GetLastNum(); }

	inline void ResetScore() { m_Score = 0; GetLastNum(); SaveScore = m_Score; };
	inline void SetScore(int nScore) { m_Score = nScore; GetLastNum(); SaveScore = m_Score; }
	inline void AddScore(int nScore) { m_Score += nScore; GetLastNum(); SaveScore = m_Score; }
private:
	static constexpr int DEFAULT_DIGIT = 8;
	static constexpr float DEFAULT_HEIGHT = 50.0f;
	static constexpr float DEFAULT_WIDTH = 80.0f;

	int m_nDigit;	//桁数
	float m_fHeight, m_fWidth;

	void GetLastNum();
	int m_Score;

	static const D3DXVECTOR3 DEFAULT_POSITION;
	static int SaveScore;
	std::vector<CNumber*> m_number;
};

#endif