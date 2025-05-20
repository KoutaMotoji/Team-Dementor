//===============================================================================
//
//  �v���C���[����(playerX.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _STAGE1_BOSS_H_
#define _STAGE1_BOSS_H_

#include "main.h"
#include "character.h"

#include "manager.h"

//�O���錾

class CG_Gorira :public CCharacter
{
public:
	CG_Gorira();						//�R���X�g���N�^
	~CG_Gorira()override {};		//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��

	static CG_Gorira* Create(D3DXVECTOR3 pos);

	enum
	{
		MOTION_NUTORAL = 0,
		MOTION_WALK,
		MOTION_ATTACK,
		MOTION_JUMP,
		MOTION_LANDING,
	};
private:
	//�X�e�[�^�X�p�萔
	static constexpr int MAX_LIFE = 1000;			//�̗�

	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_OldPos;					//�ߋ��̈ʒu

	void FloorCollision();					//���Ƃ̓����蔻��
	bool m_bAttackCt;
};

#endif