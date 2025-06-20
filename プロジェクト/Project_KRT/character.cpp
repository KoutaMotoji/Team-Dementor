//===============================================================================
//
//  プレイヤー処理(character.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "character.h"
#include "floor_stone.h"


namespace
{
	float Damage_Ratio = 0.2f;
	float _RADIUS = 200.0f;
};

//==========================================================================================
//コンストラクタ
//==========================================================================================
CCharacter::CCharacter(int nPriority) :CObject(nPriority),
						m_nLife(1000),
						m_bMotion(false),
						m_bBlend(false),
						m_NowAllFrame(0),
						m_move( { 0.0f,0.0f,0.0f }),
						m_rot ( { 0.0f,0.0f,0.0f }),
						m_size ( { 1.0f,1.0f,1.0f }),
						m_Radius({ _RADIUS ,_RADIUS ,_RADIUS })
{

}

//==========================================================================================
//デストラクタ
//==========================================================================================
CCharacter::~CCharacter()
{

}

//==========================================================================================
//初期化処理
//==========================================================================================
void CCharacter::Init()
{
	MotionInit();		//モーションの初期設定
}

//==========================================================================================
//終了処理
//==========================================================================================
void CCharacter::Uninit()
{
	for (auto& e : m_apModelParts)
	{
		e->Uninit();
	}
}

//==========================================================================================
//更新処理
//==========================================================================================
void CCharacter::Update()
{
	if (!MotionBlending())	//モーションブレンド中か判断
	{//モーションブレンド中でなければ通常のモーション再生
		SetNextKey();
	}
	AddPos(m_move);

	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.14f;
	m_move.y += (0.0f - m_move.y) * 0.14f;
	m_move.z += (0.0f - m_move.z) * 0.17f;
}

//==========================================================================================
//描画処理
//==========================================================================================
void CCharacter::Draw()
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
	for (auto& e : m_apModelParts)
	{
		e->Draw();
	}
	int nCnt{};
	for (auto& e : m_pHitCircle)
	{
		if (e->GetEnable()) {
			D3DXVECTOR3 pos = e->CalcMtxPos(m_apModelParts[e->GetParentNum()]->GetWorldMatrix());
			m_pDebugCircle[nCnt]->Draw(pos);
		}
		++nCnt;
	}
}

//==========================================================================================
//生成処理
//==========================================================================================
CCharacter* CCharacter::Create(D3DXVECTOR3 pos)
{
	CCharacter* charactor = new CCharacter;

	charactor->m_pos = pos;
	charactor->Init();

	return charactor;
}


//==========================================================================================
// プレイヤーの移動制限判定
//==========================================================================================
void CCharacter::FloorCollision()
{

}

//==========================================================================================
//モーションの初期化処理
//==========================================================================================
void CCharacter::MotionInit()
{
	m_CurMotion = 0;
	m_CurKey = 0;
	m_NowFrame = 0;
	m_NowAllFrame = 0;
}

//==========================================================================================
//次のモーションに移行する処理
//==========================================================================================
void CCharacter::SetNextMotion(int nNextMotionNum)
{
	if (m_NextMotion == nNextMotionNum)
	{
		return;
	}
	m_NextMotion = nNextMotionNum;
	m_NowFrame = 0;
	m_NowAllFrame = 0;
	m_bBlend = true;
}
//==========================================================================================
//次のモーションに移行する処理(モーションブレンド)
//==========================================================================================
void CCharacter::SetNextMotion(int nNextMotionNum,bool bBlend)
{
	if (m_NextMotion == nNextMotionNum)
	{
		return;
	}
	m_NextMotion = nNextMotionNum;
	m_NowFrame = 0;
	m_NowAllFrame = 0;
	m_bBlend = bBlend;
}
//==========================================================================================
//次のキーのモーション処理
//==========================================================================================
void CCharacter::SetNextKey()
{
	//現在の位置・角度
	D3DXVECTOR3 NowPos = {};
	D3DXVECTOR3 NowRot = {};

	//次の位置・角度
	D3DXVECTOR3 NextPos = {};
	D3DXVECTOR3 NextRot = {};

	//動きの差分を求める用
	D3DXVECTOR3 DifPos = {};
	D3DXVECTOR3 DifRot = {};

	//計算用
	D3DXVECTOR3 DigitPos = {};
	D3DXVECTOR3 DigitRot = {};

	int nNowKey = m_CurKey;
	int nNowMotion = m_CurMotion;
	int nNextKey = (m_CurKey + 1) % m_aMotion[nNowMotion].nKeyNum;
	float fRatioFrame = (float)m_NowFrame / (float)m_aMotion[nNowMotion].aKetSet[nNowKey].nFrame;
	int nCntParts = 0;
	++m_NowAllFrame;
	int nCnt{};
	for (auto& e : m_pHitCircle)
	{
		if (e->GetMotionNum() == nNowMotion) {
			if (m_NowAllFrame >= e->GetStart() && m_NowAllFrame <= e->GetEnd()) {
				e->SetEnable();
			}
		}
		else {
			e->SetDisable();
		}
		++nCnt;
	}
	for (auto& e : m_apModelParts)
	{
		//現在の向きと位置の情報
		NowPos = m_aMotion[nNowMotion].aKetSet[nNowKey].aKey[nCntParts].pos;
		NowRot = m_aMotion[nNowMotion].aKetSet[nNowKey].aKey[nCntParts].rot;

		//次のキーの情報
		NextPos = m_aMotion[nNowMotion].aKetSet[nNextKey].aKey[nCntParts].pos;
		NextRot = m_aMotion[nNowMotion].aKetSet[nNextKey].aKey[nCntParts].rot;

		//差分を求める
		DifPos = NextPos - NowPos;
		DifRot = NextRot - NowRot;

		//-3.14～3.14の間を超える場合の修正
		if (DifRot.x >= D3DX_PI)
		{
			DifRot.x -= D3DX_PI * 2;
		}
		if (DifRot.y >= D3DX_PI)
		{
			DifRot.y -= D3DX_PI * 2;
		}
		if (DifRot.z >= D3DX_PI)
		{
			DifRot.z -= D3DX_PI * 2;
		}
		if (DifRot.x <= -D3DX_PI)
		{
			DifRot.x += D3DX_PI * 2;
		}
		if (DifRot.y <= -D3DX_PI)
		{
			DifRot.y += D3DX_PI * 2;
		}
		if (DifRot.z <= -D3DX_PI)
		{
			DifRot.z += D3DX_PI * 2;
		}

		DigitPos = DifPos * fRatioFrame + e->GetDefaultPos() + NowPos;
		DigitRot = DifRot * fRatioFrame + e->GetDefaultRot() + NowRot;

		e->SetPos(DigitPos);
		e->SetRot(DigitRot);

		++nCntParts;
	}

	++m_NowFrame;

	if (m_NowFrame >= m_aMotion[nNowMotion].aKetSet[nNowKey].nFrame)
	{
		++m_CurKey;
		m_NowFrame = 0;
		if (m_CurKey >= m_aMotion[nNowMotion].nKeyNum)
		{
			if (EndMotion())
			{
				if (!m_aMotion[nNowMotion].bLoop)
				{
					--m_CurKey;
					m_CurKey = 0;
					m_NowFrame = 0;
					m_NowAllFrame = 0;
					m_CurMotion = m_NextMotion = 0;
				}
				else
				{
					m_CurKey = 0;
					m_NowAllFrame = 0;
				}
			}
			else
			{
				m_CurKey = 0;
				m_NowAllFrame = 0;
				m_NowFrame = 0;
				m_CurMotion = m_NextMotion;
				m_bBlend = false;
			}
		}
	}
}
//==========================================================================================
//モーション切り替え時のブレンド処理
//==========================================================================================
bool CCharacter::MotionBlending()
{
	if (!m_bBlend) {
		return false;
	}

	//現在の位置・角度
	D3DXVECTOR3 NowPos = {};
	D3DXVECTOR3 NowRot = {};

	//次の位置・角度
	D3DXVECTOR3 NextPos = {};
	D3DXVECTOR3 NextRot = {};

	//動きの差分を求める用
	D3DXVECTOR3 DifPos = {};
	D3DXVECTOR3 DifRot = {};

	//計算用
	D3DXVECTOR3 DigitPos = {};
	D3DXVECTOR3 DigitRot = {};

	int nLastKey = m_CurKey;
	int nNowMotion = m_CurMotion;

	float fRatioFrame = ((float)m_NowFrame / (float)m_aMotion[m_NextMotion].aKetSet[0].nFrame);
	int nCntParts = 0;

	for (auto& e : m_apModelParts)
	{
		//現在の向きと位置の情報
		NowPos = m_aMotion[nNowMotion].aKetSet[nLastKey].aKey[nCntParts].pos;
		NowRot = m_aMotion[nNowMotion].aKetSet[nLastKey].aKey[nCntParts].rot;

		//次のキーの情報
		NextPos = m_aMotion[m_NextMotion].aKetSet[0].aKey[nCntParts].pos;
		NextRot = m_aMotion[m_NextMotion].aKetSet[0].aKey[nCntParts].rot;

		//差分を求める
		DifPos = NextPos - NowPos;
		DifRot = NextRot - NowRot;

		//-3.14～3.14の間を超える場合の修正
		if (DifRot.x >= D3DX_PI)
		{
			DifRot.x -= D3DX_PI * 2;
		}
		if (DifRot.y >= D3DX_PI)
		{
			DifRot.y -= D3DX_PI * 2;
		}
		if (DifRot.z >= D3DX_PI)
		{
			DifRot.z -= D3DX_PI * 2;
		}
		if (DifRot.x <= -D3DX_PI)
		{
			DifRot.x += D3DX_PI * 2;
		}
		if (DifRot.y <= -D3DX_PI)
		{
			DifRot.y += D3DX_PI * 2;
		}
		if (DifRot.z <= -D3DX_PI)
		{
			DifRot.z += D3DX_PI * 2;
		}

		DigitPos = DifPos * fRatioFrame + e->GetDefaultPos() + NowPos;
		DigitRot = DifRot * fRatioFrame + e->GetDefaultRot() + NowRot;

		e->SetPos(DigitPos);
		e->SetRot(DigitRot);

		++nCntParts;
	}

	++m_NowFrame;

	if (m_NowFrame > m_aMotion[m_NextMotion].aKetSet[0].nFrame)
	{
		m_CurKey = 0;
		m_NowFrame = 0;
		m_CurMotion = m_NextMotion;
		SetNextKey();
		m_bBlend = false;
	}

	return m_bBlend;
}

//==========================================================================================
//モーションをファイルから読み込み
//==========================================================================================
void CCharacter::MotionDataLoad(std::string filename)
{
	char LoadData[128];
	char ModelPath[128];

	int nNumModel = 0;
	FILE* pFile;
	int nCnt = 0;

	int nMotionCnt = 0;
	int nKeySet = 0;
	int nKey = 0;
	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };
	int nFilenameCnt = 0;
	int nParent = 0;
	int nIndex = 0;
	int nModelCnt = 0;
	Motion GetMotionData;
	Key GetKeyData;
	KeySet GetKeySetData;


	pFile = fopen(filename.c_str(), "r");

	if (pFile != nullptr)
	{
		while (1)
		{
			fscanf(pFile, "%s", LoadData);

			if (!strcmp(LoadData, "END_SCRIPT"))	// ファイルの最後
			{
				fclose(pFile);
				break;
			}

			if (LoadData[0] == '#')		// 文字飛ばし
			{
				continue;
			}

			//モデルの読み込み
			if (!strcmp(LoadData, "NUM_MODEL"))
			{
				fscanf(pFile, "%s", LoadData);
				fscanf(pFile, "%d", &m_ModelParts);
			}
			//モデルのファイル名読み込み
			if (!strcmp(LoadData, "MODEL_FILENAME"))
			{
				fscanf(pFile, "%s", LoadData);

				fscanf(pFile, "%s", ModelPath);

				m_pModelFileName.push_back(ModelPath);

				m_apModelParts.push_back(CModelParts::Create(pos, m_pModelFileName[nFilenameCnt]));

				++nFilenameCnt;
			}
			//キャラクターの設定の読み込み開始
			if (!strcmp(LoadData, "CHARACTERSET"))
			{
				while (1)
				{
					fscanf(pFile, "%s", LoadData);

					if (!strcmp(LoadData, "END_CHARACTERSET"))//読み込みを終了
					{
						break;
					}
					else if (!strcmp(LoadData, "PARTSSET"))
					{
						while (1)
						{
							fscanf(pFile, "%s", LoadData);

							if (LoadData[0] == '#')
							{//文字飛ばし
								fgets(LoadData, 100, pFile);
								continue;
							}

							if (!strcmp(LoadData, "END_PARTSSET"))
							{
								//読み込みを終了
								break;
							}
							//各パーツのモーションpos値
							else if (!strcmp(LoadData, "INDEX"))
							{
								fscanf(pFile, "%s", LoadData);
								fscanf(pFile, "%d", &nIndex);
							}

							//各パーツのモーションrot値
							else if (!strcmp(LoadData, "PARENT"))
							{
								fscanf(pFile, "%s", LoadData);
								fscanf(pFile, "%d", &nParent);
							}
							//各パーツのモーションpos値
							else if (!strcmp(LoadData, "POS"))
							{
								fscanf(pFile, "%s", LoadData);
								fscanf(pFile, "%f", &pos.x);
								fscanf(pFile, "%f", &pos.y);
								fscanf(pFile, "%f", &pos.z);
							}

							//各パーツのモーションrot値
							else if (!strcmp(LoadData, "ROT"))
							{
								fscanf(pFile, "%s", LoadData);
								fscanf(pFile, "%f", &rot.x);
								fscanf(pFile, "%f", &rot.y);
								fscanf(pFile, "%f", &rot.z);
							}
						}
						m_apModelParts[nModelCnt]->SetPos(pos);
						m_apModelParts[nModelCnt]->SetRot(rot);

						m_apModelParts[nModelCnt]->SetDefault();
						m_apModelParts[nModelCnt]->SetIndex(nIndex);
						if (nParent != -1)
						{
							m_apModelParts[nModelCnt]->SetParent(m_apModelParts[nParent]);
						}
						++nModelCnt;
					}
				}
			}

			//モーションの読み込み開始
			if (!strcmp(LoadData, "MOTIONSET"))
			{
				while (1)
				{
					fscanf(pFile, "%s", LoadData);

					if (!strcmp(LoadData, "END_MOTIONSET"))//読み込みを終了
					{
						m_aMotion.push_back(GetMotionData);
						GetMotionData.aKetSet.clear();
						break;
					}
					//ループの判断
					else if (!strcmp(LoadData, "LOOP"))
					{
						int bloop;
					
						fscanf(pFile, "%s", LoadData);
						fscanf(pFile, "%d", &bloop);
						GetMotionData.bLoop = bloop;
					}

					//全体のキー数の読み込み
					else  if (!strcmp(LoadData, "NUM_KEY"))
					{
						int nNum;
						fscanf(pFile, "%s", LoadData);
						fscanf(pFile, "%d", &nNum);
						GetMotionData.nKeyNum = nNum;
					}
					//当たり判定の有無
					else  if (!strcmp(LoadData, "COLLISION"))
					{
						D3DXVECTOR3 POS, RADIUS;
						int PARENT,START_F,END_F;
						float FLOAT_RADIUS;
						fscanf(pFile, "%s", LoadData);
						fscanf(pFile, "%d", &PARENT);
						fscanf(pFile, "%f", &POS.x);
						fscanf(pFile, "%f", &POS.y);
						fscanf(pFile, "%f", &POS.z);
						fscanf(pFile, "%f", &FLOAT_RADIUS);
						fscanf(pFile, "%d", &START_F);
						fscanf(pFile, "%d", &END_F);
						RADIUS = { FLOAT_RADIUS ,FLOAT_RADIUS ,FLOAT_RADIUS };
						m_pHitCircle.push_back(CHitCircle::Create(RADIUS, POS, PARENT, START_F, END_F,nMotionCnt));
						m_pDebugCircle.push_back(CDebugLineSphire::Create(FLOAT_RADIUS));
					}
					//各キーを読み込み
					if (!strcmp(LoadData, "KEYSET"))
					{
						while (1)
						{
							fscanf(pFile, "%s", LoadData);

							if (LoadData[0] == '#')
							{//文字飛ばし
								fgets(LoadData, 100, pFile);
								continue;
							}

							if (!strcmp(LoadData, "END_KEYSET"))
							{
								GetMotionData.aKetSet.push_back(GetKeySetData);
								GetKeySetData.aKey.clear();
								//読み込みを終了
								break;
							}

							//現在のキーのフレーム数を読み込み
							else if (!strcmp(LoadData, "FRAME"))
							{
								int nFrame;
								fscanf(pFile, "%s", LoadData);
								fscanf(pFile, "%d", &nFrame);
								GetKeySetData.nFrame = nFrame;
							}

							//現在のキーの読み込み
							if (!strcmp(LoadData, "KEY"))
							{
								while (1)
								{
									fscanf(pFile, "%s", LoadData);

									if (!strcmp(LoadData, "END_KEY"))
									{
										GetKeySetData.aKey.push_back(GetKeyData);
										// 読み込みを終了
										break;
									}

									//各パーツのモーションpos値
									else if (!strcmp(LoadData, "POS"))
									{

										fscanf(pFile, "%s", LoadData);
										fscanf(pFile, "%f", &GetKeyData.pos.x);
										fscanf(pFile, "%f", &GetKeyData.pos.y);
										fscanf(pFile, "%f", &GetKeyData.pos.z);
									}

									//各パーツのモーションrot値
									else if (!strcmp(LoadData, "ROT"))
									{
										fscanf(pFile, "%s", LoadData);
										fscanf(pFile, "%f", &GetKeyData.rot.x);
										fscanf(pFile, "%f", &GetKeyData.rot.y);
										fscanf(pFile, "%f", &GetKeyData.rot.z);
									}
								}

							}
						}

					}
				}
				++nMotionCnt;
			}
		}
	}
	else
	{
		assert(pFile == nullptr);
	}
}