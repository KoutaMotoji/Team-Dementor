//===============================================================================
//
//  ジャスパ用エフェクト(parrycrit_effect.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _PARRYCRITEFF_H_
#define _PARRYCRITEFF_H_

#include "main.h"
#include "billboard.h"
#include "manager.h"

class CParryCritEff :public CBillboard
{
public:
	CParryCritEff():m_nTime(0){};				//コンストラクタ
	~CParryCritEff()override {};		//デストラクタ
	inline void Init()override {
		int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\effect000.png");
		BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), { 4,4 });
		CObject::SetType(TYPE_BILLBOARD);
		CBillboard::Init();
	}		//初期化
	void Uninit()override {};		//終了
	_forceinline void Update()override
	{
		if (m_nTime > 2)	{
			m_nTime = 0;
			if (CBillboard::GetAnim().x >= 3)	{
				if (CBillboard::GetAnim().y >= 3)	{
					Release();
					return;
				}
				else{
					CBillboard::SetAnim({ 0.0f,CBillboard::GetAnim().y });
					CBillboard::AddAnim({ 0, 1 });
				}
			}
			else{
				CBillboard::AddAnim({ 1,0 });
			}

			D3DXVECTOR2 Anim = CBillboard::GetAnim();
			Anim = Anim;
		}
		else	{
			++m_nTime;
		}
		CBillboard::Update();
	}	//更新
	void Draw()override {

		CBillboard::Draw();
	}		//描画
	static CParryCritEff* Create(D3DXVECTOR3 pos) {
		CParryCritEff* Effect = new CParryCritEff;

		Effect->SetPolygonParam(pos, 160.0f, 220.0f);
		Effect->Init();
		Effect->m_nTime = 0;
		return Effect;
	}
private:
	int m_nTime;
};

#endif