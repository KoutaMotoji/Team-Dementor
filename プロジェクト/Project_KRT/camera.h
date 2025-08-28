//===============================================================================
//
//  カメラ処理(Block.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//カメラクラス
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();

	inline void SetCameraDistance(float distance) { m_camDistance = distance; };
	inline float GetCameraDistance() { return m_camDistance; };
	inline void AddCameraDistance(float dis) { m_camDistance = dis; };

	inline void SetPlayerPos(D3DXVECTOR3 pos) { m_PlayerPos = pos; }
	inline void SetEnemyPos(const D3DXVECTOR3& pos) { m_EnemyPos = pos; }
	inline float GetRotZ() { return m_fRotZ; }
	void SetRotz(float rot);
	inline void AddRotz(float rot) { m_fRotZ += rot; }

	inline void SetCameraHeigjt(float Height) { m_camHeight = Height; };
	inline void AddCameraHeigjt(float Height) { m_camHeight += Height; };

	void SetFreeCam(D3DXVECTOR3 destPosV, D3DXVECTOR3 destPosR, int Frame, bool relative = false);
	inline void DefuseFreeCam() { m_bFreeCam = false; }

	inline void SetCamPos(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR) { m_posV = PosV; m_posR = PosR; }	//視点 / 注視点の設定
	void UpdateLockOnCam(D3DXVECTOR3 posPlayer, D3DXVECTOR3 posEnemy);

	inline D3DXVECTOR3 GetPosV() { return m_posV; }
	inline D3DXVECTOR3 GetPosR() { return m_posR; }
	inline bool IsFreeCam() const { return m_bFreeCam; }


	inline void SetShake(int nFlame, float fShake) { m_nShakeFlame = nFlame; m_fShalePower = fShake; }
	void SetCamDefault() {
		m_posV = D3DXVECTOR3(0.0f, 100.0f, -300.0f);
		m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_PlayerPos = { 0.0f,0.0f,0.0f };
		m_camDistance = 600.0f;
		m_fRotZ = 0.0f;
	};

	void UpdateNormalCam();

private:
	void UpdateFreeCam();
	D3DXVECTOR3 m_posV, m_posR, m_posU, m_rot, m_PlayerPos, m_EnemyPos;
	D3DXMATRIX m_mtxProjection, m_mtxView;
	float m_fRotZ;
	float m_camDistance;
	float m_camHeight;
	int m_nShakeFlame;
	float m_fShalePower;

	D3DXVECTOR3 m_DestPosV, m_DestPosR;	
	D3DXVECTOR3 m_LastPosV, m_LastPosR;
	D3DXVECTOR3 m_StartPlayerPos, m_StartEnemyPos;

	int m_DestFrame,m_NowFrame;
	bool m_bFreeCam, m_bLockOnCam, m_bRelative, m_bFreeCamManual;

	LPD3DXFONT m_pFont;		//フォントのポインタ

};

#endif 
