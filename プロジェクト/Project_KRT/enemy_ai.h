//===============================================================================
//
//  �G���GAI�Ǘ� (enemy_ai.h)
//                          ����F��|�
//
//===============================================================================

#ifndef _ENEMY_AI_H_
#define _ENEMY_AI_H_

#include "main.h"
#include "enemy.h"

// �GAI�̍s���X�e�[�g
enum class EnemyAIState
{
    RANDOM,     // �����_���ړ��i�p�j�j
    LOCKON,     // �v���C���[����
    DIVE,       // ��э��ݍU��
    APPROACH,   // �ڋ�
    ATTACK,     // �ߐڍU��
    COOLDOWN    // �U����̍d��
};

class EnemyAI
{
public:
    EnemyAI();
    ~EnemyAI() = default;

    void Init();
    void Update(CEnemy* pEnemy);
    void FinishAction();   // �U���I���ȂǂŌĂ΂��

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
    EnemyAIState m_State;      // ���݂̃X�e�[�g
    int m_Timer;               // �e��Ԃ̌o�߃t���[��
    bool m_bDoing;             // �s�����t���O
};

#endif
