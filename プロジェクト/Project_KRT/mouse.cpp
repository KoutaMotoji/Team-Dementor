
#include "mouse.h"

CMouse::CMouse()
{
}


CMouse::~CMouse()
{
}

//=============================================
//������
//=============================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	m_MousePos = { 0.0f,0.0f,0.0f };
	m_MouseMove = { 0.0f,0.0f,0.0f };
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;


	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return E_FAIL;
	}

	//�}�E�X�̃A�N�Z�X�����l��
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CMouse::Uninit()
{
	CInput::Uninit();
}

//=============================================
//�X�V
//=============================================
void CMouse::Update()
{

	DIMOUSESTATE zdiMouseState;
	int nCntMouse;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(zdiMouseState), &zdiMouseState)))
	{
		for (nCntMouse = 0; nCntMouse < NUM_MOUSE_MAX; nCntMouse++)
		{
			m_KeyStateRelease.rgbButtons[nCntMouse] = (m_KeyState.rgbButtons[nCntMouse] ^ zdiMouseState.rgbButtons[nCntMouse]) & ~zdiMouseState.rgbButtons[nCntMouse];
			m_KeyStateTrigger.rgbButtons[nCntMouse] = (m_KeyState.rgbButtons[nCntMouse] ^ zdiMouseState.rgbButtons[nCntMouse]) & zdiMouseState.rgbButtons[nCntMouse];
			m_KeyState.rgbButtons[nCntMouse] = zdiMouseState.rgbButtons[nCntMouse]; //�L�[�{�[�h�̃v���X����ۑ�
		}

		m_MouseMove.x = (float)zdiMouseState.lX;
		m_MouseMove.y = (float)zdiMouseState.lY;
	}
	else
	{
		m_pDevice->Acquire(); //�L�[�{�[�h�̃A�N�Z�X�����l��
	}
}

//=============================================
//�}�E�X�̏����擾
//=============================================
bool CMouse::GetPress(int nKey)
{
	return(m_KeyState.rgbButtons[nKey] & 0x80) != 0;
}
//=============================================
//�}�E�X�̃g���K�[�擾
//=============================================
bool CMouse::GetTrigger(int nKey)
{
	return(m_KeyStateTrigger.rgbButtons[nKey] & 0x80) != 0;
}
//=============================================
//�}�E�X�̃����[�X�擾
//=============================================
bool CMouse::GetRelease(int nKey)
{
	return(m_KeyStateRelease.rgbButtons[nKey] & 0x80) != 0;
}
//=============================================
//�}�E�X�̃��[�u�l�擾
//=============================================
D3DXVECTOR3 CMouse::GetMouseMove(void)
{
	return(m_MouseMove);
}
