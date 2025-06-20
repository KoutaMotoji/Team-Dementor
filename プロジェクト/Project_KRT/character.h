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
#include "collision.h"
#include "debug_line.h"


#include "manager.h"

class CCharacter :public CObject
{
public:
	CCharacter(int nPriority = 1);				//コンストラクタ
	~CCharacter()override;		//デストラクタ
	void Init()override;		//初期化
	void Uninit()override;		//終了
	void Update()override;		//更新
	void Draw()override;		//描画

	virtual bool EndMotion() { return true; };
	static CCharacter* Create(D3DXVECTOR3 pos);

	inline D3DXVECTOR3 GetPos() { return m_pos; }				//座標取得
	inline void AddPos(D3DXVECTOR3 pos) { m_pos += pos; }		//座標移動
	inline void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }		//座標変更
	inline D3DXVECTOR3 GetRot() { return m_rot; }				//角度取得
	inline void AddRot(D3DXVECTOR3 rot) { m_rot += rot; }		//角度移動	
	inline void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	inline void AddSize(D3DXVECTOR3 size) { m_size += size; };
	inline void SetSize(D3DXVECTOR3 size) { m_size = size; };
	inline D3DXVECTOR3 GetRadius() { return m_Radius; }
	inline void SetRadius(float RadiusValue) { m_Radius = { RadiusValue ,RadiusValue ,RadiusValue }; }

	inline D3DXVECTOR3 GetMove() { return m_move; }
	inline void SetMove(D3DXVECTOR3 move) { m_move = move; }
	inline void AddMove(D3DXVECTOR3 move) { m_move += move; }


	inline int GetNowMotion() { return m_CurMotion; }
	inline int GetNextMotion() { return m_NextMotion; }
	inline std::vector<CModelParts*> GetModelPartsVec() { return m_apModelParts; }
	inline void BlendDisable() { m_bBlend = false; }
	void MotionDataLoad(std::string filename);
	void SetNextMotion(int nNextMotionNum);
	void SetNextMotion(int nNextMotionNum,bool bBlend);

	inline std::vector<std::shared_ptr<CHitCircle>> GetVecHitCircle() { return m_pHitCircle; }
private:
	D3DXVECTOR3 m_pos, m_rot, m_size;			//座標・回転・大きさ
	D3DXVECTOR3 m_move;						//移動量
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス
	D3DXVECTOR3 m_Radius;

	void FloorCollision();					//床との当たり判定

	int m_nLife;			//体力

	std::vector<CModelParts*> m_apModelParts;	//モデルパーツのポインタの配列

	std::vector<char*> m_pModelFileName;
	int m_ModelParts;	//モデルパーツ数
	int m_CurKey;		//現在のキー番号
	int m_CurMotion;	//現在のモーション番号
	int m_NextMotion;	//次のモーション番号
	int m_KeySetNum;	//キーセット数
	int m_MotionNum;	//モーション最大数
	int m_NowFrame;		//現在のフレーム
	int m_NowAllFrame;

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

	std::vector<std::shared_ptr<CHitCircle>> m_pHitCircle;	//円の当たり判定配列

	std::vector<std::shared_ptr<CDebugLine>> m_pDebugCircle;
	

	//========================			クオータニオン用		====================================
	D3DXMATRIX m_mtxRot;		//回転マトリックス(保存用)
	D3DXQUATERNION m_quat;		//クオータニオン
	D3DXVECTOR3 m_vecAxis;		//回転軸のベクトル
	float m_fValueRot;			//回転量
};

#endif