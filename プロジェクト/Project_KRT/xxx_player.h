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
	CPlayerX();					//�R���X�g���N�^
	~CPlayerX()override;		//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��

	bool PMove(float fCamRotZ);
	bool PAttackInfo();
	static CPlayerX* Create(D3DXVECTOR3 pos);

	inline D3DXVECTOR3 GetPos() { return CCharacter::GetPos(); };
	inline D3DXVECTOR3 GetMove() { return m_move; };
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

	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_OldPos;					//�ߋ��̈ʒu
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

	void FloorCollision();					//���Ƃ̓����蔻��
	bool FloorbumpyMesh(LPD3DXMESH pMesh);
	CCTBarUI* m_pCctBarUI;
	bool m_bAttackCt;
	int m_nPushedKey;
	bool m_bParryWait;
	std::vector<CButtonUI*>m_vButtonUI;
	std::shared_ptr<CPlayerMask> m_playerMask2D;
	//========================			�N�I�[�^�j�I���p		====================================
	D3DXMATRIX m_mtxRot;		//��]�}�g���b�N�X(�ۑ��p)
	D3DXQUATERNION m_quat;		//�N�I�[�^�j�I��
	D3DXVECTOR3 m_vecAxis;		//��]���̃x�N�g��
	float m_fValueRot;			//��]��
};

class CPlayerMask : public CObject2D
{
public:
	_forceinline void Init()override {
		CObject::SetType(TYPE_2D_UI);
		CObject2D::Init();
	}
	_forceinline static std::shared_ptr<CPlayerMask> Create()
	{
		std::shared_ptr<CPlayerMask> instance = std::make_shared<CPlayerMask>();

		instance->SetPolygonParam({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, SCREEN_HEIGHT, SCREEN_WIDTH, {1.0f,0.4,0.4f,1.0f});
		instance->Init();

		return instance;
	}
};

#endif