//===============================================================================
//
//  �v���C���[����(playerX.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "main.h"
#include "object.h"
#include "modelparts.h"

#include "manager.h"

class CCharacter :public CObject
{
public:
	CCharacter();					//�R���X�g���N�^
	~CCharacter()override;		//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void SetDamageState();
	void ShootBullet();
	void Draw()override;		//�`��

	bool PMove(float fCamRotZ);
	static CCharacter* Create(D3DXVECTOR3 pos);
	inline int GetPLife() { return m_nLife; };

	inline D3DXVECTOR3 GetPos() { return m_pos; };
	inline D3DXVECTOR3 GetMove() { return m_move; };
private:

	//���[�V�����p�萔
	static constexpr int MAX_MODELPARTS = 32;
	static constexpr int MAX_PARTS = 32;
	static constexpr int MAX_KEYSET = 32;
	static constexpr int MAX_MOTION = 16;

	//�X�e�[�^�X�p�萔
	static constexpr int MAX_LIFE = 1000;			//�̗�
	static constexpr float MOVE_JET_SPEED = 3.5f;	//�ړ��X�s�[�h�̐ݒ�
	static constexpr float MOVE_ROBO_SPEED = 2.00f;	//�ړ��X�s�[�h�̐ݒ�

	static constexpr float SCROLL_SPEED = 5.5f;		//�����X�N���[���X�s�[�h�̐ݒ�
	static constexpr float RETICLE_VALUE = 8.5f;	//���e�B�N���̈ړ��M���b�v

	D3DXVECTOR3 m_pos, m_rot, m_size;			//���W�E��]�E�傫��
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_OldPos;					//�ߋ��̈ʒu
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

	void FloorCollision();					//���Ƃ̓����蔻��

	void DamageAdd(int nDmg);				//�_���[�W���Z�A�����m�F

	float m_fWeaponRadius;
	int m_nLife;			//�̗�

	CModelParts* m_apModelParts[MAX_MODELPARTS];

	char* m_pModelFileName[MAX_MODELPARTS];
	int m_ModelParts;	//���f���p�[�c��
	int m_CurKey;		//���݂̃L�[�ԍ�
	int m_CurMotion;	//���݂̃��[�V�����ԍ�
	int m_NextMotion;	//���݂̃��[�V�����ԍ�
	int m_KeySetNum;	//�L�[�Z�b�g��
	int m_MotionNum;	//���[�V�����ő吔
	int m_NowFrame;		//���݂̃t���[��
	struct Key
	{
		//�ʒu
		D3DXVECTOR3 pos;
		//����
		D3DXVECTOR3 rot;
	};
	struct KeySet
	{

		int nFrame;
		Key aKey[MAX_PARTS];
	};
	struct Motion
	{
		int bLoop;
		int nKeyNum;
		KeySet aKetSet[MAX_KEYSET];
	};
	Motion m_aMotion[MAX_MOTION];

	void MotionInit();
	void MotionDataLoad();
	void SetNextMotion(int nNextMotionNum);
	void SetNextKey();
	bool MotionBlending();

	void TransformSound();


	bool m_bBlend;
	bool m_bMotion;
	bool TestUseMeshCollision();

	//========================			�N�I�[�^�j�I���p		====================================
	D3DXMATRIX m_mtxRot;		//��]�}�g���b�N�X(�ۑ��p)
	D3DXQUATERNION m_quat;		//�N�I�[�^�j�I��
	D3DXVECTOR3 m_vecAxis;		//��]���̃x�N�g��
	float m_fValueRot;			//��]��
};

#endif