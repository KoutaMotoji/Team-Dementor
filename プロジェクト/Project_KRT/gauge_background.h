//=====================================================================================================================
//
//�Q�[�W�̔w�i�̏���[gauge_background.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _GAUGE_BACKGROUND_H_
#define _GAUGE_BACKGROUND_H_

#include "main.h"

//�O���錾
class Gauge;   //�Q�[�W

//�Q�[�W�̔w�i
class GaugeBackground
{
public:
	//�R���X�g���N�^
	GaugeBackground(Gauge* pGauge)
	{
		//�����o�ϐ�������������
		this->m_pGauge = pGauge;   //�Q�[�W
		this->m_pVtxBuffer = nullptr;   //���_�o�b�t�@
		this->m_pTexture = nullptr;   //�e�N�X�`��
		this->m_color = { 1.0f, 1.0f, 1.0f, 1.0f };   //�F
		this->m_v2AddSize = { 0.0f, 0.0f };   //�T�C�Y�̉��Z�l
	}

	//�f�X�g���N�^
	~GaugeBackground()
	{
	}

	void Init();   //������
	void Uninit();   //�I������
	void Update();   //�X�V����
	void Draw();   //�`�揈��
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { this->m_pTexture = pTexture; };   //�e�N�X�`���̐ݒ菈��
	void SetAddSize(D3DXVECTOR2 v2AddSize) { this->m_v2AddSize = v2AddSize; };   //�T�C�Y�̉��Z�l�̐ݒ菈��

private:
	Gauge* m_pGauge;   //�Q�[�W
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;   //���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;   //�e�N�X�`��
	D3DXCOLOR m_color;   //�F
	D3DXVECTOR2 m_v2AddSize;   //�T�C�Y�̉��Z�l
};

#endif // !_GAUGE_BACKGROUND_H_
