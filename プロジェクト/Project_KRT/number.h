//===============================================================================
//
//  �X�R�A�\���̐����|���S���\��(number.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "object2D.h"


class CNumber :public CObject2D
{
public:
	CNumber(int nPriority = 6);		//�R���X�g���N�^
	~CNumber()override;				//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��

	static CNumber* Create(D3DXVECTOR3 pos,float Height,float Width);

	void SetNum(int Num) { 
		m_nNum = Num;	
		CObject2D::SetAnim({ (float)m_nNum,CObject2D::GetAnim().y });
	};							//���g�̌��̐������擾�A�A�j���[�V�������ړ�
private:
	int m_nNum;
};

#endif