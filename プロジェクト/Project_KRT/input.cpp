//===============================================================================
//
//		 �C���v�b�g�Ǘ��N���X(input.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "input.h"
//�}�N����`

////�O���[�o���ϐ�
//XINPUT_STATE g_joyKeyState;
//XINPUT_STATE g_joyKeyStateTrigger;

//�ÓI�����o������
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

CInput::CInput()
{

}

CInput::~CInput()
{

}

//==========================================================================================
//���͏���������
//==========================================================================================
HRESULT CInput::Init(HINSTANCE hInstace, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstace, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	return S_OK;
}

//==========================================================================================
//���͏I������
//==========================================================================================
void CInput::Uninit(void)
{
	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//
////�L�[�{�[�h�̃v���X�����擾
//bool GetKeyboardPress(int nKey)
//{
//	return (g_aKeyState[nKey] & 0x80) != 0;
//}
////�L�[�{�[�h�̃v���X�����擾
//bool GetKeyboardTrigger(int nKey)
//{
//	return (g_aKeyStateTrigger[nKey] & 0x80) != 0;
//}
//
//HRESULT InitJoypad(void)
//{
//	//�������̃N���A
//	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));
//
//	//XInputEnable�̃X�e�[�g��ݒ�(�L���ɂ���)
//	XInputEnable(true);
//
//	return S_OK;
//}
//
//void UninitJoypad(void)
//{
//	//XInputEnable�̃X�e�[�g��ݒ�(�����ɂ���)
//	XInputEnable(false);
//}
//
//void UpdateJoypad(void)
//{
//	XINPUT_STATE JoykeyState;
//	//�W���C�p�b�h�̏�Ԃ��擾
//	if (XInputGetState(0, &JoykeyState) == ERROR_SUCCESS)
//	{
//		WORD Button = JoykeyState.Gamepad.wButtons;
//		WORD OldButton = g_joyKeyState.Gamepad.wButtons;
//		g_joyKeyStateTrigger.Gamepad.wButtons = ~OldButton & Button;
//
//		g_joyKeyState = JoykeyState;
//	}
//}
//
//bool GetJoypadPress(JOYKEY key)
//{
//	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
//}
//
//bool GetJoypadTrigger(JOYKEY key)
//{
//	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
//}