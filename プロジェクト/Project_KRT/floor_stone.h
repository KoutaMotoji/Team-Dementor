//===============================================================================
//
//  �n�`���b�V���̏���(mesh_ground.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _FLOOR_STONE_H_
#define _FLOOR_STONE_H_

#include "main.h"
#include "objectX.h"

class CMeshGround :public CObjectX
{
public:
	CMeshGround(int nPriority = 0);				//�R���X�g���N�^
	~CMeshGround()override;		//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��
	static CMeshGround* Create(D3DXVECTOR3 pos);

protected:

private:
	int m_mode;
};

#endif