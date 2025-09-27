//===============================================================================
//
//  雑魚敵の攻撃AIクラス(enemy_attack_state.cpp)
//								制作：大竹熙 (改修版)
// 
//===============================================================================

#include "enemy_attack_state.h"
#include "player_observer.h"
#include "collision.h"
#include "enemy_ai.h"
#include <random>
#include <cstdio>

// 調整用定数
namespace {
    constexpr float SEARCH_MIN_DIST = 0.0f;
    constexpr float SEARCH_MAX_DIST = 600.0f;
    constexpr int   ATTACK_COOL_FRAMES = 180;   // 攻撃後のクールタイム（フレーム）
    constexpr int   DEFAULT_DIVE_FRAMES = 82;   // モーション合計フレーム（あなたのtxtだと82）
    constexpr float DIVE_JUMP_HEIGHT = 80.0f;   // 飛び上がり高さ
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
    // デバッグ：状態表示
    {
        char dbg[256];
        sprintf_s(dbg, "AI_Update: bDoing=%d Cool=%d Timer=%d\n",
            m_bDoing ? 1 : 0, m_CoolTime, m_Timer);
        OutputDebugStringA(dbg);
    }

    // クールタイム中なら何もしない（クールタイムを消化）
    if (m_CoolTime > 0) {
        --m_CoolTime;
        return;
    }

    // 攻撃中なら何もしない（攻撃が終わるまで待つ）
    if (m_bDoing) {
        OutputDebugStringA("AI_Update: skip because m_bDoing=1\n");
        return;
    }

    // 思考中でなければ待つ（タイマーをデクリメント）
    if (!GetIsThinking()) {
        --m_Timer;
        return;
    }

    // 思考する（プレイヤーを検索して行動を決定）
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
        // 検索失敗時は次の思考時間を設定して間隔を置く（過負荷防止）
        SetThinkValue();
    }
}

void Enemy_AI::SetThinkValue()
{
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> rand_num(30, 50); // 30~50フレーム待つ

    m_Timer = rand_num(mt);

    char buf[128];
    sprintf_s(buf, "ThinkValue set: %d\n", m_Timer);
    OutputDebugStringA(buf);
}

bool Enemy_AI::SearchPlayer([[maybe_unused]] CEnemy* pEnemy)
{
    D3DXVECTOR3 playerPos = CPlayerObserver::GetInstance()->GetPlayerPos();
    D3DXVECTOR3 enemyPos = pEnemy->GetPos();  // 現在位置を必ず取得

    D3DXVECTOR3 diff = playerPos - enemyPos;
    float dist = D3DXVec3Length(&diff);

    // デバッグ
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
    m_CoolTime = ATTACK_COOL_FRAMES; // 攻撃後のクールタイム
    SetThinkValue();                 // 次の思考タイマーをセット

    OutputDebugStringA("FinishAction: m_bDoing reset to false\n");
    OutputDebugStringA("FinishAction: action finished, cooldown set\n");
}

// ==============================================
// 飛び込み攻撃（E_Attack_Dive）
// ==============================================
void E_Attack_Dive::AttackInit([[maybe_unused]] CEnemy* pEnemy)
{
    // 開始位置と検知時のプレイヤー位置を保存
    m_LastPos = pEnemy->GetPos();
    m_LastPlayerPos = CPlayerObserver::GetInstance()->GetPlayerPos();

    // 差分と距離
    D3DXVECTOR3 diff = m_LastPlayerPos - m_LastPos;
    float Distance = D3DXVec3Length(&diff);

    // 近すぎる／ほぼ同位置ならキャンセルして戻す
    if (Distance < 1.0f)
    {
        OutputDebugStringA("Dive::Init cancelled - distance too small\n");
        pEnemy->SetAttackState(std::make_shared<E_Attack_None>());
        return;
    }

    // 方向ベクトル（XZを向く）
    D3DXVECTOR3 dir = diff;
    dir.y = 0.0f;
    D3DXVec3Normalize(&m_Dir, &dir);

    // モーションフレームに同期（TXTより合計82フレーム）
    m_DestFrame = DEFAULT_DIVE_FRAMES;
    if (m_DestFrame < 1) m_DestFrame = 1;
    m_NowFrame = 0;

    // 向き（モデルの正面がどちらかで +/-PI を調整して下さい）
    float angle = atan2f(m_Dir.x, m_Dir.z); // うまく向かないなら +D3DX_PI を試す
    pEnemy->SetRot({ 0.0f, angle, 0.0f });

    // モーション切替
    pEnemy->CCharacter::SetNextMotion(CEnemy::MOTION_DIVE);

    // デバッグ
    {
        char dbg[128];
        sprintf_s(dbg, "Dive::Init Dist=%.2f DestFrame=%d\n", Distance, m_DestFrame);
        OutputDebugStringA(dbg);
    }
}

void E_Attack_Dive::AttackUpdate([[maybe_unused]] CEnemy* pEnemy)
{
    // デバッグ毎フレーム
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

        // 現在位置を更新
        pEnemy->SetPos(newPos);

        // 向きも補間に合わせる場合は更新
        float angle = atan2f(m_Dir.x, m_Dir.z) + D3DX_PI; // + D3DX_PI は必要な場合だけ
        pEnemy->SetRot({ 0.0f, angle, 0.0f });

        ++m_NowFrame;
    }
    else
    {
        // Attack 終了時
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
    // 既存の円弧補間関数はそのまま残しておきます（必要なら使う）
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
