//===============================================================================
//
//		�W���C�p�b�h���͊Ǘ��N���X(joypad.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "main.h"
#include "joypad.h"

namespace
{
	int LEFT_JOYSTICK_DEADZONE = 3500;
	int RIGHT_JOYSTICK_DEADZONE = 4200;
}

CJoypad::CJoypad()
{

}

CJoypad::~CJoypad()
{

}

//==========================================================================================
//�R���g���[���[�̏�����
//==========================================================================================
HRESULT CJoypad::Init(HINSTANCE hInstace, HWND hWnd)
{
	//�������̃N���A
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));

	//XInputEnable�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK;
}

//==========================================================================================
//�R���g���[���[�̏I������
//==========================================================================================
void CJoypad::Uninit()
{
	//XInputEnable�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);
}

//==========================================================================================
//�R���g���[���[�̍X�V����
//==========================================================================================
void CJoypad::Update()
{
	XINPUT_STATE JoykeyState;
	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &JoykeyState) == ERROR_SUCCESS)
	{
		WORD Button = JoykeyState.Gamepad.wButtons;
		BYTE LeftTrigger = JoykeyState.Gamepad.bLeftTrigger;    // ���g���K�[�A�i���O�R���g���[��
		BYTE RightTrigger = JoykeyState.Gamepad.bRightTrigger;   // �E�g���K�[�A�i���O�R���g���[��
		SHORT ThumbLX = JoykeyState.Gamepad.sThumbLX;       // ���X�e�B�b�N�� X ��
		SHORT ThumbLY = JoykeyState.Gamepad.sThumbLY;       // ���X�e�B�b�N�� Y ��
		SHORT ThumbRX = JoykeyState.Gamepad.sThumbRX;       // �E�X�e�B�b�N�� X ��
		SHORT ThumbRY = JoykeyState.Gamepad.sThumbRY;       // �E�X�e�B�b�N�� Y ��

		WORD OldButton = m_joyKeyState.Gamepad.wButtons;
		WORD OldLeftTrigger = m_joyKeyState.Gamepad.bLeftTrigger;
		WORD OldRightTrigger = m_joyKeyState.Gamepad.bRightTrigger;
		m_joyKeyOldState = m_joyKeyState;


		m_joyKeyStateTrigger.Gamepad.wButtons = ~OldButton & Button;
		m_joyKeyStateTrigger.Gamepad.bLeftTrigger = ~OldLeftTrigger & LeftTrigger;
		m_joyKeyStateTrigger.Gamepad.bRightTrigger = ~OldRightTrigger & RightTrigger;

		m_joyKeyStateRelease.Gamepad.wButtons = OldButton & ~Button;
		m_joyKeyStateRelease.Gamepad.bLeftTrigger = OldLeftTrigger & ~LeftTrigger;
		m_joyKeyStateRelease.Gamepad.bRightTrigger = OldRightTrigger & ~RightTrigger;

		m_joyKeyStateRepeat.Gamepad.wButtons = OldButton & Button;
		m_joyKeyStateRepeat.Gamepad.bLeftTrigger = OldLeftTrigger & LeftTrigger;
		m_joyKeyStateRepeat.Gamepad.bRightTrigger = OldRightTrigger & RightTrigger;


		//XINPUT_STATE state;
		//ZeroMemory(&state, sizeof(XINPUT_STATE));
		// �e�X�e�B�b�N�̓��͒l���f�b�h�]�[���ȉ��Ȃ���͒l��0�ɂ���
		if ((JoykeyState.Gamepad.sThumbLX <  LEFT_JOYSTICK_DEADZONE &&
			JoykeyState.Gamepad.sThumbLX > -LEFT_JOYSTICK_DEADZONE) &&
			(JoykeyState.Gamepad.sThumbLY <  LEFT_JOYSTICK_DEADZONE &&
				JoykeyState.Gamepad.sThumbLY > -LEFT_JOYSTICK_DEADZONE))
		{//���X�e�B�b�N���f�b�h�]�[�����Ȃ̂Ő��l�𖳌�
			JoykeyState.Gamepad.sThumbLX = 0;
			JoykeyState.Gamepad.sThumbLY = 0;
		}

		if ((JoykeyState.Gamepad.sThumbRX <  RIGHT_JOYSTICK_DEADZONE &&
			JoykeyState.Gamepad.sThumbRX >  -RIGHT_JOYSTICK_DEADZONE) &&
			(JoykeyState.Gamepad.sThumbRY <  RIGHT_JOYSTICK_DEADZONE &&
				JoykeyState.Gamepad.sThumbRY >  -RIGHT_JOYSTICK_DEADZONE))
		{//�E�X�e�B�b�N���f�b�h�]�[�����Ȃ̂Ő��l�𖳌�
			JoykeyState.Gamepad.sThumbRX = 0;
			JoykeyState.Gamepad.sThumbRY = 0;
		}
		m_joyKeyState = JoykeyState;

	}
}

//==========================================================================================
//�R���g���[���[�̃v���X���
//==========================================================================================
bool CJoypad::GetPress(JOYKEY key)
{
	//�������͂��ꂽ�{�^����LT�ERT�Ȃ�{�^�����͂ɕϊ�����
	if (key == JOYPAD_LEFT_TRIGGER)
	{
		return (m_joyKeyState.Gamepad.bLeftTrigger & key) ? true : false;
	}
	else if (key == JOYPAD_RIGHT_TRIGGER)
	{
		return (m_joyKeyState.Gamepad.bRightTrigger & key) ? true : false;
	}
	else
	{
		return (m_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
	}
}

//==========================================================================================
//�R���g���[���[�̃g���K�[���
//==========================================================================================
bool CJoypad::GetTrigger(JOYKEY key)
{
	//�������͂��ꂽ�{�^����LT�ERT�Ȃ�{�^�����͂ɕϊ�����
	if (key == JOYPAD_LEFT_TRIGGER)
	{
		return (m_joyKeyStateTrigger.Gamepad.bLeftTrigger & key) ? true : false;
	}
	else if (key == JOYPAD_RIGHT_TRIGGER)
	{
		return (m_joyKeyStateTrigger.Gamepad.bRightTrigger & key) ? true : false;
	}
	else
	{
		return (m_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
	}
}

//==========================================================================================
//�R���g���[���[�̃����[�X(��������)���
//==========================================================================================
bool CJoypad::GetRelease(JOYKEY key)
{
	//�������͂��ꂽ�{�^����LT�ERT�Ȃ�{�^�����͂ɕϊ�����
	if (key == JOYPAD_LEFT_TRIGGER)
	{
		return (m_joyKeyStateRelease.Gamepad.bLeftTrigger & key) ? true : false;
	}
	else if (key == JOYPAD_RIGHT_TRIGGER)
	{
		return (m_joyKeyStateRelease.Gamepad.bRightTrigger & key) ? true : false;
	}
	else
	{
		return (m_joyKeyStateRelease.Gamepad.wButtons & (0x01 << key)) ? true : false;
	}
}

//==========================================================================================
//�R���g���[���[�̃��s�[�g(�����ꑱ���Ă���)���
//==========================================================================================
bool CJoypad::GetRepeat(JOYKEY key)
{

	//�������͂��ꂽ�{�^����LT�ERT�Ȃ�{�^�����͂ɕϊ�����
	if (key == JOYPAD_LEFT_TRIGGER)
	{
		return (m_joyKeyStateRepeat.Gamepad.bLeftTrigger & key) ? true : false;
	}
	else if (key == JOYPAD_RIGHT_TRIGGER)
	{
		return (m_joyKeyStateRepeat.Gamepad.bRightTrigger & key) ? true : false;
	}
	else
	{
		return (m_joyKeyStateRepeat.Gamepad.wButtons & (0x01 << key)) ? true : false;
	}
}

//==========================================================================================
//���X�e�B�b�N�̎擾
//==========================================================================================
bool CJoypad::GetJoyStickL(JOYSTICK joystick)
{
	switch (joystick)
	{
	case JOYSTICK_DLEFT:
		return m_joyKeyState.Gamepad.sThumbLX <= -LEFT_JOYSTICK_DEADZONE;
		break;
	case JOYSTICK_DRIGHT:
		return m_joyKeyState.Gamepad.sThumbLX >= LEFT_JOYSTICK_DEADZONE;
		break;
	case JOYSTICK_DUP:
		return m_joyKeyState.Gamepad.sThumbLY >= LEFT_JOYSTICK_DEADZONE;
		break;
	case JOYSTICK_DDOWN:
		return m_joyKeyState.Gamepad.sThumbLY <= -LEFT_JOYSTICK_DEADZONE;
		break;
	}
}

//==========================================================================================
//�E�X�e�B�b�N�̎擾
//==========================================================================================
bool CJoypad::GetJoyStickR(JOYSTICK joystick)
{
	switch (joystick)
	{
	case JOYSTICK_DLEFT:
		return m_joyKeyState.Gamepad.sThumbRX <= -RIGHT_JOYSTICK_DEADZONE;
		break;
	case JOYSTICK_DRIGHT:
		return m_joyKeyState.Gamepad.sThumbRX >= RIGHT_JOYSTICK_DEADZONE;
		break;
	case JOYSTICK_DUP:
		return m_joyKeyState.Gamepad.sThumbRY >= RIGHT_JOYSTICK_DEADZONE;
		break;
	case JOYSTICK_DDOWN:
		return m_joyKeyState.Gamepad.sThumbRY <= -RIGHT_JOYSTICK_DEADZONE;
		break;
	}
}

//==========================================================================================
//���X�e�B�b�N�̕����x�N�g�����擾
//==========================================================================================
D3DXVECTOR2 CJoypad::GetJoyStickVecL()
{
	// �e�X�e�B�b�N�̓��͒l���f�b�h�]�[���ȉ��Ȃ���͒l��0�ɂ���
	if ((m_joyKeyState.Gamepad.sThumbLX > LEFT_JOYSTICK_DEADZONE ||
		m_joyKeyState.Gamepad.sThumbLX < -LEFT_JOYSTICK_DEADZONE) ||
		(m_joyKeyState.Gamepad.sThumbLY > LEFT_JOYSTICK_DEADZONE ||
			m_joyKeyState.Gamepad.sThumbLY < -LEFT_JOYSTICK_DEADZONE))
	{//���X�e�B�b�N
		float VecX = m_joyKeyState.Gamepad.sThumbLX / 32767.0f;
		float VecY = m_joyKeyState.Gamepad.sThumbLY / 32767.0f;
		return { VecX ,VecY };
	}
	else
	{
		return { 0.0f,0.0f };
	}
}
//==========================================================================================
//�E�X�e�B�b�N�̕����x�N�g�����擾
//==========================================================================================
D3DXVECTOR2 CJoypad::GetJoyStickVecR()
{
	// �e�X�e�B�b�N�̓��͒l���f�b�h�]�[���ȉ��Ȃ���͒l��0�ɂ���
	if ((m_joyKeyState.Gamepad.sThumbRX > RIGHT_JOYSTICK_DEADZONE ||
		m_joyKeyState.Gamepad.sThumbRX < -RIGHT_JOYSTICK_DEADZONE) ||
		(m_joyKeyState.Gamepad.sThumbRY > RIGHT_JOYSTICK_DEADZONE ||
			m_joyKeyState.Gamepad.sThumbRY < -RIGHT_JOYSTICK_DEADZONE))
	{//���X�e�B�b�N
		float VecX = sinf(atan2f((float)m_joyKeyState.Gamepad.sThumbRX * 0.01f, (float)m_joyKeyState.Gamepad.sThumbRY * 0.01f));
		float VecY = cosf(atan2f((float)m_joyKeyState.Gamepad.sThumbRX * 0.01f, (float)m_joyKeyState.Gamepad.sThumbRY * 0.01f));
		return { VecX ,VecY };
	}
	else
	{
		return { 0.0f,0.0f };
	}

}
//==========================================================================================
//�X�e�B�b�N�̃g���K�[����̎擾
//==========================================================================================
bool CJoypad::GetJoyStickTrigger(JOYKEY joykey, JOYSTICK joystick)
{
	if (joykey == JOYPAD_LEFT_THUMB)
	{
		switch (joystick)
		{
		case JOYSTICK_DLEFT:
			return (m_joyKeyState.Gamepad.sThumbLX <= -RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbLX >= -RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DRIGHT:
			return (m_joyKeyState.Gamepad.sThumbLX >= RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbLX <= RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DUP:
			return (m_joyKeyState.Gamepad.sThumbLY >= RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbLY <= RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DDOWN:
			return (m_joyKeyState.Gamepad.sThumbLY <= -RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbLY >= -RIGHT_JOYSTICK_DEADZONE);
			break;
		}
	}
	else if (joykey == JOYPAD_RIGHT_THUMB)
	{
		switch (joystick)
		{
		case JOYSTICK_DLEFT:
			return (m_joyKeyState.Gamepad.sThumbRX <= -RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbRX >= -RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DRIGHT:
			return (m_joyKeyState.Gamepad.sThumbRX >= RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbRX <= RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DUP:
			return (m_joyKeyState.Gamepad.sThumbRY >= RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbRY <= RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DDOWN:
			return (m_joyKeyState.Gamepad.sThumbRY <= -RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbRY >= -RIGHT_JOYSTICK_DEADZONE);
			break;
		}
	}
}
//==========================================================================================
//�X�e�B�b�N�̃����[�X����̎擾
//==========================================================================================
bool CJoypad::GetJoyStickRelease(JOYKEY joykey, JOYSTICK joystick)
{
	if (joykey == JOYPAD_LEFT_THUMB)
	{
		switch (joystick)
		{
		case JOYSTICK_DLEFT:
			return (m_joyKeyState.Gamepad.sThumbLX >= -RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbLX <= -RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DRIGHT:
			return (m_joyKeyState.Gamepad.sThumbLX <= RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbLX >= RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DUP:
			return (m_joyKeyState.Gamepad.sThumbLY <= RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbLY >= RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DDOWN:
			return (m_joyKeyState.Gamepad.sThumbLY >= -RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbLY <= -RIGHT_JOYSTICK_DEADZONE);
			break;
		}
	}
	else if (joykey == JOYPAD_RIGHT_THUMB)
	{
		switch (joystick)
		{
		case JOYSTICK_DLEFT:
			return (m_joyKeyState.Gamepad.sThumbRX >= -RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbRX <= -RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DRIGHT:
			return (m_joyKeyState.Gamepad.sThumbRX <= RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbRX >= RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DUP:
			return (m_joyKeyState.Gamepad.sThumbRY <= RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbRY >= RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DDOWN:
			return (m_joyKeyState.Gamepad.sThumbRY >= -RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbRY <= -RIGHT_JOYSTICK_DEADZONE);
			break;
		}
	}
}
//==========================================================================================
//�X�e�B�b�N�̃��s�[�g����̎擾
//==========================================================================================
bool CJoypad::GetJoyStickRepeat(JOYKEY joykey, JOYSTICK joystick)
{
	if (joykey == JOYPAD_LEFT_THUMB)
	{
		switch (joystick)
		{
		case JOYSTICK_DLEFT:
			return (m_joyKeyState.Gamepad.sThumbLX <= -RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbLX <= -RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DRIGHT:
			return (m_joyKeyState.Gamepad.sThumbLX >= RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbLX >= RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DUP:
			return (m_joyKeyState.Gamepad.sThumbLY >= RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbLY >= RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DDOWN:
			return (m_joyKeyState.Gamepad.sThumbLY <= -RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbLY <= -RIGHT_JOYSTICK_DEADZONE);
			break;
		}
	}
	else if (joykey == JOYPAD_RIGHT_THUMB)
	{
		switch (joystick)
		{
		case JOYSTICK_DLEFT:
			return (m_joyKeyState.Gamepad.sThumbRX <= -RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbRX <= -RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DRIGHT:
			return (m_joyKeyState.Gamepad.sThumbRX >= RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbRX >= RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DUP:
			return (m_joyKeyState.Gamepad.sThumbRY >= RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbRY >= RIGHT_JOYSTICK_DEADZONE);
			break;
		case JOYSTICK_DDOWN:
			return (m_joyKeyState.Gamepad.sThumbRY <= -RIGHT_JOYSTICK_DEADZONE && m_joyKeyOldState.Gamepad.sThumbRY <= -RIGHT_JOYSTICK_DEADZONE);
			break;
		}
	}
}
