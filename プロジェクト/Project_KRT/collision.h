//===============================================================================
//
//  �����蔻�菈���N���X(collision.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"

class CCollision
{
public:
	CCollision();
	~CCollision();

	bool CircleCollosion(D3DXVECTOR3 MainPos, D3DXVECTOR3 SubPos, D3DXVECTOR3 MainRadius, D3DXVECTOR3 SubRadious);	//�~�`�����蔻��
	bool SphireCollosion(D3DXVECTOR3 MainPos, D3DXVECTOR3 SubPos, D3DXVECTOR3 MainRadius, D3DXVECTOR3 SubRadious);	//�~�`�����蔻��
	bool CylinderCollosion(D3DXVECTOR3 MainPos, D3DXVECTOR3 SubPos, D3DXVECTOR3 MainRadius, D3DXVECTOR3 SubRadious);	//�~�`�����蔻��

	bool MeshToIntersectCollision(LPD3DXMESH pMesh, D3DXVECTOR3 pos, D3DXVECTOR3 dir, float CheckDistance);			//���C�ƃ��b�V���̌�������
	bool MeshToIntersectCollision(float* Distance, LPD3DXMESH pMesh, D3DXVECTOR3 pos, D3DXVECTOR3 dir, float CheckDistance);			//���C�ƃ��b�V���̌�������
	bool MeshToIntersectCollision(LPD3DXMESH mesh, D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXMATRIX mtx, float CheckDistance);		//���b�V�����ړ��E��]���������̏������܂ރI�[�o�[���[�h
};

class CHitCircle
{
public:
	inline CHitCircle() :m_ParentNum(0),
		m_Radius({ 0.0f,0.0f,0.0f }),
		m_pos({ 0.0f,0.0f,0.0f }),
		m_startF(0),
		m_endF(0),
		m_MotionNum(0),
		m_bEnable(false),
		m_bInvincible(false)
	{}
	~CHitCircle() = default;

	inline void SetEnable() { m_bEnable = true; }
	inline void SetDisable() { m_bEnable = false; }
	inline bool GetEnable() { return m_bEnable; }

	inline void SetInvincible(bool hit) { m_bInvincible = hit; }
	inline bool GetInvincible() { return m_bInvincible; }

	inline int GetMotionNum() { return m_MotionNum; }
	inline int GetStart() { return m_startF; }
	inline int GetEnd() { return m_endF; }
	inline D3DXVECTOR3 GetPos() { return m_pos; }				//���[�J�����W�擾
	inline D3DXVECTOR3 GetRadius() { return m_Radius; }			//���a�擾
	inline int GetParentNum() { return m_ParentNum; }			//�����蔻�������e�̃C���f�b�N�X�ԍ�
	inline static std::shared_ptr<CHitCircle> Create(D3DXVECTOR3 Radius, D3DXVECTOR3 pos, int ParentNum, int StartF, int EndF, int MotionNum) {
		std::shared_ptr<CHitCircle> instance = std::make_shared<CHitCircle>();
		instance->m_pos = pos;
		instance->m_Radius = Radius;
		instance->m_ParentNum = ParentNum;
		instance->m_startF = StartF;
		instance->m_endF = EndF;
		instance->m_MotionNum = MotionNum;
		return instance;
	}
	_forceinline D3DXVECTOR3 CalcMtxPos(D3DXMATRIX mtx)
	{
		D3DXMATRIX SetMtx{}, mtxTrans{};

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&SetMtx);
		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			m_pos.x,
			m_pos.y,
			m_pos.z);
		D3DXMatrixMultiply(&SetMtx,
			&SetMtx,
			&mtxTrans);
		D3DXMatrixMultiply(&SetMtx,
			&SetMtx,
			&mtx);
		D3DXVECTOR3 mtxPos = {
			SetMtx._41,
			SetMtx._42,
			SetMtx._43
		};
		return mtxPos;
	}
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_Radius;
	int m_ParentNum, m_startF, m_endF, m_MotionNum;
	bool m_bEnable;
	bool m_bInvincible;
};

#endif 
