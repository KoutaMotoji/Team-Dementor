//===============================================================================
//
//  プレイヤー処理(playerX.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "main.h"
#include "object.h"
#include "modelparts.h"

#include "manager.h"

class CCharacter :public CObject
{
public:
	CCharacter();					//コンストラクタ
	~CCharacter()override;		//デストラクタ
	void Init()override;		//初期化
	void Uninit()override;		//終了
	void Update()override;		//更新
	void SetDamageState();
	void ShootBullet();
	void Draw()override;		//描画

	bool PMove(float fCamRotZ);
	static CCharacter* Create(D3DXVECTOR3 pos);
	inline int GetPLife() { return m_nLife; };

	inline D3DXVECTOR3 GetPos() { return m_pos; };
	inline D3DXVECTOR3 GetMove() { return m_move; };
private:

	//モーション用定数
	static constexpr int MAX_MODELPARTS = 32;
	static constexpr int MAX_PARTS = 32;
	static constexpr int MAX_KEYSET = 32;
	static constexpr int MAX_MOTION = 16;

	//ステータス用定数
	static constexpr int MAX_LIFE = 1000;			//体力
	static constexpr float MOVE_JET_SPEED = 3.5f;	//移動スピードの設定
	static constexpr float MOVE_ROBO_SPEED = 2.00f;	//移動スピードの設定

	static constexpr float SCROLL_SPEED = 5.5f;		//自動スクロールスピードの設定
	static constexpr float RETICLE_VALUE = 8.5f;	//レティクルの移動ギャップ

	D3DXVECTOR3 m_pos, m_rot, m_size;			//座標・回転・大きさ
	D3DXVECTOR3 m_move;						//移動量
	D3DXVECTOR3 m_OldPos;					//過去の位置
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	void FloorCollision();					//床との当たり判定

	void DamageAdd(int nDmg);				//ダメージ加算、生存確認

	float m_fWeaponRadius;
	int m_nLife;			//体力

	CModelParts* m_apModelParts[MAX_MODELPARTS];

	char* m_pModelFileName[MAX_MODELPARTS];
	int m_ModelParts;	//モデルパーツ数
	int m_CurKey;		//現在のキー番号
	int m_CurMotion;	//現在のモーション番号
	int m_NextMotion;	//現在のモーション番号
	int m_KeySetNum;	//キーセット数
	int m_MotionNum;	//モーション最大数
	int m_NowFrame;		//現在のフレーム
	struct Key
	{
		//位置
		D3DXVECTOR3 pos;
		//向き
		D3DXVECTOR3 rot;
	};
	struct KeySet
	{

		int nFrame;
		Key aKey[MAX_PARTS];
	};
	struct Motion
	{
		int bLoop;
		int nKeyNum;
		KeySet aKetSet[MAX_KEYSET];
	};
	Motion m_aMotion[MAX_MOTION];

	void MotionInit();
	void MotionDataLoad();
	void SetNextMotion(int nNextMotionNum);
	void SetNextKey();
	bool MotionBlending();

	void TransformSound();


	bool m_bBlend;
	bool m_bMotion;
	bool TestUseMeshCollision();

	//========================			クオータニオン用		====================================
	D3DXMATRIX m_mtxRot;		//回転マトリックス(保存用)
	D3DXQUATERNION m_quat;		//クオータニオン
	D3DXVECTOR3 m_vecAxis;		//回転軸のベクトル
	float m_fValueRot;			//回転量
};

#endif