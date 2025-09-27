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
	void Init(D3DXVECTOR3 pos, int i);		//������

	void Uninit();		//�I��
	void Update();		//�X�V
	void Draw();		//�`��
	static CScore* Create();
	static CScore* Create(D3DXVECTOR3 pos);
	static CScore* Create(D3DXVECTOR3 pos, int Digit, float Height, float Width);	//�ʒu�A�����A�����A���p�̃I�[�o�[���[�h


	inline void LoadLastScore() { m_Score = SaveScore; GetLastNum(); }
	inline void ResetSaveScore() { SaveScore = 0; GetLastNum(); }

	inline void ResetScore() { m_Score = 0; GetLastNum(); SaveScore = m_Score; };
	inline void SetScore(int nScore) { m_Score = nScore; GetLastNum(); SaveScore = m_Score; }
	inline void AddScore(int nScore) { m_Score += nScore; GetLastNum(); SaveScore = m_Score; }
private:
	static constexpr int DEFAULT_DIGIT = 8;
	static constexpr float DEFAULT_HEIGHT = 50.0f;
	static constexpr float DEFAULT_WIDTH = 80.0f;

	int m_nDigit;	//����
	float m_fHeight, m_fWidth;

	void GetLastNum();
	int m_Score;

	static const D3DXVECTOR3 DEFAULT_POSITION;
	static int SaveScore;
	std::vector<CNumber*> m_number;
};

#endif