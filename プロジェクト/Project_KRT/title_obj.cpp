
#include "title_obj.h"
#include "inimanager.h"
#include "collision.h"

namespace
{

	struct _FILENAME	//ファイルのパス管理構造体
	{
		std::string config;		//ファイルのパス
		std::string section;	//セクション名
		std::string keyword;	//キーワード名
	};
	_FILENAME st_filename = {				//プレイヤーのモデル・モーション用ファイルパス
		"data\\TEXT\\Config.ini",
		 "ModelData",
		 "TitlePlayerMotion"
	};
	std::string GROUND_FILENAME = "data\\MODEL\\title_field.x";
	std::string TREE_FILENAME = "data\\TEXTURE\\Tree000.png";

	D3DXVECTOR3 T_PLAYER_POS = { 100.0f,-110.0f,0.0f };
	D3DXVECTOR3 T_FIELD_POS = { 0.0f,500.0f,0.0f };
	float TREE_RADIUS = 200.0f;
};

//==========================================================================================
//コンストラクタ
//==========================================================================================
CT_Player::CT_Player(int nPriority) :CCharacter(nPriority)
{

}

//==========================================================================================
//デストラクタ
//==========================================================================================
CT_Player::~CT_Player()
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
void CT_Player::Init()
{
	CObject::SetType(TYPE_3D_TITLEOBJ);						//オブジェクト一括管理用のタイプを設定
	CCharacter::Init();
	CCharacter::MotionDataLoad(CiniManager::GetInstance()->GetINIData(st_filename.config, st_filename.section, st_filename.keyword));	//iniファイルから設定されてるプレイヤーの読み込み
	CCharacter::SetPos(T_PLAYER_POS);
	CCharacter::AddRot({ 0.0f,-1.56,0.0f });
}

//==========================================================================================
//終了処理
//==========================================================================================
void CT_Player::Uninit()
{

	CCharacter::Uninit();
}

//==========================================================================================
//更新処理
//==========================================================================================
void CT_Player::Update()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN) ||
		CManager::GetInstance()->GetJoypad()->GetTrigger(CJoypad::JOYPAD_A))
	{
		CCharacter::SetNextMotion(MOTION_ACTION);
	}
	CCharacter::Update();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CT_Player::Draw()
{
	CCharacter::Draw();
}

//==========================================================================================
//生成処理
//==========================================================================================
CT_Player* CT_Player::Create()
{
	CT_Player* player = new CT_Player;
	player->Init();
	player->SetMove({ 0.0f,0.0f,0.0f });
	return player;
}

//==========================================================================================
// モーション終了時に呼ばれる関数(オーバーライド)
//==========================================================================================
bool  CT_Player::EndMotion()
{

	return true;
}

CT_Graound::CT_Graound(int nPriority) :CObjectX(nPriority)
{

}

CT_Graound::~CT_Graound()
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
void CT_Graound::Init()
{
	CObject::SetType(TYPE_3D_TITLEMESH);
	CObjectX::Init();
}

//==========================================================================================
//描画処理
//==========================================================================================
void CT_Graound::Draw()
{
	CObjectX::Draw();
}

//==========================================================================================
//生成処理
//==========================================================================================
CT_Graound* CT_Graound::Create()
{
	CT_Graound* enemy = new CT_Graound;
	enemy->BindModel(GROUND_FILENAME.c_str());
	enemy->SetModelParam(T_FIELD_POS);
	enemy->Init();
	return enemy;
}

CTreeBillboard::CTreeBillboard(int nPriority) :CBillboard(nPriority)
{
}

CTreeBillboard::~CTreeBillboard()
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
void CTreeBillboard::Init()
{
	CObject::SetType(TYPE_BILLBOARD);
	CBillboard::Init();
	//テクスチャの登録・割り当て
	int nIdx = CManager::GetInstance()->GetTexture()->Regist(TREE_FILENAME.c_str());
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx), { 1,1 });		//横5、縦3に分割
}

//==========================================================================================
//終了処理
//==========================================================================================
void CTreeBillboard::Uninit()
{
	CBillboard::Uninit();
}

//==========================================================================================
//更新処理
//==========================================================================================
void CTreeBillboard::Update()
{

	CBillboard::Update();
}

void CTreeBillboard::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//アルファテスト設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CBillboard::Draw();

	//通常の合成に戻す設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


//==========================================================================================
//生成処理
//==========================================================================================
CTreeBillboard* CTreeBillboard::Create(D3DXVECTOR3 pos)
{
	CTreeBillboard* tree = new CTreeBillboard();

	tree->SetPolygonParam(pos, TREE_RADIUS, TREE_RADIUS, { 1.0f,1.0f,1.0f,1.0f });
	tree->Init();
	tree->AddPos({ 0.0f,-1000.0f,0.0f });
	tree->SetPosGround(TREE_RADIUS);
	return tree;
}

//==========================================================================================
//地形メッシュに沿って位置を合わせる処理
//==========================================================================================
void CTreeBillboard::SetPosGround(float HalfRadius)
{
	std::shared_ptr<CCollision> pCollision = std::make_shared<CCollision>();
	D3DXVECTOR3 dir = { 0.0f,1.0f,0.0f };
	float Distance = 0;

	LPD3DXMESH pMesh = nullptr;
	for (int j = 0; j < SET_PRIORITY; j++) {
		for (int i = 0; i < MAX_OBJECT; i++) {
			CObject* pObj = CObject::GetObjects(j, i);
			if (pObj == nullptr) continue;
			CObject::TYPE type = pObj->GetType();
			if (type != CObject::TYPE::TYPE_3D_TITLEMESH) continue;
			CT_Graound* pTest = dynamic_cast<CT_Graound*>(pObj);
			if (pTest == nullptr) continue;
			pMesh = pTest->GetMesh();
			D3DXVECTOR3 pos = CBillboard::GetPos();

			D3DXVECTOR3 objpos = pos - pTest->GetPos();
			float ChedkDis = 2000.0f;
			// ----- 接地時処理 -----
			if (pCollision->MeshToIntersectCollision(&Distance, pMesh, objpos, dir, ChedkDis))
			{
				CBillboard::AddPos({ 0.0f,Distance + HalfRadius,0.0f });
				return;
			}
		}
	}

}