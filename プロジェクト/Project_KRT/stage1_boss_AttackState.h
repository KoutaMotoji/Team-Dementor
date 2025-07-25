////===============================================================================
////
////  ゴリラの攻撃AIクラス(stage1_boss_AttackState.h)
////								制作：元地弘汰
//// 
////===============================================================================
//#ifndef _GORIRA_ATTACKSTATE_H_
//#define _GORIRA_ATTACKSTATE_H_
//
//#include "main.h"
//#include "stage1_boss.h"
//
////========================================================================================================
////プレイヤーの連続攻撃
//class AttackBehavior
//{
//private:
//
//
//protected:
//	bool InputNormal();		//通常攻撃の入力
//	bool InputExtended();	//派生攻撃の入力
//	struct MyInfo
//	{
//		bool use;
//		int motion_num;
//	};
//
//public:
//	bool m_bUse;
//	int m_MyMotionNum;
//
//	AttackBehavior(MyInfo info = { false,1 }) :m_bUse(info.use), m_MyMotionNum(info.motion_num) {};
//	virtual void NextAttack([[maybe_unused]] CG_Gorira* pGorira) = 0;
//	virtual void UseDisable() {}
//	bool GetUse() { return m_bUse; }
//	int GetMyMotionNum() { return m_MyMotionNum; }
//
//
//};
//
//
//class Attack_None : public AttackBehavior		//非攻撃状態
//{
//public:
//	Attack_None(MyInfo info = { true,CG_Gorira::MOTION_NUTORAL }) :AttackBehavior(info) {}
//	void NextAttack([[maybe_unused]] CG_Gorira* pPlayer)override;
//	void UseDisable()override { m_bUse = false; }
//
//};
//class Attack_Normal1 : public AttackBehavior	//通常1段目
//{
//public:
//	Attack_Normal1(MyInfo info = { true,CG_Gorira::MOTION_ATTACK_N1 }) :AttackBehavior(info) {}
//	void NextAttack([[maybe_unused]] CG_Gorira* pPlayer)override;
//	void UseDisable()override { m_bUse = false; }
//
//};
//class Attack_Normal2 : public AttackBehavior	//通常2段目
//{
//public:
//	Attack_Normal2(MyInfo info = { true,CG_Gorira::MOTION_ATTACK_N2 }) :AttackBehavior(info) {}
//	void NextAttack([[maybe_unused]] CG_Gorira* pPlayer)override;
//	void UseDisable()override { m_bUse = false; }
//
//};
//class Attack_Normal3 : public AttackBehavior	//通常3段目
//{
//public:
//	Attack_Normal3(MyInfo info = { true,CG_Gorira::MOTION_ATTACK_N3 }) :AttackBehavior(info) {}
//	void NextAttack([[maybe_unused]] CG_Gorira* pPlayer)override;
//	void UseDisable()override { m_bUse = false; }
//};
//class Attack_Normal4 : public AttackBehavior	//通常4段目
//{
//public:
//	Attack_Normal4(MyInfo info = { true,CG_Gorira::MOTION_ATTACK_N4 }) :AttackBehavior(info) {}
//	void NextAttack([[maybe_unused]] CG_Gorira* pPlayer)override;
//	void UseDisable()override { m_bUse = false; }
//};
//class Attack_Normal5 : public AttackBehavior	//通常5段目
//{
//public:
//	Attack_Normal5(MyInfo info = { true,CG_Gorira::MOTION_ATTACK_N5 }) :AttackBehavior(info) {}
//	void NextAttack([[maybe_unused]] CG_Gorira* pPlayer)override;
//	void UseDisable()override { m_bUse = false; }
//};
//class Attack_Normal6 : public AttackBehavior	//通常6段目
//{
//public:
//	Attack_Normal6(MyInfo info = { true,CG_Gorira::MOTION_ATTACK_N6 }) :AttackBehavior(info) {}
//	void NextAttack([[maybe_unused]] CG_Gorira* pPlayer)override;
//	void UseDisable()override { m_bUse = false; }
//};
//class Attack_Normal7 : public AttackBehavior	//通常最終段目
//{
//public:
//	Attack_Normal7(MyInfo info = { true,CG_Gorira::MOTION_ATTACK_N7 }) :AttackBehavior(info) {}
//	void NextAttack([[maybe_unused]] CG_Gorira* pPlayer)override;
//	void UseDisable()override { m_bUse = false; }
//};
//class Attack_Extended3 : public AttackBehavior		//派生3段目
//{
//public:
//	Attack_Extended3(MyInfo info = { true,CG_Gorira::MOTION_ATTACK_Ex3 }) :AttackBehavior(info) {}
//	void NextAttack([[maybe_unused]] CG_Gorira* pPlayer)override;
//	void UseDisable()override { m_bUse = false; }
//};
//class Attack_Extended5 : public AttackBehavior		//派生5段目
//{
//public:
//	Attack_Extended5(MyInfo info = { true,CG_Gorira::MOTION_ATTACK_Ex5 }) :AttackBehavior(info) {}
//	void NextAttack([[maybe_unused]] CG_Gorira* pPlayer)override;
//	void UseDisable()override { m_bUse = false; }
//};
//class Attack_Extended6 : public AttackBehavior		//派生6段目
//{
//public:
//	Attack_Extended6(MyInfo info = { true,CG_Gorira::MOTION_ATTACK_Ex6 }) :AttackBehavior(info) {}
//	void NextAttack([[maybe_unused]] CG_Gorira* pPlayer)override;
//	void UseDisable()override { m_bUse = false; }
//};
//
//class Attack_ExGorira3 : public AttackBehavior		//派生5段目
//{
//public:
//	Attack_ExGorira3(MyInfo info = { true,CG_Gorira::MOTION_ATTACK_G_Ex3 }) :AttackBehavior(info) {}
//	void NextAttack([[maybe_unused]] CG_Gorira* pPlayer)override;
//	void UseDisable()override { m_bUse = false; }
//};
//class Attack_ExGorira4 : public AttackBehavior		//派生5段目
//{
//public:
//	Attack_ExGorira4(MyInfo info = { true,CG_Gorira::MOTION_ATTACK_G_Ex4 }) :AttackBehavior(info) {}
//	void NextAttack([[maybe_unused]] CG_Gorira* pPlayer)override;
//	void UseDisable()override { m_bUse = false; }
//};
//
//class Attack_ExGorira6 : public AttackBehavior		//派生6段目
//{
//public:
//	Attack_ExGorira6(MyInfo info = { true,CG_Gorira::MOTION_ATTACK_G_Ex6 }) :AttackBehavior(info) {}
//	void NextAttack([[maybe_unused]] CG_Gorira* pPlayer)override;
//	void UseDisable()override { m_bUse = false; }
//};
//
//#endif 
