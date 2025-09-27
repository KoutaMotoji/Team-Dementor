//===============================================================================
//
//  装備の処理(weapom.cpp)
//					制作：大竹熙
// 
//===============================================================================

#include "weapon.h"

#include "manager.h"
#include "game.h"

namespace 
{
	float ROTATE_SPEED = 0.05f;   // 回転速度（ラジアン / フレーム）
	float FLOAT_SPEED = 0.05f;  // 上下移動の速さ
	float FLOAT_RANGE = 0.5f;  // 上下移動の幅
}

CWeapon::CWeapon(int nPriority) :CObjectX(nPriority)
{

}

CWeapon::~CWeapon()
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
void CWeapon::Init()
{
	D3DXVECTOR3 pos = GetPos();
	pos.y = -600.0f;  // 地面のちょい上に固定
	SetPos(pos);

	m_baseY = pos.y;

	CObject::SetType(TYPE_WEAPON);
	CObjectX::Init();
}

//==========================================================================================
//終了処理
//==========================================================================================
void CWeapon::Uninit()
{
	CObjectX::Uninit();
}

//==========================================================================================
//更新処理
//==========================================================================================
void CWeapon::Update()
{
	if (m_bEquipped) return;

	CObjectX::Update();

	// 回転
	D3DXVECTOR3 rot = GetRot();
	rot.y += ROTATE_SPEED;
	if (rot.y > D3DX_PI * 2.0f) rot.y -= D3DX_PI * 2.0f;
	SetRot(rot);

	// 上下移動
	m_floatTime += FLOAT_SPEED;
	D3DXVECTOR3 pos = GetPos();
	pos.y = m_baseY + sinf(m_floatTime) * FLOAT_RANGE;
	SetPos(pos);
}

//==========================================================================================
//描画処理
//==========================================================================================
void CWeapon::Draw()
{
	if (m_bEquipped) return;

	CObjectX::Draw();
}

//==========================================================================================
//生成処理
//==========================================================================================
CWeapon* CWeapon::Create(D3DXVECTOR3 pos)
{
	CWeapon* weapon = new CWeapon;
	weapon->BindModel("data\\MODEL\\G_riraWeapon\\G_riraWeapon.x");
	weapon->SetModelParam(pos);
	weapon->Init();
	return weapon;
}