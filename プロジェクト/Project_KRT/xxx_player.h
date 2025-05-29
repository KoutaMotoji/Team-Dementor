//===============================================================================
//
//  �v���C���[����(playerX.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _PLAYERX_H_
#define _PLAYERX_H_

#include "main.h"
#include "character.h"
#include "object2D.h"
#include "modelparts.h"


#include "manager.h"

//�O���錾
class CCTBarUI;
class CButtonUI;
class CCharacter;
class CPlayerMask;

class CPlayerX :public CCharacter
{
public:
	CPlayerX(int nPriority = 1);					//�R���X�g���N�^
	~CPlayerX()override;		//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��

	bool PMove(float fCamRotZ);
	bool PAttackInfo();
	static CPlayerX* Create(D3DXVECTOR3 pos);

	inline D3DXVECTOR3 GetPos() { return CCharacter::GetPos(); };
	inline D3DXVECTOR3 GetMove() { return CCharacter::GetMove(); };
	void SetParry();
	enum
	{
		MOTION_NUTORAL = 0,
		MOTION_WALK,
		MOTION_ATTACK,
		MOTION_JUMP,
		MOTION_LANDING,
		MOTION_PARRY,
		MOTION_PARRY_STAY,
		MOTION_PARRY_ATTACK
	};
private:

	//�X�e�[�^�X�p�萔
	static constexpr int MAX_LIFE = 1000;			//�̗�

	D3DXVECTOR3 m_OldPos;					//�ߋ��̈ʒu
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

	void FloorCollision();					//���Ƃ̓����蔻��
	void EnemyCollision();
	void CamFloorCollision(LPD3DXMESH pMesh);
	bool FloorbumpyMesh(LPD3DXMESH pMesh);
	CCTBarUI* m_pCctBarUI;
	bool m_bAttackCt;
	int m_nPushedKey;
	bool m_bParryWait;
	std::vector<CButtonUI*>m_vButtonUI;
	float m_LastCamDis;
	//========================			�N�I�[�^�j�I���p		====================================
	D3DXMATRIX m_mtxRot;		//��]�}�g���b�N�X(�ۑ��p)
	D3DXQUATERNION m_quat;		//�N�I�[�^�j�I��
	D3DXVECTOR3 m_vecAxis;		//��]���̃x�N�g��
	float m_fValueRot;			//��]��
};



#endif