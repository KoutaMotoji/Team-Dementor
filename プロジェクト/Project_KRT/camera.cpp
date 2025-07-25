//===============================================================================
//
//  カメラ処理(camera.h)
//								制作：元地弘汰
// 
//===============================================================================
#include "camera.h"
#include "manager.h"
#include "xxx_player.h"
#include "stage1_boss.h"

namespace
{
	float _CAM_ROTSPEED = 0.05f;
	float _CAM_UPSPEED = 15.0f;
	float _CAM_ZOOMSPEED = 15.0f;

	float _CAM_MAX_HEIGHT = 600.0f;
	float _CAM_MIN_HEIGHT = 100.0f;
	float _CAM_MAX_ZOOM = 600.0f;
	float _CAM_MIN_ZOOM = 100.0f;
}

CCamera::CCamera():m_nShakeFlame(0)
					,m_fShalePower(0.0f), m_camHeight(1000.0f), m_DestFrame(0),m_NowFrame(0), m_bFreeCam(false), m_bLockOnCam(false)
					,m_DestPosR({ 0.0f,0.0f,0.0f }),m_DestPosV({ 0.0f,0.0f,0.0f }),m_LastPosR({ 0.0f,0.0f,0.0f }),m_LastPosV({ 0.0f,0.0f,0.0f })
{

}

CCamera::~CCamera()
{

}

//初期化
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 100.0f, -300.0f);
	m_posR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_posU = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PlayerPos = { 0.0f,0.0f,0.0f };
	m_camDistance = 600.0f;
	m_fRotZ = 0.0f;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//デバイスへのポインタを取得

	//デバッグ表示用フォントの生成	
	D3DXCreateFont(pDevice, 20, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "HGPｺﾞｼｯｸE", &m_pFont);
	return S_OK;
}

//終了
void CCamera::Uninit(void)
{
	//デバッグ表示用フォントの廃棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//更新
void CCamera::Update(void)
{
	if (m_bFreeCam)
	{
		UpdateFreeCam();
		return;
	}

	if (!m_bLockOnCam)
	{
		if (CManager::GetInstance()->GetJoypad()->GetJoyStickR(CJoypad::JOYSTICK_DLEFT) == true ||
			CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LEFTARROW) == true)
		{
			m_fRotZ += _CAM_ROTSPEED;
			if (m_fRotZ > D3DX_PI)
			{
				m_fRotZ = -D3DX_PI;
			}
		}

		if (CManager::GetInstance()->GetJoypad()->GetJoyStickR(CJoypad::JOYSTICK_DRIGHT) == true ||
			CManager::GetInstance()->GetKeyboard()->GetPress(DIK_RIGHTARROW) == true)
		{
			m_fRotZ -= _CAM_ROTSPEED;
			if (m_fRotZ < -1 * D3DX_PI)
			{
				m_fRotZ = D3DX_PI;
			}
		}

		if (CManager::GetInstance()->GetJoypad()->GetJoyStickR(CJoypad::JOYSTICK_DUP) == true ||
			CManager::GetInstance()->GetKeyboard()->GetPress(DIK_UPARROW) == true)
		{
			m_camHeight += _CAM_UPSPEED;
			if (m_camHeight > _CAM_MAX_HEIGHT)
			{
				m_camHeight = _CAM_MAX_HEIGHT;
			}
		}
		if (CManager::GetInstance()->GetJoypad()->GetJoyStickR(CJoypad::JOYSTICK_DDOWN) == true ||
			CManager::GetInstance()->GetKeyboard()->GetPress(DIK_DOWNARROW) == true)
		{
			m_camHeight -= _CAM_UPSPEED;
			if (m_camHeight < _CAM_MIN_HEIGHT)
			{
				m_camHeight = _CAM_MIN_HEIGHT;
			}
		}
		if (CManager::GetInstance()->GetJoypad()->GetPress(CJoypad::JOYPAD_DPAD_UP) == true)
		{
			m_camDistance += _CAM_ZOOMSPEED;
			if (m_camDistance > _CAM_MAX_ZOOM)
			{
				m_camDistance = _CAM_MAX_ZOOM;
			}
		}
		if (CManager::GetInstance()->GetJoypad()->GetPress(CJoypad::JOYPAD_DPAD_DOWN) == true)
		{
			m_camDistance -= _CAM_ZOOMSPEED;
			if (m_camDistance < _CAM_MIN_ZOOM)
			{
				m_camDistance = _CAM_MIN_ZOOM;
			}
		}

		UpdateNormalCam();
	}
	m_bLockOnCam = false;
}

//設定
void CCamera::SetCamera(void)
{
	D3DXVECTOR3 adjust = { 0.0f,0.0f,0.0f };
	if (m_nShakeFlame > 0)
	{
		--m_nShakeFlame;
		//乱数生成
		std::random_device rnd;				// 非決定的な乱数生成器でシード生成機を生成
		std::mt19937 mt(rnd());				//  メルセンヌツイスターの32ビット版、引数は初期シード
		std::uniform_int_distribution<> rand_value(-m_fShalePower, m_fShalePower);     // クエイク関数呼び出し時の引数での範囲の一様乱数

		float randShake = (rand_value(mt) );
		adjust.x = randShake;
		adjust.z = randShake;

		m_posV += adjust;
		m_posR += adjust;
	}

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//プロジェクションマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxProjection);
	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DXToRadian(45.0f),
								(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,
								10.0f,
								20000.0f);
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posV,
						&m_posR,
						&m_posU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW,
							&m_mtxView);
}

void CCamera::SetRotz(float rot)
{
	m_fRotZ = rot;
}

void CCamera::UpdateNormalCam()
{
	float m_Dis = (m_camDistance);
	m_posV.x = sinf(D3DX_PI + m_fRotZ) * sqrtf(m_Dis * m_Dis + (m_Dis * 0.1f) * (m_Dis * 0.1f)) / 2.0f + m_PlayerPos.x;
	m_posV.z = cosf(D3DX_PI + m_fRotZ) * sqrtf(m_Dis * m_Dis + (m_Dis * 0.1f) * (m_Dis * 0.1f)) / 2.0f + m_PlayerPos.z;
	m_posV.y = m_PlayerPos.y + m_camHeight;

	m_posR.x = m_PlayerPos.x;
	m_posR.z = m_PlayerPos.z;
	m_posR.y = m_PlayerPos.y + 50.0f;
}

void CCamera::UpdateLockOnCam(D3DXVECTOR3 posPlayer, D3DXVECTOR3 posEnemy)
{
	m_posV = posPlayer;

	m_posR = posEnemy;

	m_posR.y += 150.0f;

	m_bLockOnCam = true;
}

void CCamera::UpdateFreeCam()
{
	// 補間の進行度を計算 (0.0～1.0) smoothstepで滑らかに
	float t = (float)m_NowFrame / (float)m_DestFrame;
	t = t * t * (3 - 2 * t);

	// ---- カメラ位置の補間 ----
	// 開始時のプレイヤー位置から見た「カメラ相対位置」
	D3DXVECTOR3 startCamOffset = m_LastPosV - m_StartPlayerPos;
	D3DXVECTOR3 destCamOffset = m_DestPosV - m_StartPlayerPos;

	// 相対位置を補間
	D3DXVECTOR3 interpCamOffset;
	D3DXVec3Lerp(&interpCamOffset, &startCamOffset, &destCamOffset, t);

	// 実際のカメラ位置 = 現在のプレイヤー位置 + 補間済みの相対位置
	m_posV = m_PlayerPos + interpCamOffset;

	// ---- 注視点の補間 ----
	D3DXVECTOR3 startTargetOffset = m_LastPosR - m_StartPlayerPos;
	D3DXVECTOR3 destTargetOffset = m_DestPosR - m_StartPlayerPos;

	D3DXVECTOR3 interpTargetOffset;
	D3DXVec3Lerp(&interpTargetOffset, &startTargetOffset, &destTargetOffset, t);

	// 実際の注視点 = 現在のプレイヤー位置 + 補間済みの注視点相対位置
	m_posR = m_PlayerPos + interpTargetOffset;
	m_posR.y += 150.0f; // 少し上に注視

	// ---- 補間フレームを進める ----
	++m_NowFrame;
	if (m_NowFrame >= m_DestFrame)
	{
		m_bFreeCam = false; // 補間終了
	}

	//// 補間進行度
	//float t = (float)m_NowFrame / (float)m_DestFrame;
	//t = t * t * (3 - 2 * t); // smoothstep

	//D3DXVECTOR3 destV, destR;
	//D3DXVec3Lerp(&destV, &m_LastPosV, &m_DestPosV, t);
	//D3DXVec3Lerp(&destR, &m_LastPosR, &m_DestPosR, t);

	//m_posV = destV;
	//m_posR = destR;

	//++m_NowFrame;
	//if (m_NowFrame >= m_DestFrame) {
	//	m_bFreeCam = false;
	//}

	//D3DXVECTOR3 destV, destR;
	//float SetLerp = (1.0f / m_DestFrame) * m_NowFrame;
	//D3DXVec3Lerp(&destV, &m_LastPosV, &m_DestPosV, SetLerp);
	//D3DXVec3Lerp(&destR, &m_LastPosR, &m_DestPosR, SetLerp);

	//m_posV = destV;
	//m_posR = destR;

	//++m_NowFrame;
	//if (m_DestFrame <= m_NowFrame)
	//{
	//	--m_NowFrame;
	//	m_bFreeCam = false;
	//}
}

void CCamera::SetFreeCam(D3DXVECTOR3* destPosV, D3DXVECTOR3* destPosR, int Frame)
{
	m_LastPosR = m_posR;
	m_LastPosV = m_posV;
	m_DestPosR = *destPosR;
	m_DestPosV = *destPosV;
	m_DestFrame = Frame;
	m_NowFrame = 0;
	m_bFreeCam = true;

	// 補間開始時のプレイヤーと敵の位置を記録
	m_StartPlayerPos = m_PlayerPos;
	m_StartEnemyPos = m_EnemyPos;
}