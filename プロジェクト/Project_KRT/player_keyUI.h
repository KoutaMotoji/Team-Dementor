//===============================================================================
//
//  �v���C���[�{�^��UI����(player_keyUI.cpp)
//								����F���n�O��
// 
//===============================================================================
#ifndef _PLAYER_KEYUI_H_
#define _PLAYER_KEYUI_H_

#include "scene.h"
#include "object2D.h"


class CButtonUI : public CObject2D
{
public:
	CButtonUI() {};
	~CButtonUI()override = default;
	void Init()override;
	void Update()override;

	static CButtonUI* Create(D3DXVECTOR3 pos);
	static CButtonUI* Create(D3DXVECTOR3 pos,int s);

private:
};

class CCTBarUI :public CObject2D
{
public:
	CCTBarUI():m_EndFrag(false){};		//�R���X�g���N�^
	~CCTBarUI()override = default;				//�f�X�g���N�^
	void Init()override;		//������
	void Update()override;
	void Draw()override;

	inline bool GetEndFrag() { return m_EndFrag; }
	inline void ResetGauge() { m_GaugeValue = m_MaxValue; }
	static CCTBarUI* Create(int MaxValue);
private:
	int m_GaugeValue;
	int m_MaxValue;
	bool m_EndFrag;
};
#endif