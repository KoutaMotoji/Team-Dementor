//===============================================================================
//
//  3D�I�u�W�F�N�g���N���X(object3D.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"
#include "object.h"

class CObject3D :public CObject
{
public:
	CObject3D(int nPriority = 2);				//�R���X�g���N�^
	~CObject3D()override;		//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��
	void Draw(D3DXMATRIX SetmtxRot);		//�`��


	D3DXVECTOR3 GetPos();
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void AddSize(float value);
	void SetSize(float size);
	float GetSize();
	void SetRot(D3DXVECTOR3 rot);
	static CObject3D* Create(D3DXVECTOR3 pos);
	void SetPolygonParam(D3DXVECTOR3 pos, float fHeight, float fWidth);					//�����ݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);	//������e�N�X�`�� 
private:
	LPDIRECT3DTEXTURE9 m_pTextureObject3D;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffObject3D;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DXCOLOR m_col;
	D3DXMATRIX m_mtxWorld;
	static const int MAX_VERTEX;
	static const int MAX_POLYGON;
	float m_fAngle;
	float m_fLength;
	float m_fHeight;
	float m_fWidth;
	float m_fZoom;
	static const float MAX_OBJ3DHEIGHT;
	static const float MAX_OBJ3DWIDTH;
};

#endif