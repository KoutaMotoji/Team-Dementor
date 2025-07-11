//===============================================================================
//
//  �J��������(camera.h)
//								����F���n�O��
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
					,m_DestPosR({0.0f,0.0f,0.0f}),m_DestPosV({ 0.0f,0.0f,0.0f }),m_LastPosR({ 0.0f,0.0f,0.0f }),m_LastPosV({ 0.0f,0.0f,0.0f })
{

}

CCamera::~CCamera()
{

}

//������
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 100.0f, -300.0f);
	m_posR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_posU = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PlayerPos = { 0.0f,0.0f,0.0f };
	m_camDistance = 600.0f;
	m_fRotZ = 0.0f;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾

	//�f�o�b�O�\���p�t�H���g�̐���	
	D3DXCreateFont(pDevice, 20, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "HGP�޼��E", &m_pFont);
	return S_OK;
}

//�I��
void CCamera::Uninit(void)
{
	//�f�o�b�O�\���p�t�H���g�̔p��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//�X�V
void CCamera::Update(void)
{
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

		if (!m_bFreeCam)
		{
			UpdateNormalCam();
		}
		else
		{
			UpdateFreeCam();
		}
	}
	m_bLockOnCam = false;
}

//�ݒ�
void CCamera::SetCamera(void)
{
	D3DXVECTOR3 adjust = { 0.0f,0.0f,0.0f };
	if (m_nShakeFlame > 0)
	{
		--m_nShakeFlame;
		//��������
		std::random_device rnd;				// �񌈒�I�ȗ���������ŃV�[�h�����@�𐶐�
		std::mt19937 mt(rnd());				//  �����Z���k�c�C�X�^�[��32�r�b�g�ŁA�����͏����V�[�h
		std::uniform_int_distribution<> rand_value(-m_fShalePower, m_fShalePower);     // �N�G�C�N�֐��Ăяo�����̈����ł͈̔͂̈�l����

		float randShake = (rand_value(mt) );
		adjust.x = randShake;
		adjust.z = randShake;

		m_posV += adjust;
		m_posR += adjust;
	}

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//�v���W�F�N�V�����}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxProjection);
	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DXToRadian(45.0f),
								(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,
								10.0f,
								20000.0f);
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posV,
						&m_posR,
						&m_posU);
	//�r���[�}�g���b�N�X�̐ݒ�
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

void CCamera::UpdateLockOnCam(D3DXMATRIX mat, D3DXVECTOR3 posEnemy)
{
	D3DXMATRIX SetMtx{}, mtxTrans{}, mtxRot{};

	D3DXVECTOR3 pos = { 0.0f,200.0f,-700.0f };
	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };

	//�}�g���b�N�X����ʒu�𒊏o
	D3DXVECTOR3 mtxPos1 = {
	mat._41,
	mat._42,
	mat._43
	};
	D3DXVECTOR3 PlayerPos = { mtxPos1.x,0.0f,mtxPos1.z };

	D3DXVECTOR3 EnemyPos = { posEnemy.x,0.0f,posEnemy.z };

	D3DXVECTOR3 dir = EnemyPos - PlayerPos;
	D3DXVec3Normalize(&dir, &dir);

	float Yaw = atan2f(dir.x, dir.z);

	D3DXMATRIX RotY;
	D3DXVECTOR3 RotateOffset;

	D3DXMatrixRotationY(&RotY, Yaw);
	D3DXVec3TransformCoord(&RotateOffset, &pos, &RotY);

	D3DXVECTOR3 CamPos = mtxPos1 + RotateOffset;

	CManager::GetInstance()->GetCamera()->SetRotz(Yaw);

	m_posV = CamPos;

	m_posR = posEnemy;

	m_posR.y += 150.0f;

	m_bLockOnCam = true;
}

void CCamera::UpdateFreeCam()
{
	D3DXVECTOR3 destV, destR;
	float SetLerp = (1.0f / m_DestFrame) * m_NowFrame;
	D3DXVec3Lerp(&destV, &m_LastPosV, &m_DestPosV, SetLerp);
	D3DXVec3Lerp(&destR, &m_LastPosR, &m_DestPosR, SetLerp);

	m_posV = destV;
	m_posR = destR;

	++m_NowFrame;
	if (m_DestFrame <= m_NowFrame)
	{
		--m_NowFrame;
	}
}

void CCamera::SetFreeCam(D3DXVECTOR3 destPosV, D3DXVECTOR3 destPosR, int Frame)
{
	m_LastPosR = m_posR;
	m_LastPosV = m_posV;
	m_DestPosR = destPosR;
	m_DestPosV = destPosV;
	m_DestFrame = Frame;
	m_NowFrame = 0;
	m_bFreeCam = true;
}
