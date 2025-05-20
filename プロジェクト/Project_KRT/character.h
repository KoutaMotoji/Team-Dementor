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

	void Draw()override;		//�`��

	static CCharacter* Create(D3DXVECTOR3 pos);

	inline D3DXVECTOR3 GetPos() { return m_pos; }				//���W�擾
	inline void AddPos(D3DXVECTOR3 pos) { m_pos += pos; }		//���W�ړ�
	inline void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }		//���W�ύX
	inline D3DXVECTOR3 GetRot() { return m_rot; }				//�p�x�擾
	inline void AddRot(D3DXVECTOR3 rot) { m_rot += rot; }		//�p�x�ړ�	
	inline void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

	inline D3DXVECTOR3 GetMove() { return m_move; };
	inline int GetNowMotion() { return m_CurMotion; }
	inline int GetNextMotion() { return m_NextMotion; }

	void MotionDataLoad(std::string filename);
	void SetNextMotion(int nNextMotionNum);
	inline std::vector<CModelParts*> GetVecModelParts() {
		return m_apModelParts;
	}
private:
	D3DXVECTOR3 m_pos, m_rot, m_size;			//���W�E��]�E�傫��
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

	void FloorCollision();					//���Ƃ̓����蔻��


	int m_nLife;			//�̗�

	std::vector<CModelParts*> m_apModelParts;

	std::vector<char*> m_pModelFileName;
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
		std::vector<Key>aKey;
	};
	struct Motion
	{
		int bLoop;
		int nKeyNum;
		std::vector<KeySet>aKetSet;
	};
	std::vector<Motion>m_aMotion;

	void MotionInit();
	void SetNextKey();
	bool MotionBlending();

	bool m_bBlend;
	bool m_bMotion;

	//========================			�N�I�[�^�j�I���p		====================================
	D3DXMATRIX m_mtxRot;		//��]�}�g���b�N�X(�ۑ��p)
	D3DXQUATERNION m_quat;		//�N�I�[�^�j�I��
	D3DXVECTOR3 m_vecAxis;		//��]���̃x�N�g��
	float m_fValueRot;			//��]��
};

#endif