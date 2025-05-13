//===============================================================================
//
//  �ۉe�p����(shadow.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "object3D.h"

static constexpr float DEF_RADIUS = 70.0f;

class CShadow :public CObject3D
{
public:
	CShadow(int nPriority = 1) :CObject3D(nPriority),m_fValueRot(0){}				//�R���X�g���N�^
	~CShadow()override = default;		//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override { CObject3D::Uninit(); }		//�I��
	void Update()override { CObject3D::Update(); }		//�X�V
	void Draw()override;		//�`��

	static CShadow* Create(D3DXVECTOR3 pos);
	static CShadow* Create(D3DXVECTOR3 pos, float radius);	//�T�C�Y�w��p�I�[�o�[���[�h

	void SetShadowGround(D3DXVECTOR3 pos);

private:
	//=====================			�N�I�[�^�j�I���p		====================================
	D3DXMATRIX m_mtxRot;		//��]�}�g���b�N�X(�ۑ��p)
	D3DXQUATERNION m_quat;		//�N�I�[�^�j�I��
	D3DXVECTOR3 m_vecAxis;		//��]���̃x�N�g��
	float m_fValueRot;			//��]��	
};

#endif