//===============================================================================
//
//  ゴリラの攻撃AIクラス(stage1_boss_AttackState.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _GORIRA_ATTACKSTATE_H_
#define _GORIRA_ATTACKSTATE_H_

#include "main.h"
#include "stage1_boss.h"

class Gorira_AI
{
public:
	Gorira_AI() :m_bDoing(false){};
	~Gorira_AI() = default;
	void AI_Init();
	void AI_Update([[maybe_unused]] CG_Gorira* pGorira);
	void AI_DoFinish() { m_bDoing = false; }

private:
	void SetNextAction([[maybe_unused]] CG_Gorira* pGorira);		//次の行動を決定
	void SetThinkValue();		//思考する間隔を設定
	bool SearchPlayer([[maybe_unused]] CG_Gorira* pGorira);		//遠い場合にtrueを返す
	bool GetIsThinking() { return m_Timer <= 0; }
	int m_Timer;
	bool m_bDoing;
};

//========================================================================================================
//ボスの各攻撃
class G_AttackBehavior	//攻撃ステート基底クラス
{
private:

protected:

public:
	G_AttackBehavior() {};
	virtual void G_AttackInit([[maybe_unused]] CG_Gorira* pGorira) = 0;
	virtual void G_AttackUninit([[maybe_unused]] CG_Gorira* pGorira) = 0;

	virtual void G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira) = 0;
	virtual void G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira) = 0;
};


class G_Attack_None : public G_AttackBehavior		//非攻撃状態
{
public:
	void G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)override {};
	void G_AttackUninit([[maybe_unused]] CG_Gorira* pGorira)override {};
	void G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira)override {};
	void G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)override {};
};
class G_Attack_Normal : public G_AttackBehavior	//通常攻撃
{
public:
	void G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackUninit([[maybe_unused]] CG_Gorira* pGorira)override {};
	void G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)override {};

};
class G_Attack_Dive : public G_AttackBehavior	//通常飛び込み
{
public:
	void G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackUninit([[maybe_unused]] CG_Gorira* pGorira)override {};
	void G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)override;

private:
	void SlerpRotatedPosition([[maybe_unused]] CG_Gorira* pGorira,float frame);
	int m_NowFrame;			//現在の補間フレーム
	int m_DestFrame;		//補間フレームの最大値
	D3DXVECTOR3 m_LastPos;
	D3DXVECTOR3 m_LastPlayerPos;

	D3DXQUATERNION quat;
};
class G_Attack_Spin : public G_AttackBehavior	//通常腕回転
{
public:
	void G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackUninit([[maybe_unused]] CG_Gorira* pGorira)override {};
	void G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)override {};

};
class G_Attack_DoubleHammer : public G_AttackBehavior	//ダブルスレッジハンマー
{
public:
	void G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackUninit([[maybe_unused]] CG_Gorira* pGorira)override {}
	void G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira)override;
	void G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)override {};

};

#endif 
