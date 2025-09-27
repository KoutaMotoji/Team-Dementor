//===============================================================================
//
//  �G���G�̍U��AI�N���X(enemy_attack_state.cpp)
//								����F��|� (���C��)
// 
//===============================================================================

#include "enemy_attack_state.h"
#include "player_observer.h"
#include "collision.h"
#include "enemy_ai.h"
#include <random>
#include <cstdio>

// �����p�萔
namespace {
    constexpr float SEARCH_MIN_DIST = 0.0f;
    constexpr float SEARCH_MAX_DIST = 600.0f;
    constexpr int   ATTACK_COOL_FRAMES = 180;   // �U����̃N�[���^�C���i�t���[���j
    constexpr int   DEFAULT_DIVE_FRAMES = 82;   // ���[�V�������v�t���[���i���Ȃ���txt����82�j
    constexpr float DIVE_JUMP_HEIGHT = 80.0f;   // ��яオ�荂��
}

// -------------------------------------------
// Enemy_AI
// -------------------------------------------
void Enemy_AI::AI_Init()
{
    m_Timer = 0;
    m_CoolTime = 0;
    m_bDoing = false;
}

void Enemy_AI::AI_Update([[maybe_unused]] CEnemy* pEnemy)
{
    // �f�o�b�O�F��ԕ\��
    {
        char dbg[256];
        sprintf_s(dbg, "AI_Update: bDoing=%d Cool=%d Timer=%d\n",
            m_bDoing ? 1 : 0, m_CoolTime, m_Timer);
        OutputDebugStringA(dbg);
    }

    // �N�[���^�C�����Ȃ牽�����Ȃ��i�N�[���^�C���������j
    if (m_CoolTime > 0) {
        --m_CoolTime;
        return;
    }

    // �U�����Ȃ牽�����Ȃ��i�U�����I���܂ő҂j
    if (m_bDoing) {
        OutputDebugStringA("AI_Update: skip because m_bDoing=1\n");
        return;
    }

    // �v�l���łȂ���Α҂i�^�C�}�[���f�N�������g�j
    if (!GetIsThinking()) {
        --m_Timer;
        return;
    }

    // �v�l����i�v���C���[���������čs��������j
    SetNextAction(pEnemy);
}

void Enemy_AI::SetNextAction([[maybe_unused]] CEnemy* pEnemy)
{
    if (SearchPlayer(pEnemy))
    {
        OutputDebugStringA("SetNextAction: SearchPlayer==true -> Start Dive\n");
        pEnemy->SetAttackState(std::make_shared<E_Attack_Dive>());
        m_bDoing = true;
    }
    else
    {
        OutputDebugStringA("SetNextAction: SearchPlayer==false\n");
        // �������s���͎��̎v�l���Ԃ�ݒ肵�ĊԊu��u���i�ߕ��זh�~�j
        SetThinkValue();
    }
}

void Enemy_AI::SetThinkValue()
{
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> rand_num(30, 50); // 30~50�t���[���҂�

    m_Timer = rand_num(mt);

    char buf[128];
    sprintf_s(buf, "ThinkValue set: %d\n", m_Timer);
    OutputDebugStringA(buf);
}

bool Enemy_AI::SearchPlayer([[maybe_unused]] CEnemy* pEnemy)
{
    D3DXVECTOR3 playerPos = CPlayerObserver::GetInstance()->GetPlayerPos();
    D3DXVECTOR3 enemyPos = pEnemy->GetPos();  // ���݈ʒu��K���擾

    D3DXVECTOR3 diff = playerPos - enemyPos;
    float dist = D3DXVec3Length(&diff);

    // �f�o�b�O
    char buf[256];
    sprintf_s(buf, "SearchPlayer: Dist=%.2f Enemy(%.1f,%.1f,%.1f) Player(%.1f,%.1f,%.1f)\n",
        dist,
        enemyPos.x, enemyPos.y, enemyPos.z,
        playerPos.x, playerPos.y, playerPos.z);
    OutputDebugStringA(buf);

    return (dist > SEARCH_MIN_DIST && dist < SEARCH_MAX_DIST);
}

void Enemy_AI::FinishAction()
{
    m_bDoing = false;
    m_CoolTime = ATTACK_COOL_FRAMES; // �U����̃N�[���^�C��
    SetThinkValue();                 // ���̎v�l�^�C�}�[���Z�b�g

    OutputDebugStringA("FinishAction: m_bDoing reset to false\n");
    OutputDebugStringA("FinishAction: action finished, cooldown set\n");
}

// ==============================================
// ��э��ݍU���iE_Attack_Dive�j
// ==============================================
void E_Attack_Dive::AttackInit([[maybe_unused]] CEnemy* pEnemy)
{
    // �J�n�ʒu�ƌ��m���̃v���C���[�ʒu��ۑ�
    m_LastPos = pEnemy->GetPos();
    m_LastPlayerPos = CPlayerObserver::GetInstance()->GetPlayerPos();

    // �����Ƌ���
    D3DXVECTOR3 diff = m_LastPlayerPos - m_LastPos;
    float Distance = D3DXVec3Length(&diff);

    // �߂�����^�قړ��ʒu�Ȃ�L�����Z�����Ė߂�
    if (Distance < 1.0f)
    {
        OutputDebugStringA("Dive::Init cancelled - distance too small\n");
        pEnemy->SetAttackState(std::make_shared<E_Attack_None>());
        return;
    }

    // �����x�N�g���iXZ�������j
    D3DXVECTOR3 dir = diff;
    dir.y = 0.0f;
    D3DXVec3Normalize(&m_Dir, &dir);

    // ���[�V�����t���[���ɓ����iTXT��荇�v82�t���[���j
    m_DestFrame = DEFAULT_DIVE_FRAMES;
    if (m_DestFrame < 1) m_DestFrame = 1;
    m_NowFrame = 0;

    // �����i���f���̐��ʂ��ǂ��炩�� +/-PI �𒲐����ĉ������j
    float angle = atan2f(m_Dir.x, m_Dir.z); // ���܂������Ȃ��Ȃ� +D3DX_PI ������
    pEnemy->SetRot({ 0.0f, angle, 0.0f });

    // ���[�V�����ؑ�
    pEnemy->CCharacter::SetNextMotion(CEnemy::MOTION_DIVE);

    // �f�o�b�O
    {
        char dbg[128];
        sprintf_s(dbg, "Dive::Init Dist=%.2f DestFrame=%d\n", Distance, m_DestFrame);
        OutputDebugStringA(dbg);
    }
}

void E_Attack_Dive::AttackUpdate([[maybe_unused]] CEnemy* pEnemy)
{
    // �f�o�b�O���t���[��
    {
        char dbg[128];
        sprintf_s(dbg, "Dive::Update Now=%d / Dest=%d\n", m_NowFrame, m_DestFrame);
        OutputDebugStringA(dbg);
    }

    if (m_NowFrame < m_DestFrame)
    {
        float t = (float)m_NowFrame / (float)m_DestFrame;
        D3DXVECTOR3 newPos = m_LastPos + (m_LastPlayerPos - m_LastPos) * t;
        newPos.y += sinf(D3DX_PI * t) * DIVE_JUMP_HEIGHT;

        // ���݈ʒu���X�V
        pEnemy->SetPos(newPos);

        // ��������Ԃɍ��킹��ꍇ�͍X�V
        float angle = atan2f(m_Dir.x, m_Dir.z) + D3DX_PI; // + D3DX_PI �͕K�v�ȏꍇ����
        pEnemy->SetRot({ 0.0f, angle, 0.0f });

        ++m_NowFrame;
    }
    else
    {
        // Attack �I����
        pEnemy->SetAttackState(std::make_shared<E_Attack_None>());
        pEnemy->CCharacter::SetNextMotion(0);

        if (auto ai = pEnemy->GetEnemy_AI())
        {
            ai->FinishAction();
        }
    }
}

void E_Attack_Dive::AttackFinish([[maybe_unused]] CEnemy* pEnemy)
{
    D3DXVECTOR3 epos = pEnemy->GetPos();
    D3DXVECTOR3 ppos = CPlayerObserver::GetInstance()->GetPlayerPos();
    D3DXVECTOR3 diff = ppos - epos;
    float dist = D3DXVec3Length(&diff);

    char dbg[256];
    sprintf_s(dbg, "Dive::Finish Enemy(%.1f,%.1f,%.1f) Player(%.1f,%.1f,%.1f) Dist=%.2f\n",
        epos.x, epos.y, epos.z,
        ppos.x, ppos.y, ppos.z, dist);
    OutputDebugStringA(dbg);
}

void E_Attack_Dive::SlerpRotatedPosition([[maybe_unused]] CEnemy* pEnemy, float frame)
{
    // �����̉~�ʕ�Ԋ֐��͂��̂܂܎c���Ă����܂��i�K�v�Ȃ�g���j
    D3DXVECTOR3 EnemyPos = m_LastPos;
    D3DXVECTOR3 PlayerPos = m_LastPlayerPos;

    D3DXVECTOR3 C = (EnemyPos + PlayerPos) * 0.5f;
    D3DXVECTOR3 vecA = EnemyPos - C;
    D3DXVECTOR3 vecB = PlayerPos - C;
    D3DXVECTOR3 abXZ = PlayerPos - EnemyPos;
    abXZ.y = 0;
    D3DXVec3Normalize(&abXZ, &abXZ);
    D3DXVECTOR3 axis = D3DXVECTOR3(-abXZ.z, 0.0f, abXZ.x);
    D3DXVec3Normalize(&axis, &axis);
    float dot = D3DXVec3Dot(&vecA, &vecB);
    float lenA = D3DXVec3Length(&vecA);
    float lenB = D3DXVec3Length(&vecB);
    float cosTheta = dot / (lenA * lenB);
    cosTheta = max(-1.0f, min(1.0f, cosTheta));
    float angle = acosf(cosTheta);
    D3DXQUATERNION quatStart(0, 0, 0, 1);
    D3DXQUATERNION quatEnd;
    D3DXQuaternionRotationAxis(&quatEnd, &axis, angle);
    D3DXQUATERNION quatInterp;
    D3DXQuaternionSlerp(&quatInterp, &quatStart, &quatEnd, frame);
    D3DXMATRIX rotMat;
    D3DXMatrixRotationQuaternion(&rotMat, &quatInterp);
    D3DXVECTOR3 rotatedVec;
    D3DXVec3TransformCoord(&rotatedVec, &vecA, &rotMat);
    rotatedVec.y = abs(rotatedVec.y);
    D3DXVECTOR3 result = C + rotatedVec;
    pEnemy->SetPos(result);
}
