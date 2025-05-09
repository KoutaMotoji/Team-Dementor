//===============================================================================
//
//		�L�[�{�[�h���͊Ǘ��N���X(input.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "input.h"

class CMouse :public CInput
{
public:
	static const int NUM_MOUSE_MAX = 3; //�}�E�X�̃L�[��
	CMouse();
	~CMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	D3DXVECTOR3 GetMouseMove(void);
	void Debug();
private:
	DIMOUSESTATE m_KeyStateTrigger; //�}�E�X�̃g���K�[���
	DIMOUSESTATE m_KeyStateRelease; //�}�E�X�̃����[�X���
	DIMOUSESTATE m_KeyState; //�}�E�X�̃v���X���
	DIMOUSESTATE m_zdiMouseMove; //�}�E�X���[�u
	D3DXVECTOR3 m_MousePos;
	D3DXVECTOR3 m_MouseMove;
};

#endif
