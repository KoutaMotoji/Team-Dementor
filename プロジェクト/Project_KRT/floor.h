//===============================================================================
//
//  ��p�|���S������(sky_bg.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _FLOOR_H_
#define _FLOOR_H_

#include "main.h"
#include "object3D.h"


class CFloor :public CObject3D
{
public:
	CFloor();					//�R���X�g���N�^
	~CFloor()override;			//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��

	static CFloor* Create(D3DXVECTOR3 pos);

private:
	static constexpr float FLOOR_SIZE = 1000.0f;
};



#endif