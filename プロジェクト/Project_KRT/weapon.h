//===============================================================================
//
//  �����̏���(weapom.h)
//					����F��|�
// 
//===============================================================================

#ifndef _WEAPOM_H_
#define _WEAPOM_H_

#include "main.h"
#include "objectX.h"
#include "collision.h"

class CWeapon :public CObjectX
{
public:
	CWeapon(int nPriority = 2);				//�R���X�g���N�^
	~CWeapon()override;		//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��

	void OnPickedUp();
	void SetEquipped(bool b) { m_bEquipped = b; }
	bool IsEquipped() const { return m_bEquipped; }
	static CWeapon* Create(D3DXVECTOR3 pos);

protected:


private:
	CHitCircle* m_pHitCircle = nullptr;
	std::vector<std::shared_ptr<CHitCircle>> m_HitCircle;	//�~�̓����蔻��z��

	LPDIRECT3DTEXTURE9 m_pTextureObjectX[MAX_OBJ_TEX];
	DWORD m_dwNumMat;
	LPD3DXMESH m_pMesh;
	float m_baseY;
	bool m_bEquipped = false;
	float m_floatTime; // �㉺�^���p����
};

#endif