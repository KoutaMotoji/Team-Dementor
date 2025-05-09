//===============================================================================
//
//		���C�g����(light.h)
//								����F���n�O��
// 
//===============================================================================
#include "light.h"
#include "manager.h"

CLight::CLight()
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&m_aLight[i], sizeof(D3DLIGHT9));
	}
}

CLight::~CLight()
{
}

//===============================================================================
//������
//===============================================================================
HRESULT CLight::Init(void)
{
	
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir[3];

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		//���C�g�̎�ނ�ݒ�
		m_aLight[i].Type = D3DLIGHT_DIRECTIONAL;
		//���C�g�̊g�U��
		m_aLight[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//���C�g�̕�����ݒ�
		switch (i)
		{
		case 0:
			vecDir[0] = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
			break;
		case 1:
			vecDir[1] = D3DXVECTOR3(-0.5f, -0.3f, 0.2f);
			break;
		case 2:
			vecDir[2] = D3DXVECTOR3(0.6f, -0.6f, -0.2f);
			break;
		}
		D3DXVec3Normalize(&vecDir[i], &vecDir[i]);
		m_aLight[i].Direction = vecDir[i];

		//���C�g��ݒ肷��
		pDevice->SetLight(i, &m_aLight[i]);
		//���C�g��L���ɂ���
		pDevice->LightEnable(i, TRUE);
	}

	return S_OK;
}

//===============================================================================
//�I��
//===============================================================================
void CLight::Uninit(void)
{

}

//===============================================================================
//�X�V
//===============================================================================
void CLight::Update(void)
{

}