//===============================================================================
//
//  �X�e���V���}�X�N�̏���(stencile_mask.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _MASK_H_
#define _MASK_H_

#include "main.h"
#include "object2D.h"

#include "manager.h"
class CPlayerMask : public CObject2D
{
public:
	CPlayerMask(int nPriority = 3) :CObject2D(nPriority) {}
	_forceinline void Init()override {
		CObject::SetType(TYPE_2D_UI);
		CObject2D::Init();
	}
	void Draw()override {
		LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

		CObject2D::Draw();

		pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

		//�X�e���V���}�X�N�̐ݒ莞�ɖ���������Z�o�b�t�@�����Ƃɂ��ǂ�
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
	_forceinline static CPlayerMask* Create()
	{
		CPlayerMask* instance = new CPlayerMask;

		instance->SetPolygonParam({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, SCREEN_HEIGHT, SCREEN_WIDTH, { 1.0f,0.0f,0.0f,1.0f });
		instance->Init();

		return instance;
	}
};

#endif