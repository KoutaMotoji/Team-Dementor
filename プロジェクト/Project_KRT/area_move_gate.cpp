//===============================================================================
//
//  エリア移動用ゲートオブジェクト(area_move_gate.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "area_move_gate.h"
#include "field_manager.h"
#include "player_observer.h"
#include "floor_stone.h"

namespace
{
	float _RADIUS = 100.0f;
}

//==========================================================================================
//初期化処理
//==========================================================================================
void CAreaGate::Init()
{
	CObject::SetType(TYPE_AREAGATE);
	CObjectX::Init();
	SetFirstPosY();
	CField_Manager::GetInstance()->RegistObj(this);
	m_pDebugLine = CDebugLineCylinder::Create(_RADIUS, {0.0f,7.0f,7.0f,1.0f});		//デバッグ用線の生成
}

//==========================================================================================
//更新処理
//==========================================================================================
void CAreaGate::Update()
{
	CObjectX::Update();
	if (ToPlayerCollision())
	{
		if (!m_bPass)
		{
			m_bPass = true;
			CField_Manager::GetInstance()->SetField();
		}
	}
}


//==========================================================================================
//描画処理
//==========================================================================================
void CAreaGate::Draw()
{
	m_pDebugLine->Draw(CObjectX::GetPos());
	CObjectX::Draw();
}

//==========================================================================================
//生成処理
//==========================================================================================
CAreaGate* CAreaGate::Create(D3DXVECTOR3 pos)
{
	CAreaGate* enemy = new CAreaGate;

	enemy->BindModel("data\\MODEL\\AreaMove_obj.x");
	enemy->SetModelParam({ pos.x,-1000.0f,pos.z });
	enemy->Init();
	enemy->SetRot({ 0.0f,0.0f,0.0f });
	return enemy;
}

//==========================================================================================
//プレイヤーが当たり判定内にいるかチェック
//==========================================================================================
bool CAreaGate::ToPlayerCollision()
{
	D3DXVECTOR3 PlayerPos = CPlayerObserver::GetInstance()->GetPlayerPos();

	float LengthX = CObjectX::GetPos().x - PlayerPos.x;
	float LengthZ = CObjectX::GetPos().z - PlayerPos.z;

	return (((LengthX * LengthX) + (LengthZ * LengthZ)) <= (_RADIUS * _RADIUS));
}

//==========================================================================================
//生成された時に地形に位置を沿わせる
//==========================================================================================
void CAreaGate::SetFirstPosY()
{
	// 地形判定
	BOOL  bIsHit = false;
	float fLandDistance;
	DWORD dwHitIndex = 0U;
	float fHitU;
	float fHitV;
	LPD3DXMESH pMesh = nullptr;
	for (int j = 0; j < SET_PRIORITY; ++j) {
		for (int i = 0; i < MAX_OBJECT; ++i) {
			CObject* pObj = CObject::GetObjects(j, i);
			if (pObj == nullptr) continue;
			CObject::TYPE type = pObj->GetType();
			if (type != CObject::TYPE::TYPE_3D_MESHOBJECT) continue;
			CMeshGround* pTest = dynamic_cast<CMeshGround*>(pObj);
			if (pTest == nullptr) continue;
			// 地形判定
			pMesh = pTest->GetMesh();
			D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 objpos = CObjectX::GetPos() - pTest->GetPos();
			D3DXIntersect(pMesh, &objpos, &dir, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, nullptr, nullptr);

			// ----- 接地時処理 -----
			if (bIsHit)
			{
				CObjectX::AddPos({ 0.0f,fLandDistance,0.0f });
				return;
			}
		}
	}
}