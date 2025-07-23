//===============================================================================
//
//  プレイヤーの腕状態管理クラス(player_armState.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _PLAYER_ARMSTATE_H_
#define _PLAYER_ARMSTATE_H_

#include "main.h"
#include "xxx_player.h"

//腕状態管理クラスの基底クラス
class PlayerArm_State
{
private:

public:
	//腕の状態によって変化するモーションを別々に扱う用の関数(攻撃モーションは別で管理)
	virtual void WalkMotion([[maybe_unused]]CPlayerX* pPlayer) = 0;
	virtual void ParryMotion([[maybe_unused]]CPlayerX* pPlayer) = 0;
	virtual void ParryStayMotion([[maybe_unused]]CPlayerX* pPlayer) = 0;
};

//通常腕の時の振る舞いを管理するクラス
class Arm_Normal : public PlayerArm_State
{
	void WalkMotion([[maybe_unused]]CPlayerX* pPlayer)override;
	void ParryMotion([[maybe_unused]]CPlayerX* pPlayer) override;
	void ParryStayMotion([[maybe_unused]]CPlayerX* pPlayer) override;
};

//ゴリラ腕の時の振る舞いを管理するクラス
class Arm_Gorira : public PlayerArm_State
{
	void WalkMotion([[maybe_unused]]CPlayerX* pPlayer)override;
	void ParryMotion([[maybe_unused]]CPlayerX* pPlayer) override;
	void ParryStayMotion([[maybe_unused]]CPlayerX* pPlayer) override;
};


#endif 
