//===============================================================================
//
//  エリア移動用ゲートオブジェクト(area_move_gate.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _AREA_GATE_H_
#define _AREA_GATE_H_

#include "objectX.h"
#include "debug_line.h"

class CAreaGate : public CObjectX
{
public:
	CAreaGate() :m_bPass(false){};				//コンストラクタ
	~CAreaGate()override {};		//デストラクタ
	void Init()override;		//初期化
	void Update()override;		//更新
	void Draw()override;		//描画
	static CAreaGate* Create(D3DXVECTOR3 pos);
protected:

private:
	std::shared_ptr<CDebugLine>m_pDebugLine;
	bool ToPlayerCollision();
	void SetFirstPosY();
	bool m_bPass;
};

#endif