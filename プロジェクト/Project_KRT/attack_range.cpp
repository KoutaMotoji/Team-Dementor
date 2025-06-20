//===============================================================================
//
//  攻撃の当たり判定(予兆)の可視化(attack_range.cpp)
//	制作：大竹熙
// 
//===============================================================================

#include "attack_range.h"
#include "manager.h"

namespace
{
	const int MAX_VERTEX = 4;
	const int MAX_VERTEX_FAN = 3;
	const int MAX_POLYGON = 2;
};

CAttackRange::CAttackRange() :m_pos{}, m_size{} {

}

CAttackRange::~CAttackRange(){
    Uninit();
}

//==========================================================================================
//初期化処理
//==========================================================================================
void CAttackRange::Init()
{
    CObject3D::Init();
}

//==========================================================================================
//終了処理
//==========================================================================================
void CAttackRange::Uninit(){
    CObject3D::Uninit();
}

//==========================================================================================
//更新処理
//==========================================================================================
void CAttackRange::Update(){
    CObject3D::Update();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CAttackRange::Draw()
{
    CObject3D::Draw();
}

//==========================================================================================
//生成処理
//==========================================================================================
CAttackRange* CAttackRange::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CAttackRange* attackrange = new CAttackRange;
    attackrange->m_pos = pos;
    attackrange->SetPolygonParam(pos, size.x, size.y);

    attackrange->Init();
    return attackrange;
}

CDrawFan::CDrawFan() :m_pos{}, m_size{} {

}

CDrawFan::~CDrawFan(){
    Uninit();
}

//==========================================================================================
//初期化処理
//==========================================================================================
void CDrawFan::Init()
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX_FAN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffObject3D,
		NULL);
	VERTEX_3D* pVtx;	//頂点情報のポインタ

	//頂点バッファをロックして、頂点情報へのポインタを取得
	m_pVtxBuffObject3D->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, 0.0f, m_fHeight);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, 0.0f, m_fHeight);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, 0.0f, -m_fHeight);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, 0.0f, -m_fHeight);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//頂点バッファのアンロック
	m_pVtxBuffObject3D->Unlock();

}

//==========================================================================================
//終了処理
//==========================================================================================
void CDrawFan::Uninit(){
	//頂点バッファの破棄
	if (m_pVtxBuffObject3D != NULL)
	{
		m_pVtxBuffObject3D->Release();
		m_pVtxBuffObject3D = NULL;
	}
}

//==========================================================================================
//更新処理
//==========================================================================================
void CDrawFan::Update(){

}

//==========================================================================================
//描画処理
//==========================================================================================
void CDrawFan::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;
	//ワールドマトリックス
	D3DXMatrixIdentity(&m_mtxWorld);
	//大きさを反映(初期設定された大きさx,zを基準値1.0としたサイズスケーリング)
	D3DXMatrixScaling(&mtxSize,
		m_size.y,
		m_size.x,
		m_size.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxSize);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffObject3D, 0, sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTextureObject3D);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN,
		0,
		MAX_POLYGON);

}

//==========================================================================================
//生成時の初期設定処理
//==========================================================================================
void CDrawFan::SetPolygonParam(D3DXVECTOR3 pos, float fHeight, float fWidth)
{
	m_pos = pos;
	m_fHeight = fHeight;
	m_fWidth = fWidth;
	m_size = { 1.0f,1.0f,1.0f };
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//対角線の長さを算出
	m_fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) / 2.0f;
	//対角線の角度を算出
	m_fAngle = atan2f(m_fWidth, m_fHeight);
}

//==========================================================================================
//生成処理
//==========================================================================================
CDrawFan* CDrawFan::Create(D3DXVECTOR3 pos)
{
    CDrawFan* drawFan = new CDrawFan;
    drawFan->m_pos = pos;
	drawFan->SetPolygonParam(pos, 500.0f, 500.0f);
    drawFan->Init();
    return drawFan;
}