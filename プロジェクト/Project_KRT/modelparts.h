//===============================================================================
//
//  C++�g����3D�Q�[��(modelparts.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _MODELPARTS_H_
#define _MODELPARTS_H_

#include "main.h"

#define MAX_MODEL_TEX	(10)

class CModelParts 
{
public:
	CModelParts();		//�R���X�g���N�^
	~CModelParts();		//�f�X�g���N�^
	HRESULT Init();
	void Uninit();
	void Draw();
	static CModelParts* Create(D3DXVECTOR3 pos,const char* apFileName);
	void SetParent(CModelParts* pParent);

	void BindModel(const char* apFileName);	//���f���ǂݍ��� 
	void SetModelSize();								//���f���T�C�Y�ő�l�E�ŏ��l���擾

	D3DXVECTOR3& GetPos() { return m_pos; };			//���f���ʒu�擾
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };		//���f���ʒu�ύX
	D3DXVECTOR3& GetRot() { return m_rot; };			//���f����]�擾
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };		//���f����]�ύX
	D3DXVECTOR3& GetSize() { return m_size; };			//���f���g�k�擾
	void SetSize(D3DXVECTOR3 size) { m_size = size; };	//���f���g�k�ύX
	void SetDefault() { m_defaultPos = m_pos; m_defaultRot = m_rot; };	//�ʒu�E��]�����l�ݒ�
	int GetIndex() { return m_nIdx; };					//�C���f�b�N�X�ԍ��擾
	void SetIndex(int Idx) { m_nIdx = Idx; };			//�C���f�b�N�X�ԍ��ݒ�
	D3DXVECTOR3 GetDefaultPos() { return m_defaultPos; };	//�ʒu�����l�擾
	D3DXVECTOR3 GetDefaultRot() { return m_defaultRot; };	//��]�����l�擾
	D3DXMATRIX& GetWorldMatrix() { return m_mtxWorld; };	//�}�g���b�N�X�擾

	D3DXVECTOR3 GetModelMin() { return m_vtxMinModel; }		//�ő�l�擾
	D3DXVECTOR3 GetModelMax() { return m_vtxMaxModel; }		//�ŏ��l�擾

	D3DXVECTOR3* GetRadius() { return &m_radius; };			//���a�擾

private:
	//X�t�@�C���Ǘ��ɕK�v�ȃf�[�^
	LPDIRECT3DTEXTURE9 m_pTextureObjectX[MAX_MODEL_TEX];	//���f���ɓ\��t����e�N�X�`���Ǘ�
	LPD3DXMESH m_pMesh;				//���f���̃��b�V�����
	LPD3DXBUFFER m_pBuffMat;		//���f���̃o�b�t�@
	DWORD m_dwNumMat;				//�}�e���A��
	D3DXVECTOR3 m_vtxMinModel, m_vtxMaxModel;	//���f���̃T�C�Y�i�[�p

	//�I�u�W�F�N�g���
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_defaultPos;	//�����ʒu
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_defaultRot;	//�����̌���
	D3DXVECTOR3 m_size;			//�傫��
	D3DXVECTOR3 m_radius;		//���a

	int m_nIdx;
	CModelParts* m_pParent;		//�e�̃��f���̃|�C���^
};

#endif