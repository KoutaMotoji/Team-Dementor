//===============================================================================
//
//  ゴリラの攻撃AIクラス(stage1_boss_AttackState.cpp)
//								制作：元地弘汰
// 
//===============================================================================

#include "stage1_boss_AttackState.h"
#include "player_observer.h"
#include "collision.h"

int G_Attack_Normal::m_ContNum = 0;

namespace
{
    const std::vector<float> SearchRadius = {
         300.0f,
         500.0f
    };
    enum
    {
        ATTACK_SHORTRANGE_ = 1,
        ATTACK_MIDRANGE_,
    };
}

void Gorira_AI::AI_Init()
{

}

void Gorira_AI::AI_Update([[maybe_unused]] CG_Gorira* pGorira)
{
    if (m_bDoing)return;
    if (!GetIsThinking()) {
        pGorira->AddRot({ 0.0f,-m_LeapRotValue,0.0f });
        --m_Timer;
        return;
    }
    SetNextAction(pGorira);
}

void Gorira_AI::SetNextAction([[maybe_unused]] CG_Gorira* pGorira)
{
    pGorira->SetState(std::make_shared<Stage1Boss_Attack>());
    m_bDoing = true;
    int SearchNum = SearchPlayer(pGorira);
    if (SearchNum != 0)
    {
        switch (SearchNum)
        {
        case ATTACK_SHORTRANGE_:
            pGorira->SetAttackState(std::make_shared<G_Attack_Normal>());
            break;
        case ATTACK_MIDRANGE_:
            pGorira->SetAttackState(std::make_shared<G_Attack_Spin>());
            break;
        default:
            break;
        }
    }
    else
    {
        pGorira->SetAttackState(std::make_shared<G_Attack_Dive>());
    }
}

void Gorira_AI::SetThinkValue()
{
    std::random_device rnd;				// 非決定的な乱数生成器でシード生成機を生成
    std::mt19937 mt(rnd());				//  メルセンヌツイスターの32ビット版、引数は初期シード
    std::uniform_int_distribution<> rand_num(20, 40);     // [20, 40] 範囲の一様乱数

    m_Timer = rand_num(mt);
}

void Gorira_AI::LookPlayer([[maybe_unused]] CG_Gorira* pGorira)
{
    D3DXVECTOR3 EnemyPos = pGorira->GetPos();
    D3DXVECTOR3 PlayerPos = CPlayerObserver::GetInstance()->GetPlayerPos();

    D3DXVECTOR3 dir = EnemyPos - PlayerPos;
    D3DXVec3Normalize(&dir, &dir);

    float Yaw = atan2f(dir.x, dir.z);
    float EnemyYaw = pGorira->GetRot().y;
    m_LeapRotValue = (EnemyYaw - Yaw) / m_Timer;
}

int Gorira_AI::SearchPlayer([[maybe_unused]] CG_Gorira* pGorira)
{
    CG_Gorira* gorira = pGorira;
    std::shared_ptr<CCollision>pCollision = std::make_shared<CCollision>();

    D3DXVECTOR3 PlayerRadius = { 2.0f,2.0f,2.0f };
    for (int i = 0; i < 2; ++i)
    {
        D3DXVECTOR3 EnemyRadius = { SearchRadius[i],SearchRadius[i],SearchRadius[i] };
        if (pCollision->SphireCollosion(gorira->GetPos(), CPlayerObserver::GetInstance()->GetPlayerPos(), EnemyRadius, PlayerRadius))return i + 1;
    }
    return 0;
}



//=============================================================================================================
//以下ボス行動制御
// ==================== 通常攻撃 ==================== 
void G_Attack_Normal::G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)
{
    ++m_ContNum;
    if (m_ContNum > 2)
    {
        m_ContNum = 0;
        pGorira->SetAttackState(std::make_shared<G_Attack_BackStep>());
        return;
    }
    pGorira->SetMotionMag(0.25f);
    pGorira->CCharacter::SetNextMotion(2, false);
}

void G_Attack_Normal::G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)
{
    pGorira->SetMotionMag(1.0f);
    pGorira->SetState(std::make_shared<Stage1Boss_Nutoral>());

    //pGorira->SetAttackState(std::make_shared<G_Attack_Spin>());

}
// ==================== 飛び込み攻撃 ==================== 
void G_Attack_Dive::G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)
{
    D3DXVECTOR3 EnemyPos = pGorira->GetPos();
    D3DXVECTOR3 PlayerPos = CPlayerObserver::GetInstance()->GetPlayerPos();
    D3DXVECTOR3 PosMinuts = PlayerPos - EnemyPos;
    float Distance = sqrtf((PosMinuts.x * PosMinuts.x) + (PosMinuts.z * PosMinuts.z));

    m_DestFrame = Distance * 0.1f;
    float FrameDig = m_DestFrame / 194.0f;
    m_NowFrame = 0;
    m_LastPos = EnemyPos;
    m_LastPlayerPos = PlayerPos;
    pGorira->CCharacter::SetNextMotion(9, false);

    pGorira->CCharacter::SetMotionMag(FrameDig);
    CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS1_SWING);

}

void G_Attack_Dive::G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira)
{
    D3DXVECTOR3 EnemyPos = m_LastPos;
    D3DXVECTOR3 PlayerPos = CPlayerObserver::GetInstance()->GetPlayerPos();

    D3DXVECTOR3 dir = EnemyPos - PlayerPos;
    D3DXVec3Normalize(&dir, &dir);

    float Yaw = atan2f(dir.x, dir.z);

    float SetLerp = (1.0f / m_DestFrame) * m_NowFrame;

    SlerpRotatedPosition(pGorira, SetLerp);
    pGorira->SetRot({ 0.0f,Yaw,0.0f });

    ++m_NowFrame;
    if (m_DestFrame <= m_NowFrame)
    {
        pGorira->CCharacter::SetMotionMag(1.0f);
        pGorira->SetAttackState(std::make_shared<G_Attack_None>());
        pGorira->CCharacter::SetNextMotion(0);
    }
}
void G_Attack_Dive::G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)
{
    pGorira->SetState(std::make_shared<Stage1Boss_Nutoral>());
}
void G_Attack_Dive::SlerpRotatedPosition([[maybe_unused]] CG_Gorira* pGorira, float frame)
{
    D3DXVECTOR3 EnemyPos = m_LastPos;
    D3DXVECTOR3 PlayerPos = m_LastPlayerPos;

    // 中心点Cを計算
    D3DXVECTOR3 C = (EnemyPos + PlayerPos) * 0.5f;

    // Aから中心へのベクトル
    D3DXVECTOR3 vecA = EnemyPos - C;
    D3DXVECTOR3 vecB = PlayerPos - C;

    // ABのXZ成分
    D3DXVECTOR3 abXZ = PlayerPos - EnemyPos;
    abXZ.y = 0;
    D3DXVec3Normalize(&abXZ, &abXZ);

    // ABに垂直なXZ軸：(-z, 0, x)
    D3DXVECTOR3 axis = D3DXVECTOR3(-abXZ.z, 0.0f, abXZ.x);
    D3DXVec3Normalize(&axis, &axis);

    // vecAとvecBのなす角を求める
    float dot = D3DXVec3Dot(&vecA, &vecB);
    float lenA = D3DXVec3Length(&vecA);
    float lenB = D3DXVec3Length(&vecB);
    float cosTheta = dot / (lenA * lenB);

    if (cosTheta > 1.0f) cosTheta = 1.0f;
    if (cosTheta < -1.0f) cosTheta = -1.0f;

    float angle = acosf(cosTheta); // ラジアン

    // 回転クオータニオン作成（axis, angle）
    D3DXQUATERNION quatStart(0, 0, 0, 1); // 単位クオータニオン
    D3DXQUATERNION quatEnd;
    D3DXQuaternionRotationAxis(&quatEnd, &axis, angle);

    // 球面線形補間
    D3DXQUATERNION quatInterp;
    D3DXQuaternionSlerp(&quatInterp, &quatStart, &quatEnd, frame);

    // 回転行列生成
    D3DXMATRIX rotMat;
    D3DXMatrixRotationQuaternion(&rotMat, &quatInterp);

    // vecAを回転
    D3DXVECTOR3 rotatedVec;
    D3DXVec3TransformCoord(&rotatedVec, &vecA, &rotMat);

    rotatedVec.y = abs(rotatedVec.y);

    // 中心点に加算
    D3DXVECTOR3 result = C + rotatedVec;

    pGorira->SetPos(result);
}

// ==================== スイング攻撃 ==================== 
void G_Attack_Spin::G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)
{
    D3DXVECTOR3 EnemyPos = pGorira->GetPos();
    D3DXVECTOR3 PlayerPos = CPlayerObserver::GetInstance()->GetPlayerPos();

    D3DXVECTOR3 dir = EnemyPos - PlayerPos;
    D3DXVec3Normalize(&dir, &dir);

    float Yaw = atan2f(dir.x, dir.z);
    pGorira->SetRot({ 0.0f,Yaw,0.0f });

    pGorira->CCharacter::SetNextMotion(8, false);
}

void G_Attack_Spin::G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira)
{

}
void G_Attack_Spin::G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)
{
    pGorira->SetState(std::make_shared<Stage1Boss_Nutoral>());
}

// ==================== バクステ攻撃 ==================== 
void G_Attack_BackStep::G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)
{
    pGorira->CCharacter::SetNextMotion(12, false);
}

void G_Attack_BackStep::G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)
{
    pGorira->SetState(std::make_shared<Stage1Boss_Nutoral>());
}