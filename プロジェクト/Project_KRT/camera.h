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
	inline void AddCameraDistance(float dis) { m_camDistance = dis; };

	inline float GetCameraDistance() { return m_camDistance; };
	inline D3DXVECTOR3 GetPosV() { return m_posV; }
	inline D3DXVECTOR3& GetPlayerPos() { return m_PlayerPos; }
	inline void SetPlayerPos(D3DXVECTOR3 pos) { m_PlayerPos = pos; m_bLockOnCam = false;}
	inline void SetLockOnPos(D3DXVECTOR3 pos) { m_LockOnPos = pos; m_bLockOnCam = true; }
	inline float GetRotZ() { return m_fRotZ; }

	void SetFreeCam(D3DXVECTOR3 destPosV, D3DXVECTOR3 destPosR, int Frame);
	inline void DefuseFreeCam() { m_bFreeCam = false; }
	void SetRotz(float rot);
	inline void AddRotz(float rot) { m_fRotZ += rot; }

	inline void SetCameraHeigjt(float Height) { m_camHeight = Height; };
	inline void AddCameraHeigjt(float Height) { m_camHeight += Height; };

	inline void SetShake(int nFlame, float fShake) { m_nShakeFlame = nFlame; m_fShalePower = fShake; }
	inline void SetCamPos(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR) { m_posV = PosV; m_posR = PosR; }	//視点 / 注視点の設定
	void SetCamDefault() {
		m_posV = D3DXVECTOR3(0.0f, 100.0f, -300.0f);
		m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_PlayerPos = { 0.0f,0.0f,0.0f };
		m_camDistance = 600.0f;
		m_fRotZ = 0.0f;
	};

	void UpdateLockOnCam(D3DXMATRIX mat, D3DXVECTOR3 posEnemy);

private:
	void UpdateNormalCam();
	void UpdateFreeCam();
	D3DXVECTOR3 m_posV, m_posR, m_posU,m_rot,m_PlayerPos,m_LockOnPos;
	D3DXMATRIX m_mtxProjection, m_mtxView;
	float m_fRotZ;
	float m_camDistance;
	float m_camHeight;
	int m_nShakeFlame;
	float m_fShalePower;

	D3DXVECTOR3 m_DestPosV, m_DestPosR,m_LastPosV,m_LastPosR;
	int m_DestFrame,m_NowFrame;
	bool m_bFreeCam,m_bLockOnCam;

	LPD3DXFONT m_pFont;		//フォントのポインタ

};

#endif 
