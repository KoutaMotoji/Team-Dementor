//=====================================================================================================================
//
//�h�蕔���̏���[fill.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _FILL_H_
#define _FILL_H_

#include "main.h"

//�O���錾
class Gauge;   //�Q�[�W

//�h�蕔��
class Fill
{
public:
	//�R���X�g���N�^
	Fill(Gauge* pGauge , D3DXCOLOR color)
	{
		//�����o�ϐ�������������
		this->m_pGauge = pGauge;   //�Q�[�W
		this->m_pVtxBuffer = nullptr;   //���_�o�b�t�@
		this->m_color = color;   //�F
		this->m_fRatio = 1.0f;   //����
	}

	//�f�X�g���N�^
	~Fill()
	{
	}

	void Init();   //������
	void Uninit();   //�I������
	void Update();   //�X�V����
	void Draw();   //�`�揈��
	void SetRatio(float fRatio) { this->m_fRatio = fRatio; };   //�����̐ݒ菈��
	float GetRatio() { return this->m_fRatio; };   //�����̎擾����

private:
	Gauge* m_pGauge;   //�Q�[�W
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;   //���_�o�b�t�@
	D3DXCOLOR m_color;   //�F
	float m_fRatio;   //����
};

#endif // !_FILL_H_
