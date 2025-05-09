//===============================================================================
//
//  X�t�@�C���I�u�W�F�N�g���N���X(objectX.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "main.h"
#include "object.h"

#define MAX_OBJ_TEX	(10)

class CObjectX :public CObject
{
public:
	CObjectX(int nPriority = 1);				//�R���X�g���N�^
	~CObjectX()override;		//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��
	void Draw(D3DXCOLOR col);		//�`��(�F�ύX�p�I�[�o�[���[�h)
	void Draw(D3DXMATRIX RotMtx);	//�`��(�N�I�[�^�j�I����]�p�I�[�o�[���[�h)


	inline D3DXVECTOR3 GetPos() { return m_pos; };				//���W�擾
	inline void AddPos(D3DXVECTOR3 pos) { m_pos += pos; };		//���W�ړ�
	inline void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };		//���W�ύX
	inline D3DXVECTOR3 GetRot() { return m_rot; };				//�p�x�擾
	inline void AddRot(D3DXVECTOR3 rot) { m_rot += rot; };		//�p�x�ړ�
	inline void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };		//�p�x�ړ�
	inline void AddSize(D3DXVECTOR3 size) { m_size += size; };
	inline void SetSize(D3DXVECTOR3 size) { m_size = size; };
	inline LPD3DXMESH GetMesh() { return m_pMesh; };			//���b�V���̎擾
	inline D3DXVECTOR3* GetRadius() { return &m_radius; };		//���f���̔��a�擾

	inline D3DXVECTOR3 GetModelMin() { return m_vtxMinModel; };
	inline D3DXVECTOR3 GetModelMax() { return m_vtxMaxModel; };
	inline D3DXMATRIX GetMatrix() { return m_mtxWorld; }
	static CObjectX* Create(D3DXVECTOR3 pos);
	void SetModelParam(D3DXVECTOR3 pos);					//�����ݒ�
	void BindModel(const char* apFileName);	//���f���ǂݍ��� 
	void SetModelSize();
private:
	LPDIRECT3DTEXTURE9 m_pTextureObjectX[MAX_OBJ_TEX];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_radius;		//���a
	D3DXCOLOR m_col;
	
	D3DMATERIAL9 m_defMat;
	D3DXMATRIX m_mtxWorld;
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_dwNumMat;
	D3DXVECTOR3 m_vtxMinModel, m_vtxMaxModel;
};

#endif