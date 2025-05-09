//===============================================================================
//
//		�L�[�{�[�h���͊Ǘ��N���X(keyboard.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "main.h"
#include "keyboard.h"

//�ÓI�����o������
LPDIRECTINPUTDEVICE8 CKeyboard::m_pDevKeyboard = nullptr;

CKeyboard::CKeyboard() :
	m_aKeyState(), 
	m_aKeyStateTrigger()
{

}

CKeyboard::~CKeyboard()
{

}

//==========================================================================================
//����������
//==========================================================================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�̃A�N�Z�X�����l��
	m_pDevKeyboard->Acquire();
	return S_OK;
}

//==========================================================================================
//�I������
//==========================================================================================
void CKeyboard::Uninit()
{
	//���̓f�o�C�X�̔j��
	if (m_pDevKeyboard != NULL)
	{
		m_pDevKeyboard->Unacquire();
		m_pDevKeyboard->Release();
		m_pDevKeyboard = nullptr;
	}
	CInput::Uninit();
}

//==========================================================================================
//�X�V����
//==========================================================================================
void CKeyboard::Update()
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;
	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			m_aKeyStateRepeat[nCntKey]  = (m_aKeyState[nCntKey] & aKeyState[nCntKey]);

			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevKeyboard->Acquire();
	}
}

//==========================================================================================
//�L�[�{�[�h�̃v���X�����擾
//==========================================================================================
bool CKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) != 0;
}

//==========================================================================================
//�L�[�{�[�h�̃g���K�[�����擾
//==========================================================================================
bool CKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) != 0;
}

//==========================================================================================
//�L�[�{�[�h�̃����[�X�����擾
//==========================================================================================
bool CKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) != 0;
}

//==========================================================================================
//�L�[�{�[�h�̃��s�[�g�����擾
//==========================================================================================
bool CKeyboard::GetRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0x80) != 0;
}