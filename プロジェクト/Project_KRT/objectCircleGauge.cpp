//===============================================================================
//
//  2D円形ゲージクラス(objectCircleGauge.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "objectCircleGauge.h"

#include "manager.h"

CObjectCircleGauge::CObjectCircleGauge(int nPriority) : CObject(nPriority),
                                        m_pVtxBuffer(nullptr), m_pTexture(nullptr),
                                        m_fRadius(100.0f), m_nPercent(1.0f), m_color(D3DXCOLOR(1, 1, 1, 1)),
                                        m_nResolution(60), m_pos({0.0f,0.0f,0.0f}), m_bGaugeRotate(false)
{
}

CObjectCircleGauge::~CObjectCircleGauge()
{
    Uninit();
}

void CObjectCircleGauge::Init()
{
    LPDIRECT3DDEVICE9 pDevice;
    //デバイスの取得
    pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    const int vertexCount = m_nResolution + 2;

    pDevice->CreateVertexBuffer(sizeof(VERTEX) * vertexCount,
                                    D3DUSAGE_WRITEONLY,
                                    D3DFVF_GAUGEVERTEX,
                                   D3DPOOL_MANAGED,
                                   &m_pVtxBuffer,
                                    NULL);
    
    VERTEX* pVtx;
    m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);
    
    float cx = m_fRadius;
    float cy = m_fRadius;

    pVtx[0] = { { cx, cy, 0.0f },1.0f, m_color, {0.5f, 0.5f} };

    for (int i = 0; i <= m_nResolution; ++i)
    {
        float t = static_cast<float>(i) / m_nResolution;
        float angle;
        if (m_bGaugeRotate) angle = -D3DX_PI / 2 - (2.0f * D3DX_PI * m_nPercent * t);
        else  angle = -D3DX_PI / 2 + (2.0f * D3DX_PI * m_nPercent * t);
        float x = cx + cosf(angle) * m_fRadius;
        float y = cy + sinf(angle) * m_fRadius;

        float u = 0.5f + cosf(angle) * 0.5f;
        float v = 0.5f + sinf(angle) * 0.5f;

        pVtx[i + 1] = { { x, y, 0.0f },1.0f, m_color, {u, v}  };
    }

    m_pVtxBuffer->Unlock();
}

void CObjectCircleGauge::Uninit()
{
    if (m_pVtxBuffer) {
        m_pVtxBuffer->Release();
        m_pVtxBuffer = nullptr;
    }
}

void CObjectCircleGauge::Update()
{
    VERTEX* pVtx;
    m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

    float cx = m_fRadius;
    float cy = m_fRadius;

    pVtx[0] = { { cx + m_pos.x, cy + m_pos.y, 0.0f },1.0f, m_color, {0.5f, 0.5f} };

    for (int i = 0; i <= m_nResolution; ++i)
    {
        float t = static_cast<float>(i) / m_nResolution;
        float angle;
        if(m_bGaugeRotate) angle = -D3DX_PI / 2 - (2.0f * D3DX_PI * m_nPercent * t);
        else  angle = -D3DX_PI / 2 + (2.0f * D3DX_PI * m_nPercent * t);

        float x = cx + cosf(angle) * m_fRadius;
        float y = cy + sinf(angle) * m_fRadius;

        float u = 0.5f + cosf(angle) * 0.5f;
        float v = 0.5f + sinf(angle) * 0.5f;
        x += m_pos.x;
        y += m_pos.y;

        pVtx[i + 1] = { {x, y, 0.0f },1.0f, m_color, {u, v }  };
    }

    m_pVtxBuffer->Unlock();
}

void CObjectCircleGauge::Draw()
{
    LPDIRECT3DDEVICE9 pDevice;
    //デバイスの取得
    pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
    pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//カリング両面に

    pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX));

    pDevice->SetFVF(D3DFVF_GAUGEVERTEX);

    pDevice->SetTexture(0, m_pTexture);

    pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN,
                             0,
                             m_nResolution);
    pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//カリング戻し

}


//==========================================================================================
//テクスチャの設定(テクスチャのポインタ)
//==========================================================================================
void CObjectCircleGauge::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
    m_pTexture = pTex;
}

//==========================================================================================
//生成処理
//==========================================================================================
CObjectCircleGauge* CObjectCircleGauge::Create(float radius)
{
    CObjectCircleGauge* gauge = new CObjectCircleGauge();
    gauge->m_fRadius = radius;
    gauge->Init();
    gauge->m_bGaugeRotate = false;
    return gauge;
}


//==========================================================================================
//生成処理
//==========================================================================================
CObjectCircleGauge* CObjectCircleGauge::Create(float radius,bool RotateReverse)
{
    CObjectCircleGauge* gauge = new CObjectCircleGauge();
    gauge->m_fRadius = radius;
    gauge->Init();
    gauge->m_bGaugeRotate = RotateReverse;
    return gauge;
}

//==========================================================================================
//ゲージの割合算出
//==========================================================================================
void CObjectCircleGauge::SetGaugePercent(float percent)
{
    m_nPercent = max(0.0f, min(1.0f, percent));
}

//==========================================================================================
//生成時の初期設定処理
//==========================================================================================
void CObjectCircleGauge::SetPolygonParam(D3DXVECTOR3 pos,float radius)
{
    m_pos = pos;
    m_fRadius = radius;

}