//=====================================================================================================================
//
//塗り部分の処理[fill.cpp]
// Author MurataShinnosuke
//
//=====================================================================================================================
#include "fill.h"
#include "manager.h"
#include "gauge.h"

//=====================================================================================================================
//初期化処理
//=====================================================================================================================
void Fill::Init()
{
	//デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファを生成する
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&this->m_pVtxBuffer,
		NULL);
}

//=====================================================================================================================
//終了処理
//=====================================================================================================================
void Fill::Uninit()
{
	//頂点バッファを確認する
	if (this->m_pVtxBuffer != nullptr)
	{//頂点バッファがある場合
		//頂点バッファを破棄する
		this->m_pVtxBuffer->Release();
		this->m_pVtxBuffer = nullptr;
	}
}

//=====================================================================================================================
//更新処理
//=====================================================================================================================
void Fill::Update()
{
	//頂点座標をロックして、頂点情報へのポインタを取得する
	VERTEX_2D* pVtx;   //頂点座標
	this->m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標を設定する
	D3DXVECTOR3 v3Pos = this->m_pGauge->GetPos();   //位置の取得
	D3DXVECTOR2 v2Size = this->m_pGauge->GetSize();   //サイズの取得
	pVtx[0].pos = { v3Pos.x - (v2Size.x * 0.5f), v3Pos.y - (v2Size.y * 0.5f), 0.0f };
	pVtx[1].pos = { v3Pos.x + (v2Size.x * 0.5f * this->m_fRatio), v3Pos.y - (v2Size.y * 0.5f), 0.0f };
	pVtx[2].pos = { v3Pos.x - (v2Size.x * 0.5f), v3Pos.y + (v2Size.y * 0.5f), 0.0f };
	pVtx[3].pos = { v3Pos.x + (v2Size.x * 0.5f * this->m_fRatio), v3Pos.y + (v2Size.y * 0.5f), 0.0f };

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーを設定する
	pVtx[0].col = this->m_color;
	pVtx[1].col = this->m_color;
	pVtx[2].col = this->m_color;
	pVtx[3].col = this->m_color;

	//テクスチャ座標を設定する
	pVtx[0].tex = { 0.0f, 0.0f };
	pVtx[1].tex = { 1.0f, 0.0f };
	pVtx[2].tex = { 0.0f, 1.0f };
	pVtx[3].tex = { 1.0f, 1.0f };

	//頂点バッファをアンロックする
	this->m_pVtxBuffer->Unlock();
}

//=====================================================================================================================
//描画処理
//=====================================================================================================================
void Fill::Draw()
{
	//デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定する
	pDevice->SetStreamSource(0, this->m_pVtxBuffer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットを設定する
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャを設定する
	pDevice->SetTexture(0, nullptr);

	//ポリゴンを描画する
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}