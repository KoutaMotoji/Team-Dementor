//===============================================================================
//
//		キーボード入力管理クラス(input.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "input.h"

class CMouse :public CInput
{
public:
	static const int NUM_MOUSE_MAX = 3; //マウスのキー数
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
	DIMOUSESTATE m_KeyStateTrigger; //マウスのトリガー情報
	DIMOUSESTATE m_KeyStateRelease; //マウスのリリース情報
	DIMOUSESTATE m_KeyState; //マウスのプレス情報
	DIMOUSESTATE m_zdiMouseMove; //マウスムーブ
	D3DXVECTOR3 m_MousePos;
	D3DXVECTOR3 m_MouseMove;
};

#endif
