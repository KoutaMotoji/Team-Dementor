//===============================================================================
//
//  プレイヤー処理(playerX.h)
//								制作：元地弘汰
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