//===============================================================================
//
//  �G���A�ړ��p�Q�[�g�I�u�W�F�N�g(area_move_gate.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _AREA_GATE_H_
#define _AREA_GATE_H_

#include "objectX.h"
#include "debug_line.h"

class CAreaGate : public CObjectX
{
public:
	CAreaGate() :m_bPass(false){};				//�R���X�g���N�^
	~CAreaGate()override {};		//�f�X�g���N�^
	void Init()override;		//������
	void Update()override;		//�X�V
	void Draw()override;		//�`��
	static CAreaGate* Create(D3DXVECTOR3 pos);
protected:

private:
	std::shared_ptr<CDebugLine>m_pDebugLine;
	bool ToPlayerCollision();
	void SetFirstPosY();
	bool m_bPass;
};

#endif