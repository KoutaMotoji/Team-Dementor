//=====================================================================================================================
//
//ゲージの処理[gauge.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "object.h"

//ゲージ
class Gauge : public CObject   //(親)オブジェクト基底
{
public:
	//コンストラクタ
	Gauge(D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size)
	{
		//メンバ変数を初期化する
		this->m_v3Pos = v3Pos;   //位置
		this->m_v2Size = v2Size;   //サイズ
	}

	//デストラクタ
	~Gauge()
	{
	}

	virtual void Init() override = 0;   //初期化
	virtual void Uninit() override = 0;   //終了処理
	virtual void Update() override = 0;   //更新処理
	virtual void Draw() override = 0;   //描画処理
	D3DXVECTOR3 GetPos() { return this->m_v3Pos; };   //位置の取得処理
	D3DXVECTOR2 GetSize() { return this->m_v2Size; };   //サイズの取得処理

private:
	D3DXVECTOR3 m_v3Pos;   //位置
	D3DXVECTOR2 m_v2Size;   //サイズ
};

#endif // !_GAUGE_H_
