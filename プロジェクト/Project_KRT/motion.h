//===============================================================================
//
//  C++�g����3D(motion.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "main.h"

#define MAX_PARTS	(16)
#define MAX_KEYSET	(16)
#define MAX_MOTION	(8)
class CMotion
{
public:
	CMotion();
	~CMotion();

	CMotion* Create(int MaxModelParts, int KeySetNum,int MotionNum);
private:
	int m_ModelParts;	//���f���p�[�c��
	int m_CurKey;		//���݂̃L�[�ԍ�
	int m_CntMotion;	//���[�V�����J�E���^�[
	int m_CurMotion;	//���݂̃��[�V�����ԍ�
	int m_KeySetNum;	//�L�[�Z�b�g��
	int m_MotionNum;	//���[�V�����ő吔
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
		bool bLoop;
		int nKeyNum;
		KeySet aKetSet[MAX_KEYSET];
	};
	Motion aMotion[MAX_MOTION];

};

#endif