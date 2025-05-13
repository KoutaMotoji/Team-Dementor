//===============================================================================
//
//  �e�Ǘ��N���X�̈ꊇ�Ǘ��N���X(manager.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

#include "renderer.h"
#include "sound.h"
#include "texture.h"
#include "keyboard.h"
#include "joypad.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "fade.h"

class CManager
{
private:
	CManager();
	static CManager* _instance;

public:
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	static CManager* GetInstance()	//�V���O���g���p�C���X�^���X
	{
		if (_instance == nullptr)
		{//����p��������
			_instance = new CManager;
		}
		return _instance;
	}
	inline CRenderer* GetRenderer() { return m_pRenderer; };
	inline CKeyboard* GetKeyboard() { return m_pKeyboard; };
	inline CTexture* GetTexture() { return m_pTexture; };
	inline CJoypad* GetJoypad() { return m_pJoypad; };
	inline CSound* GetSound() { return m_pSound; }
	inline CCamera* GetCamera() { return m_pCamera; };
	inline CLight* GetLight() { return m_pLight; };
	inline CScene* GetScene() { return m_pScene; };
	inline CFade* GetFade() { return m_pFade; };
	 void SetMode(CScene::MODE mode);
	 const int MAP_SLICE_X;
	 const int MAP_SLICE_Y;
private:
	 CRenderer* m_pRenderer;
	 CKeyboard* m_pKeyboard;
	 CTexture* m_pTexture;
	 CJoypad* m_pJoypad;
	 CSound* m_pSound;
	 CCamera* m_pCamera;
	 CLight* m_pLight;
	 CScene* m_pScene;
	 CFade* m_pFade;
};

#endif