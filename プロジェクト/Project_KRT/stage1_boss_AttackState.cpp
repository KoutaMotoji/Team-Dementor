//===============================================================================
//
//  �S�����̍U��AI�N���X(stage1_boss_AttackState.cpp)
//								����F���n�O��
// 
//===============================================================================

#include "stage1_boss_AttackState.h"
#include "player_observer.h"
#include "collision.h"

void Gorira_AI::AI_Init()
{

}

void Gorira_AI::AI_Update([[maybe_unused]]CG_Gorira* pGorira)
{
    if (m_bDoing)return;
	if (!GetIsThinking()) {
		--m_Timer;
		return;
	}
	SetNextAction(pGorira);
}

void Gorira_AI::SetNextAction([[maybe_unused]] CG_Gorira* pGorira)
{
	if (SearchPlayer(pGorira))
	{
        pGorira->SetAttackState(std::make_shared<G_Attack_Dive>());
	}
    else
    {
        pGorira->SetAttackState(std::make_shared<G_Attack_Spin>());
    }
    m_bDoing = true;
}

void Gorira_AI::SetThinkValue()
{
	std::random_device rnd;				// �񌈒�I�ȗ���������ŃV�[�h�����@�𐶐�
	std::mt19937 mt(rnd());				//  �����Z���k�c�C�X�^�[��32�r�b�g�ŁA�����͏����V�[�h
	std::uniform_int_distribution<> rand_num(30, 50);     // [30, 50] �͈͂̈�l����

	m_Timer = rand_num(mt);
}

bool Gorira_AI::SearchPlayer([[maybe_unused]] CG_Gorira* pGorira)
{
	CG_Gorira* gorira = pGorira;
	std::shared_ptr<CCollision>pCollision = std::make_shared<CCollision>();

	D3DXVECTOR3 PlayerRadius = {2.0f,2.0f,2.0f};
	D3DXVECTOR3 EnemyRadius = {600.0f,600.0f,600.0f};

	return !(pCollision->SphireCollosion(gorira->GetPos(), CPlayerObserver::GetInstance()->GetPlayerPos(), EnemyRadius, PlayerRadius));
}



//=============================================================================================================
//�ȉ��{�X�s������


// ==================== ��э��ݍU�� ==================== 
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
    pGorira->CCharacter::SetNextMotion(7,false);

    pGorira->CCharacter::SetMotionMag(FrameDig);
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
  
}
void G_Attack_Dive::SlerpRotatedPosition([[maybe_unused]] CG_Gorira* pGorira, float frame)
{
    D3DXVECTOR3 EnemyPos = m_LastPos;
    D3DXVECTOR3 PlayerPos = m_LastPlayerPos;

    // ���S�_C���v�Z
    D3DXVECTOR3 C = (EnemyPos + PlayerPos) * 0.5f;

    // A���璆�S�ւ̃x�N�g��
    D3DXVECTOR3 vecA = EnemyPos - C;
    D3DXVECTOR3 vecB = PlayerPos - C;

    // AB��XZ����
    D3DXVECTOR3 abXZ = PlayerPos - EnemyPos;
    abXZ.y = 0;
    D3DXVec3Normalize(&abXZ, &abXZ);

    // AB�ɐ�����XZ���F(-z, 0, x)
    D3DXVECTOR3 axis = D3DXVECTOR3(-abXZ.z, 0.0f, abXZ.x);
    D3DXVec3Normalize(&axis, &axis);

    // vecA��vecB�̂Ȃ��p�����߂�
    float dot = D3DXVec3Dot(&vecA, &vecB);
    float lenA = D3DXVec3Length(&vecA);
    float lenB = D3DXVec3Length(&vecB);
    float cosTheta = dot / (lenA * lenB);

    if (cosTheta > 1.0f) cosTheta = 1.0f;
    if (cosTheta < -1.0f) cosTheta = -1.0f;

    float angle = acosf(cosTheta); // ���W�A��

    // ��]�N�I�[�^�j�I���쐬�iaxis, angle�j
    D3DXQUATERNION quatStart(0, 0, 0, 1); // �P�ʃN�I�[�^�j�I��
    D3DXQUATERNION quatEnd;
    D3DXQuaternionRotationAxis(&quatEnd, &axis, angle);

    // ���ʐ��`���
    D3DXQUATERNION quatInterp;
    D3DXQuaternionSlerp(&quatInterp, &quatStart, &quatEnd, frame);

    // ��]�s�񐶐�
    D3DXMATRIX rotMat;
    D3DXMatrixRotationQuaternion(&rotMat, &quatInterp);

    // vecA����]
    D3DXVECTOR3 rotatedVec;
    D3DXVec3TransformCoord(&rotatedVec, &vecA, &rotMat);

    rotatedVec.y = abs(rotatedVec.y);

    // ���S�_�ɉ��Z
    D3DXVECTOR3 result = C + rotatedVec;

    pGorira->SetPos(result);
}

// ==================== �X�C���O�U�� ==================== 
void G_Attack_Spin::G_AttackInit([[maybe_unused]] CG_Gorira* pGorira)
{
    D3DXVECTOR3 EnemyPos = pGorira->GetPos();
    D3DXVECTOR3 PlayerPos = CPlayerObserver::GetInstance()->GetPlayerPos();

    D3DXVECTOR3 dir = EnemyPos - PlayerPos;
    D3DXVec3Normalize(&dir, &dir);

    float Yaw = atan2f(dir.x, dir.z);
    pGorira->SetRot({ 0.0f,Yaw,0.0f });

    pGorira->CCharacter::SetNextMotion(, false);
}

void G_Attack_Spin::G_AttackUpdate([[maybe_unused]] CG_Gorira* pGorira)
{

}
void G_Attack_Spin::G_AttackFinish([[maybe_unused]] CG_Gorira* pGorira)
{

}
