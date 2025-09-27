//===============================================================================
//
//  スコアの表示・数字ポリゴンの計算処理(score.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "score.h"
#include "manager.h"

const D3DXVECTOR3 CScore::DEFAULT_POSITION = { SCREEN_WIDTH - DEFAULT_WIDTH / 2,DEFAULT_HEIGHT,0.0f };
int CScore::SaveScore = 0;
namespace			//定数用無名名前空間
{
	float POS_INTERVAL = 80.0f / 1.95;
	float POS_INTERVAL_OR = 80.0f / 1.75f;
}

CScore::CScore() : m_Score(0)
{

}

CScore::~CScore()
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
void CScore::Init()
{
	D3DXVECTOR3 pos = DEFAULT_POSITION;
	for (int i = 0; i < m_nDigit; ++i)
	{
		m_number.push_back(CNumber::Create(pos, m_fHeight, m_fWidth));
		pos.x -= POS_INTERVAL;
	}
}

//==========================================================================================
//初期化処理(オーバーロード)
//==========================================================================================
void CScore::Init(D3DXVECTOR3 pos)
{
	for (int i = 0; i < m_nDigit; ++i)
	{
		m_number.push_back(CNumber::Create(pos, m_fHeight, m_fWidth));
		pos.x -= POS_INTERVAL_OR;
	}
}
//==========================================================================================
//初期化処理(オーバーロード)
//==========================================================================================
void CScore::Init(D3DXVECTOR3 pos, int i)
{
	for (int i = 0; i < m_nDigit; ++i)
	{
		m_number.push_back(CNumber::Create(pos, m_fHeight, m_fWidth, 1));
		pos.x -= m_fWidth / 1.75f;
	}
}
//==========================================================================================
//終了処理
//==========================================================================================
void CScore::Uninit()
{

	for (auto& e : m_number)e->Uninit();

}

//==========================================================================================
//更新処理
//==========================================================================================
void CScore::Update()
{
	for (auto& e : m_number)e->Update();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CScore::Draw()
{

	for (auto& e : m_number)	e->Draw();
}

//==========================================================================================
//生成処理
//==========================================================================================
CScore* CScore::Create()
{
	CScore* number = new CScore;
	number->m_nDigit = DEFAULT_DIGIT;
	number->m_fHeight = DEFAULT_HEIGHT;
	number->m_fWidth = DEFAULT_WIDTH;
	number->Init();

	return number;
}

//==========================================================================================
//生成処理(オーバーロード)
//==========================================================================================
CScore* CScore::Create(D3DXVECTOR3 pos)
{
	CScore* number = new CScore;
	number->m_nDigit = DEFAULT_DIGIT;
	number->m_fHeight = DEFAULT_HEIGHT;
	number->m_fWidth = DEFAULT_WIDTH;
	number->Init(pos);

	return number;
}

//==========================================================================================
//生成処理(オーバーロード)
//==========================================================================================
CScore* CScore::Create(D3DXVECTOR3 pos, int Digit, float Height, float Width)
{
	CScore* number = new CScore;
	number->m_nDigit = Digit;
	number->m_fHeight = Height;
	number->m_fWidth = Width;
	number->Init(pos, 1);

	return number;
}

//==========================================================================================
//数値の各桁の数字を抜き出す
//==========================================================================================
void CScore::GetLastNum()
{
	int nType = 1;
	int nValue = m_Score;		//スコアをローカルにコピー
	int Num = 0;
	for (int i = 0; i < m_nDigit; ++i)
	{
		nType *= 10;			//桁数計算用の数値を設定
		Num = (nValue % nType * 10) / nType;	//指定桁数の数字を抜き出す
		m_number[i]->SetNum(Num);				//抜き出した数字をポリゴン表示用クラスに渡す
	}
}
