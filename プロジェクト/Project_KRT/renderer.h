//===============================================================================
//
//  �`��Ǘ��N���X(renderer.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "scene.h"

class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw(CScene* pScene);
	LPDIRECT3DDEVICE9 GetDevice();
private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_D3DDevice;

	//�t�H�O�p�ϐ�
	float m_fFogStartPos;
	float m_fFogEndPos;
};

#endif