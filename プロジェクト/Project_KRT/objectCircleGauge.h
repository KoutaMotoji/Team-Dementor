//===============================================================================
//
//  2D円形ゲージクラス(objectCircleGauge.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _OBJECT_CIRCLEGAUGE_H_
#define _OBJECT_CIRCLEGAUGE_H_

#include "main.h"
#include "object.h"

#define D3DFVF_GAUGEVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class CObjectCircleGauge :public CObject
{
public:
    CObjectCircleGauge(int nPriority = 2);
    ~CObjectCircleGauge();
    struct VERTEX
    {
        D3DXVECTOR3 position;
        DWORD color;
        float u, v;
        float rhw;
    };

    static CObjectCircleGauge* Create(float radius);
    void Init();
    void Uninit();
    void Update();
    void Draw();

    void BindTexture(LPDIRECT3DTEXTURE9 pTex);
    void SetGaugePercent(float percent);   // 0.0f ~ 1.0f
    bool GetPercentCharged() const { return m_nPercent >= 1.0f; }
    void SetPolygonParam(D3DXVECTOR3 pos, float radius);
private:
    // =====================
    // メンバ変数
    // =====================
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;
    LPDIRECT3DTEXTURE9 m_pTexture;

    float m_fRadius;
    float m_nPercent;
    D3DXCOLOR m_color;
    D3DXVECTOR3 m_pos;

    int m_nResolution;
};

#endif