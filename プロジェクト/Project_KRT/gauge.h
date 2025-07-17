//=====================================================================================================================
//
//�Q�[�W�̏���[gauge.h]
// Author MurataShinnosuke
//
//=====================================================================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "object.h"

//�Q�[�W
class Gauge : public CObject   //(�e)�I�u�W�F�N�g���
{
public:
	//�R���X�g���N�^
	Gauge(D3DXVECTOR3 v3Pos, D3DXVECTOR2 v2Size)
	{
		//�����o�ϐ�������������
		this->m_v3Pos = v3Pos;   //�ʒu
		this->m_v2Size = v2Size;   //�T�C�Y
	}

	//�f�X�g���N�^
	~Gauge()
	{
	}

	virtual void Init() override = 0;   //������
	virtual void Uninit() override = 0;   //�I������
	virtual void Update() override = 0;   //�X�V����
	virtual void Draw() override = 0;   //�`�揈��
	D3DXVECTOR3 GetPos() { return this->m_v3Pos; };   //�ʒu�̎擾����
	D3DXVECTOR2 GetSize() { return this->m_v2Size; };   //�T�C�Y�̎擾����

private:
	D3DXVECTOR3 m_v3Pos;   //�ʒu
	D3DXVECTOR2 m_v2Size;   //�T�C�Y
};

#endif // !_GAUGE_H_
