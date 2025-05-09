//===============================================================================
//
//		�W���C�p�b�h���͊Ǘ��N���X(input.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#include "input.h"

class CJoypad : public CInput
{
public:
	typedef enum
	{
		JOYPAD_DPAD_UP = 0,
		JOYPAD_DPAD_DOWN,
		JOYPAD_DPAD_LEFT,
		JOYPAD_DPAD_RIGHT,
		JOYPAD_START,
		JOYPAD_BACK,
		JOYPAD_LEFT_THUMB,
		JOYPAD_RIGHT_THUMB,
		JOYPAD_LEFT_SHOULDER,
		JOYPAD_RIGHT_SHOULDER,
		JOYPAD_RIGHT_TRIGGER,
		JOYPAD_LEFT_TRIGGER,
		JOYPAD_A,
		JOYPAD_B,
		JOYPAD_X,
		JOYPAD_Y,
		JOYPAD_MAX
	}JOYKEY;

	typedef enum
	{
		JOYSTICK_DLEFT = 0,
		JOYSTICK_DRIGHT,
		JOYSTICK_DUP,
		JOYSTICK_DDOWN
	}JOYSTICK;

	CJoypad();
	~CJoypad();
	HRESULT Init(HINSTANCE hInstace, HWND hWnd)override;

	void Uninit()override;
	void Update()override;

	bool GetPress(JOYKEY key);		//�L�[�̃v���X���
	bool GetTrigger(JOYKEY key);	//�L�[�̃g���K�[���
	bool GetRelease(JOYKEY key);	//�L�[�̃����[�X���
	bool GetRepeat(JOYKEY key);		//�L�[�̃��s�[�g���

	bool GetJoyStickL(JOYSTICK joystick);						//���X�e�B�b�N�̓��͏��
	bool GetJoyStickR(JOYSTICK joystick);						//�E�X�e�B�b�N�̓��͏��
	bool GetJoyStickTrigger(JOYKEY joykey, JOYSTICK joystick);	//�X�e�B�b�N�̃g���K�[���
	bool GetJoyStickRelease(JOYKEY joykey, JOYSTICK joystick);	//�X�e�B�b�N�̃����[�X���
	bool GetJoyStickRepeat(JOYKEY joykey, JOYSTICK joystick);	//�X�e�B�b�N�̃��s�[�g���

	D3DXVECTOR2 GetJoyStickVecL();
	D3DXVECTOR2 GetJoyStickVecR();

private:

	XINPUT_STATE m_joyKeyState;				//�L�[�̓��͏��
	XINPUT_STATE m_joyKeyOldState;			//�L�[�̉ߋ��̓��͏��
	XINPUT_STATE m_joyKeyStateTrigger;		//�L�[�̃g���K�[������
	XINPUT_STATE m_joyKeyStateRelease;		//�L�[�̃����[�X������
	XINPUT_STATE m_joyKeyStateRepeat;		//�L�[�̃��s�[�g������
};



#endif