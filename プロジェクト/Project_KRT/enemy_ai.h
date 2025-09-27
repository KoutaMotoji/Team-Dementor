//===============================================================================
//
//  雑魚敵AI管理 (enemy_ai.h)
//                          制作：大竹熙
//
//===============================================================================

#ifndef _ENEMY_AI_H_
#define _ENEMY_AI_H_

#include "main.h"
#include "enemy.h"

// 敵AIの行動ステート
enum class EnemyAIState
{
    RANDOM,     // ランダム移動（徘徊）
    LOCKON,     // プレイヤー発見
    DIVE,       // 飛び込み攻撃
    APPROACH,   // 接近
    ATTACK,     // 近接攻撃
    COOLDOWN    // 攻撃後の硬直
};

class EnemyAI
{
public:
    EnemyAI();
    ~EnemyAI() = default;

    void Init();
    void Update(CEnemy* pEnemy);
    void FinishAction();   // 攻撃終了などで呼ばれる

private:
    void ChangeState(EnemyAIState newState, CEnemy* pEnemy);

    void UpdateRandom(CEnemy* pEnemy);
    void UpdateLockon(CEnemy* pEnemy);
    void UpdateDive(CEnemy* pEnemy);
    void UpdateApproach(CEnemy* pEnemy);
    void UpdateAttack(CEnemy* pEnemy);
    void UpdateCooldown(CEnemy* pEnemy);

    bool SearchPlayer(CEnemy* pEnemy, float radius);

private:
    EnemyAIState m_State;      // 現在のステート
    int m_Timer;               // 各状態の経過フレーム
    bool m_bDoing;             // 行動中フラグ
};

#endif
