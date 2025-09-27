//===============================================================================
//
//  �G���GAI�Ǘ� (enemy_ai.cpp)
//                          ����F��|�
//
//===============================================================================

#include "enemy_ai.h"
#include "enemy_attack_state.h"
#include "player_observer.h"
#include "collision.h"

EnemyAI::EnemyAI(): m_State(EnemyAIState::RANDOM),m_Timer(0),m_bDoing(false)
{

}

void EnemyAI::Init()
{
    m_State = EnemyAIState::RANDOM;
    m_Timer = 0;
    m_bDoing = false;
}

void EnemyAI::Update(CEnemy* pEnemy)
{
    if (!pEnemy) return;

    switch (m_State)
    {
    case EnemyAIState::RANDOM:    UpdateRandom(pEnemy); break;
    case EnemyAIState::LOCKON:    UpdateLockon(pEnemy); break;
    case EnemyAIState::DIVE:      UpdateDive(pEnemy); break;
    case EnemyAIState::APPROACH:  UpdateApproach(pEnemy); break;
    case EnemyAIState::ATTACK:    UpdateAttack(pEnemy); break;
    case EnemyAIState::COOLDOWN:  UpdateCooldown(pEnemy); break;
    }
    ++m_Timer;
}

void EnemyAI::FinishAction()
{
    m_bDoing = false;
}

//--------------------------------------
// ��Ԑ؂�ւ�
//--------------------------------------
void EnemyAI::ChangeState(EnemyAIState newState, CEnemy* pEnemy)
{
    m_State = newState;
    m_Timer = 0;
    m_bDoing = false;

    if (!pEnemy) return;

    switch (newState)
    {
    case EnemyAIState::RANDOM:
        // �������Ȃ��iMove() ���ŏ����j
        break;

    case EnemyAIState::LOCKON:
        // ��������
    {
        D3DXVECTOR3 dir = CPlayerObserver::GetInstance()->GetPlayerPos() - pEnemy->GetPos();
        float yaw = atan2f(dir.x, dir.z);
        pEnemy->SetRot({ 0.0f, yaw, 0.0f });
    }
    break;

    case EnemyAIState::DIVE:
        pEnemy->SetAttackState(std::make_shared<E_Attack_Dive>());
        break;

    case EnemyAIState::APPROACH:
        // �ڋߎ��̃��[�V����
        pEnemy->CCharacter::SetNextMotion(1);
        break;

    case EnemyAIState::ATTACK:
        break;

    case EnemyAIState::COOLDOWN:
        // �d�� �� ���[�V�����߂�
        pEnemy->CCharacter::SetNextMotion(0);
        break;
    }
}

//--------------------------------------
// �e�X�e�[�g�̏���
//--------------------------------------
void EnemyAI::UpdateRandom(CEnemy* pEnemy)
{
    // CEnemy::Move() �Ƀ����_���ړ��͎����ς�
    if (SearchPlayer(pEnemy, 200.0f))
    {
        ChangeState(EnemyAIState::LOCKON, pEnemy);
    }
}

void EnemyAI::UpdateLockon(CEnemy* pEnemy)
{
    if (m_Timer > 30) // 0.5�b���炢���Ă����э���
    {
        ChangeState(EnemyAIState::DIVE, pEnemy);
    }
    else if (!SearchPlayer(pEnemy, 250.0f))
    {
        ChangeState(EnemyAIState::RANDOM, pEnemy); // ��������
    }
}

void EnemyAI::UpdateDive(CEnemy* pEnemy)
{
    if (!m_bDoing)
    {
        m_bDoing = true;
        // Dive �� AttackUpdate ���ňړ����������� AI �� FinishAction ���Ă΂��z��
    }

    if (!SearchPlayer(pEnemy, 300.0f))
    {
        ChangeState(EnemyAIState::RANDOM, pEnemy);
    }
    else if (!m_bDoing)
    {
        ChangeState(EnemyAIState::APPROACH, pEnemy);
    }
}

void EnemyAI::UpdateApproach(CEnemy* pEnemy)
{
    // �v���C���[�ɋ߂Â�
    D3DXVECTOR3 dir = CPlayerObserver::GetInstance()->GetPlayerPos() - pEnemy->GetPos();
    float dist = D3DXVec3Length(&dir);

    if (dist > 250.0f)
    {
        ChangeState(EnemyAIState::RANDOM, pEnemy); // ���ꂽ�����
        return;
    }

    if (dist < 80.0f)
    {
        ChangeState(EnemyAIState::ATTACK, pEnemy);
    }
    else
    {
        D3DXVec3Normalize(&dir, &dir);
        pEnemy->SetPos(pEnemy->GetPos() + dir * 5.0f);
        float yaw = atan2f(dir.x, dir.z);
        pEnemy->SetRot({ 0.0f, yaw, 0.0f });
    }
}

void EnemyAI::UpdateAttack(CEnemy* pEnemy)
{
    if (!m_bDoing)
    {
        m_bDoing = true;
    }

    if (!SearchPlayer(pEnemy, 250.0f))
    {
        ChangeState(EnemyAIState::RANDOM, pEnemy);
    }
    else if (!m_bDoing)
    {
        ChangeState(EnemyAIState::COOLDOWN, pEnemy);
    }
}

void EnemyAI::UpdateCooldown(CEnemy* pEnemy)
{
    if (m_Timer > 60) // 1�b�N�[���_�E��
    {
        if (SearchPlayer(pEnemy, 200.0f))
            ChangeState(EnemyAIState::LOCKON, pEnemy);
        else
            ChangeState(EnemyAIState::RANDOM, pEnemy);
    }
}

//--------------------------------------
// �v���C���[�T��
//--------------------------------------
bool EnemyAI::SearchPlayer(CEnemy* pEnemy, float radius)
{
    if (!pEnemy) return false;
    auto pCollision = std::make_shared<CCollision>();

    D3DXVECTOR3 playerRadius = { 2.0f, 2.0f, 2.0f };
    D3DXVECTOR3 enemyRadius = { radius, radius, radius };

    return pCollision->SphireCollosion(
        pEnemy->GetPos(),
        CPlayerObserver::GetInstance()->GetPlayerPos(),
        enemyRadius,
        playerRadius
    );
}
