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

	void Draw()override;		//描画

	static CCharacter* Create(D3DXVECTOR3 pos);

	inline D3DXVECTOR3 GetPos() { return m_pos; }				//座標取得
	inline void AddPos(D3DXVECTOR3 pos) { m_pos += pos; }		//座標移動
	inline void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }		//座標変更
	inline D3DXVECTOR3 GetRot() { return m_rot; }				//角度取得
	inline void AddRot(D3DXVECTOR3 rot) { m_rot += rot; }		//角度移動	
	inline void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

	inline D3DXVECTOR3 GetMove() { return m_move; };
	inline int GetNowMotion() { return m_CurMotion; }
	inline int GetNextMotion() { return m_NextMotion; }

	void MotionDataLoad(std::string filename);
	void SetNextMotion(int nNextMotionNum);
	inline std::vector<CModelParts*> GetVecModelParts() {
		return m_apModelParts;
	}
private:
	D3DXVECTOR3 m_pos, m_rot, m_size;			//座標・回転・大きさ
	D3DXVECTOR3 m_move;						//移動量
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	void FloorCollision();					//床との当たり判定


	int m_nLife;			//体力

	std::vector<CModelParts*> m_apModelParts;

	std::vector<char*> m_pModelFileName;
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
		std::vector<Key>aKey;
	};
	struct Motion
	{
		int bLoop;
		int nKeyNum;
		std::vector<KeySet>aKetSet;
	};
	std::vector<Motion>m_aMotion;

	void MotionInit();
	void SetNextKey();
	bool MotionBlending();

	bool m_bBlend;
	bool m_bMotion;

	//========================			クオータニオン用		====================================
	D3DXMATRIX m_mtxRot;		//回転マトリックス(保存用)
	D3DXQUATERNION m_quat;		//クオータニオン
	D3DXVECTOR3 m_vecAxis;		//回転軸のベクトル
	float m_fValueRot;			//回転量
};

#endif