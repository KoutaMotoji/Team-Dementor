//===============================================================================
//
//  プレイヤー処理(playerX.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "xxx_player.h"
#include "floor_stone.h"

#include "game.h"

namespace
{
	float Damage_Ratio = 0.2f;
	float _GRAVITY = 4.0f;
	float _MOVE_SPEED = 3.0f;
	float _JUMP_HEIGHT = 120.0f;
};

//==========================================================================================
//コンストラクタ
//==========================================================================================
CPlayerX::CPlayerX() 
{
	
}

//==========================================================================================
//デストラクタ
//==========================================================================================
CPlayerX::~CPlayerX()
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
void CPlayerX::Init()
{

	CObject::SetType(TYPE_3D_PLAYER);						//オブジェクト一括管理用のタイプを設定
	
}

//==========================================================================================
//終了処理
//==========================================================================================
void CPlayerX::Uninit()
{
}

//==========================================================================================
//更新処理
//==========================================================================================
void CPlayerX::Update()
{
	D3DXVECTOR3 CameraPos;		//カメラの座標移動用ローカル変数
	m_OldPos = CObjectX::GetPos();

	FloorCollision();	//プレイヤー移動制限の当たり判定
	PMove(CManager::GetInstance()->GetCamera()->GetRotZ());	//プレイヤー移動関連の処理


	CObjectX::AddPos(m_move);
	
	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.14f;
	m_move.y += (0.0f - m_move.y) * 0.14f;
	m_move.z += (0.0f - m_move.z) * 0.17f;
	CManager::GetInstance()->GetCamera()->SetPlayerPos(CObjectX::GetPos());
}

//==========================================================================================
//描画処理
//==========================================================================================
void CPlayerX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;

	//クオータニオンを作成
	D3DXQuaternionRotationAxis(
		&m_quat,
		&m_vecAxis,
		m_fValueRot);

	//クオータニオンから回転マトリックスを作成
	D3DXMatrixRotationQuaternion(
		&mtxRot,
		&m_quat);
	m_mtxRot = mtxRot;		//回転マトリックスを保存

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//大きさを反映
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
		&m_mtxRot);
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
	pDevice->SetTransform(D3DTS_WORLD,
		&m_mtxWorld);
	CObjectX::Draw();
}

//==========================================================================================
//生成処理
//==========================================================================================
CPlayerX* CPlayerX::Create(D3DXVECTOR3 pos)
{
	CPlayerX* player = new CPlayerX;
	player->Init();
	player->BindModel("data\\MODEL\\P_Model.x");
	player->SetModelParam(pos);
	player->m_move = { 0.0f,0.0f,0.0f };
	player->m_size = { 1.0f,1.0f,1.0f };
	player->m_OldPos = pos;
	return player;
}

//==========================================================================================
//移動処理
//==========================================================================================
bool CPlayerX::PMove(float fCamRotZ)
{
	D3DXVECTOR3 moveDir{};
	float moveYrot{},dashValue{};
	bool bKeyFrag = false;

	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
	{
		moveDir.z += _MOVE_SPEED;
		bKeyFrag = true;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
	{
		moveDir.z -= _MOVE_SPEED;
		bKeyFrag = true;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_A))
	{
		moveDir.x -= _MOVE_SPEED;
		bKeyFrag = true;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_D))
	{
		moveDir.x += _MOVE_SPEED;
		bKeyFrag = true;
	}
	if (!bKeyFrag)
	{
		moveDir.x = CManager::GetInstance()->GetJoypad()->GetJoyStickVecL().x;
		moveDir.z = CManager::GetInstance()->GetJoypad()->GetJoyStickVecL().y;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_SPACE) || CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_A))
	{
		m_move.y += _JUMP_HEIGHT;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetRepeat(DIK_LSHIFT) || CManager::GetInstance()->GetJoypad()->GetRepeat(CJoypad::JOYPAD_B))
	{
		dashValue = 2.0f;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_LSHIFT) || CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_B))
	{
		dashValue = 15.0f;
	}

	moveYrot = atan2f(moveDir.x, moveDir.z) + fCamRotZ;
	
	if (moveDir.x == 0.0f || moveDir.z == 0.0f)
	{
		m_move.y -= _GRAVITY;
		return true;
	}

	CObjectX::SetRot({ 0.0f,moveYrot + D3DX_PI,0.0f });
	m_move.x += sinf(moveYrot) * _MOVE_SPEED;
	m_move.z += cosf(moveYrot) * _MOVE_SPEED;

	m_move.y -= _GRAVITY;

	return true;
}


//==========================================================================================
// プレイヤーの移動制限判定
//==========================================================================================
void CPlayerX::FloorCollision()
{
	if (CObjectX::GetPos().z < -1000)
	{
		CObjectX::SetPos({ CObjectX::GetPos().x, CObjectX::GetPos().y, -1000 });
	}
	else if (CObjectX::GetPos().z > 1000)
	{
		CObjectX::SetPos({ CObjectX::GetPos().x, CObjectX::GetPos().y, 1000 });
	}
	if (CObjectX::GetPos().x < -1200)
	{
		CObjectX::SetPos({ -1200, CObjectX::GetPos().y, CObjectX::GetPos().z });
	}
	else if (CObjectX::GetPos().x > 1200)
	{
		CObjectX::SetPos({ 1200, CObjectX::GetPos().y, CObjectX::GetPos().z });
	}

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
			if (pObj != nullptr) {
				CObject::TYPE type = pObj->GetType();
				if (type == CObject::TYPE::TYPE_3D_MESHOBJECT) {
					CMeshGround* pTest = dynamic_cast<CMeshGround*>(pObj);
					if (pTest != nullptr) {
						pMesh = pTest->GetMesh();
						if (pTest != nullptr) {
							// 地形判定
							pMesh = pTest->GetMesh();
							D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
							D3DXVECTOR3 objpos = CObjectX::GetPos() - pTest->GetPos();
							D3DXIntersect(pMesh, &objpos, &dir, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, nullptr, nullptr);

							// ----- 接地時処理 -----
							if (bIsHit)
							{
								CObjectX::AddPos({ 0.0f, fLandDistance - m_move.y - _GRAVITY,0.0f });
								return;
							}
						}
					}
				}
			}
		}
	}
}

