//===============================================================================
//
//		�X�R�A�Ǘ��N���X(score.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "number.h"


class CScore
{
public:
	CScore();		//�R���X�g���N�^
	~CScore();		//�f�X�g���N�^
	void Init();		//������
	void Init(D3DXVECTOR3 pos);		//������

	void Uninit();		//�I��
	void Update();		//�X�V
	void Draw();		//�`��
	static CScore* Create();
	static CScore* Create(D3DXVECTOR3 pos);

	inline void LoadLastScore() { m_Score = SaveScore; GetLastNum(); }
	inline void ResetScore() { m_Score += 0; GetLastNum(); SaveScore = m_Score;};
	inline void SetScore(int nScore) { m_Score = nScore; GetLastNum(); SaveScore = m_Score; }
	inline void AddScore(int nScore) { m_Score += nScore; GetLastNum(); SaveScore = m_Score;}
private:
	static constexpr int MAX_DIGIT = 8;
	static constexpr float MAX_HEIGHT = 50.0f;
	static constexpr float MAX_WIDTH = 80.0f;

	void GetLastNum();
	int m_Score;

	static const D3DXVECTOR3 DEFAULT_POSITION;
	static int SaveScore;
	CNumber* m_number[MAX_DIGIT];
};

#endif