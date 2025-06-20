//===============================================================================
//
//  �U���̓����蔻��(�\��)�̉���(attack_range.h)
//	����F��|�
// 
//===============================================================================

#ifndef _ATTACK_RANGE_H_
#define _ATTACK_RANGE_H_

#include "main.h"
#include "object3D.h"

#define FVF_ATTACK_RANGE (D3DFVF_XYZ | D3DFVF_DIFFUSE)

// �U���͈͕\���}�l�[�W���[
class CAttackRange : public CObject3D
{
public:
    CAttackRange();
    ~CAttackRange();

    void Init();		//������
    void Uninit();		//�I��
    void Update();		//�X�V
    void Draw();		//�`��
    static CAttackRange* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
    D3DXVECTOR3 m_pos;
    D3DXVECTOR3 m_size;
};

// ��`�`��p�N���X
class CDrawFan : public CObject
{
public:
    CDrawFan();
    ~CDrawFan();

    void Init();		//������
    void Uninit();		//�I��
    void Update();		//�X�V
    void Draw();		//�`��
    void SetPos(D3DXVECTOR3 pos);
    void SetSize(D3DXVECTOR3 size);
    void SetPolygonParam(D3DXVECTOR3 pos, float fHeight, float fWidth);
    static CDrawFan* Create(D3DXVECTOR3 pos);
private:
    LPDIRECT3DTEXTURE9 m_pTextureObject3D;
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffObject3D;
    D3DXVECTOR3 m_pos;
    D3DXVECTOR3 m_rot;
    D3DXVECTOR3 m_size;
    D3DXCOLOR m_col;
    D3DXMATRIX m_mtxWorld;
    float m_fAngle;
    float m_fLength;
    float m_fHeight;
    float m_fWidth;
    float m_fZoom;
};

#endif