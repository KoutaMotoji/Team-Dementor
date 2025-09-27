//===============================================================================
//
//  雑魚敵の攻撃AIクラス(enemy_attack_state.h)
//								制作：大竹熙
// 
//===============================================================================

#ifndef _GORIRA_ATTACKSTATE_H_
#define _GORIRA_ATTACKSTATE_H_

#include "main.h"
#include "enemy.h"

class Enemy_AI
{
public:
	Enemy_AI() : m_Timer(0), m_bDoing(false), m_CoolTime(0) {};
	~Enemy_AI() = default;
	void AI_Init();
	void AI_Update([[maybe_unused]] CEnemy* pEnemy);
	void AI_DoFinish() { m_bDoing = false; }
	void FinishAction();

private:
	void SetNextAction([[maybe_unused]] CEnemy* pEnemy);		//次の行動を決定
	void SetThinkValue();		//思考する間隔を設定
	bool SearchPlayer([[maybe_unused]] CEnemy* pEnemy);		//遠い場合にtrueを返す
	bool GetIsThinking() { return m_Timer <= 0; }
	int m_Timer;
	bool m_bDoing;
	int m_CoolTime;    // 攻撃後クールタイム
};

//========================================================================================================
//雑魚敵の各攻撃
class E_AttackBehavior	//攻撃ステート基底クラス
{
private:

protected:

public:
	E_AttackBehavior() {};
	virtual void AttackInit([[maybe_unused]] CEnemy* pEnemy) = 0;
	virtual void AttackUninit([[maybe_unused]] CEnemy* pEnemy) = 0;
	virtual void AttackUpdate([[maybe_unused]] CEnemy* pEnemy) = 0;
	virtual void AttackFinish([[maybe_unused]] CEnemy* pEnemy) = 0;
};

class E_Attack_None : public E_AttackBehavior		//非攻撃状態
{
public:
	void AttackInit([[maybe_unused]] CEnemy* pEnemy)override {};
	void AttackUninit([[maybe_unused]] CEnemy* pEnemy)override {};
	void AttackUpdate([[maybe_unused]] CEnemy* pEnemy)override {};
	void AttackFinish([[maybe_unused]] CEnemy* pEnemy)override {};
};

class E_Attack_Normal : public E_AttackBehavior	//通常攻撃
{
public:
	void AttackInit([[maybe_unused]] CEnemy* pEnemy)override;
	void AttackUninit([[maybe_unused]] CEnemy* pEnemy)override {};
	void AttackUpdate([[maybe_unused]] CEnemy* pEnemy)override;
	void AttackFinish([[maybe_unused]] CEnemy* pEnemy)override {};

};

class E_Attack_Dive : public E_AttackBehavior	//通常飛び込み
{
public:
	void AttackInit([[maybe_unused]] CEnemy* pEnemy)override;
	void AttackUninit([[maybe_unused]] CEnemy* pEnemy)override {};
	void AttackUpdate([[maybe_unused]] CEnemy* pEnemy)override;
	void AttackFinish([[maybe_unused]] CEnemy* pEnemy)override;

private:
	void SlerpRotatedPosition([[maybe_unused]] CEnemy* pEnemy, float frame);
	int m_NowFrame;			//現在の補間フレーム
	int m_DestFrame;		//補間フレームの最大値
	D3DXVECTOR3 m_LastPos;
	D3DXVECTOR3 m_LastPlayerPos;
	D3DXVECTOR3 m_Dir;

	D3DXQUATERNION quat;
};
#endif 
