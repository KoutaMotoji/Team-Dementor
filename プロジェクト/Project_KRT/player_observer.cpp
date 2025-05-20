//===============================================================================
//
//  プレイヤー監視クラス(player_observer.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "player_observer.h"
#include "manager.h"

std::shared_ptr<CPlayerObserver> CPlayerObserver::_instance = nullptr;
//======================================================================
//プレイヤー検索
//======================================================================
void CPlayerObserver::PlayerSearch()
{
	if (pPlayer == nullptr)
	{
		for (int j = 0; j < SET_PRIORITY; ++j) {
			for (int i = 0; i < MAX_OBJECT; ++i) {
				CObject* pObj = CObject::GetObjects(j, i);
				if (pObj != nullptr) {
					CObject::TYPE type = pObj->GetType();
					if (type == CObject::TYPE::TYPE_3D_PLAYER) {
						CPlayerX* pP = dynamic_cast<CPlayerX*>(pObj);
						if (pP != nullptr)
						{
							pPlayer = pP;
						}
					}
				}
			}
		}
	}
}

//======================================================================
//確保したプレイヤーを破棄
//======================================================================
void CPlayerObserver::PlayerObsDestroy()
{
	if (pPlayer != nullptr)
	{
		pPlayer = nullptr;
	}
}

//======================================================================
//プレイヤーの座標を取得
//======================================================================
D3DXVECTOR3 CPlayerObserver::GetPlayerPos()
{
	if (pPlayer != nullptr)
	{
		return pPlayer->GetPos();
	}
	return { 0.0f,0.0f,0.0f };
}

//======================================================================
// プレイヤーの移動量を取得
//======================================================================
D3DXVECTOR3 CPlayerObserver::GetPlayerMove()
{
	if (pPlayer != nullptr)
	{
		return pPlayer->GetMove();
	}
	return { 0.0f,0.0f,0.0f };
}

//======================================================================
// プレイヤーの体力を取得
//======================================================================
int CPlayerObserver::GetPlayerLife()
{
	if (pPlayer != nullptr)
	{
		return 0;
	}
	return 0;
}

//======================================================================
// プレイヤーのポインタを取得
//======================================================================
CPlayerX* CPlayerObserver::GetPlayer()
{
	if (pPlayer != nullptr)
	{
		return pPlayer;
	}
	return nullptr;
}