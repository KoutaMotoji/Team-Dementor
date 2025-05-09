//===============================================================================
//
//  ���b�V���V�����_�[�̏���(object3D.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _MESH_CYLINDER_H_
#define _MESH_CYLINDER_H_

#include "main.h"
#include "object.h"

class CMeshCylinder :public CObject
{
public:
	CMeshCylinder(int nPliority = 0);				//�R���X�g���N�^
	~CMeshCylinder()override;		//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��
	static CMeshCylinder* Create(D3DXVECTOR3 pos);

	inline D3DXVECTOR3 GetPos() { return m_pos; }
private:
	int m_nVtx;

	D3DXVECTOR3 m_pos, m_rot;
	D3DXMATRIX m_mtx;

	//�e�N�X�`��
	LPDIRECT3DTEXTURE9 m_apTexMeshCylinder;
	//���_���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMeshCylinder;
	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuffMeshCylinder;


};

#endif