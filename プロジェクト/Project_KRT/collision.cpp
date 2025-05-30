//===============================================================================
//
//  �����蔻��Ǘ��N���X(collision.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "collision.h"

CCollision::CCollision()
{

}

CCollision::~CCollision()
{

}

//==========================================================================================
//�~�`�����蔻��
//==========================================================================================
bool CCollision::CircleCollosion(D3DXVECTOR3 MainPos, D3DXVECTOR3 SubPos, D3DXVECTOR3 MainRadius, D3DXVECTOR3 SubRadious)
{
	float fLengthX = MainPos.x - SubPos.x;
	float fLengthY = MainPos.y - SubPos.y;

	float CenterDistance = sqrtf((fLengthX * fLengthX) + (fLengthY * fLengthY));
	float fAngle = ((MainRadius.x + SubRadious.x) + (MainRadius.y + MainRadius.y)) * 0.5f;

	if (CenterDistance <= fAngle)
	{
		return true;
	}

	return false;
}

//==========================================================================================
//���`�����蔻��
//==========================================================================================
bool CCollision::SphireCollosion(D3DXVECTOR3 MainPos, D3DXVECTOR3 SubPos, D3DXVECTOR3 MainRadius, D3DXVECTOR3 SubRadious)
{
	float fLengthX = MainPos.x - SubPos.x;
	float fLengthY = MainPos.y - SubPos.y;
	float fLengthZ = MainPos.z - SubPos.z;
	float fRadiusM, fRadiusS;
	fRadiusM = MainRadius.x;
	fRadiusS = SubRadious.x;

	if ((fLengthX * fLengthX) + (fLengthY * fLengthY) + (fLengthZ * fLengthZ) <= ((fRadiusM + fRadiusS) * (fRadiusM + fRadiusS)))
	{
		return true;
	}

	return false;
}

//==========================================================================================
//�~�������蔻��
//==========================================================================================
bool CCollision::CylinderCollosion(D3DXVECTOR3 MainPos, D3DXVECTOR3 SubPos, D3DXVECTOR3 MainRadius, D3DXVECTOR3 SubRadious)
{
	float fLengthX = MainPos.x - SubPos.x;
	float fLengthY = MainPos.y - SubPos.y;
	float fLengthZ = MainPos.z - SubPos.z;
	float fRadiusM, fRadiusS;
	fRadiusM = MainRadius.x;
	fRadiusS = SubRadious.x;

	if ((fLengthX * fLengthX) + (fLengthZ * fLengthZ) <= ((fRadiusM + fRadiusS) * (fRadiusM + fRadiusS)))
	{
		return true;
	}

	return false;
}


//==========================================================================================
//��΂������C�ƃ��b�V���̔���
//==========================================================================================
bool CCollision::MeshToIntersectCollision(LPD3DXMESH pMesh, D3DXVECTOR3 pos, D3DXVECTOR3 dir, float CheckDistance)
{
	// �n�`����
	BOOL  bIsHit = false;
	float fLandDistance;
	DWORD dwHitIndex = 0U;
	float fHitU;
	float fHitV;

	D3DXIntersect(pMesh, &pos, &dir, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, nullptr, nullptr);

	return (bIsHit && fLandDistance <= CheckDistance);
}

//==========================================================================================
//��΂������C�ƃ��b�V���̔���(�ړ��E��]���������̏������܂ރI�[�o�[���[�h)
//==========================================================================================
bool CCollision::MeshToIntersectCollision(LPD3DXMESH mesh,D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXMATRIX mtx, float CheckDistance)
{
	// �n�`����
	BOOL  bIsHit = false;
	float fLandDistance;
	DWORD dwHitIndex = 0U;
	float fHitU;
	float fHitV;

	LPD3DXMESH pMesh = mesh;
	D3DXMATRIX mWorld;
	D3DXVECTOR3 vStartl;
	D3DXVECTOR3 vDirl;
	D3DXVECTOR3 vEnd;

	vEnd = pos + dir;
	D3DXMATRIX objMtx = mtx;

	// ���C�𓖂Ă�Ώۂ̃}�g���b�N�X�̋t�s����擾���A�n�_�ƏI�_�̍��W�ɑ΂��č��W�ϊ����s���A�ʒu�E��]�E�傫���̕�Ԃ�����
	D3DXMatrixInverse(&mWorld, NULL, &objMtx);
	D3DXVec3TransformCoord(&vStartl, &pos, &mWorld);
	D3DXVec3TransformCoord(&vEnd, &vEnd, &mWorld);

	vDirl = vEnd - vStartl;

	D3DXIntersect(pMesh, &vStartl, &vDirl, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, nullptr, nullptr);

	return (bIsHit && fLandDistance <= CheckDistance);
}

//==========================================================================================
//��΂������C�ƃ��b�V���̔���(����������n���I�[�o�[���[�h)
//==========================================================================================
bool CCollision::MeshToIntersectCollision(float* Distance,LPD3DXMESH pMesh, D3DXVECTOR3 pos, D3DXVECTOR3 dir, float CheckDistance)
{
	// �n�`����
	BOOL  bIsHit = false;
	float fLandDistance;
	DWORD dwHitIndex = 0U;
	float fHitU;
	float fHitV;

	D3DXIntersect(pMesh, &pos, &dir, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, nullptr, nullptr);
	*Distance = fLandDistance;
	return (bIsHit && fLandDistance <= CheckDistance);
}