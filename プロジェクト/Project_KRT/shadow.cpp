//===============================================================================
//
//  �ۉe�p����(shadow.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "shadow.h"
#include "manager.h"
#include "mesh_ground.h"
#include "player_observer.h"

//==========================================================================================
//������
//==========================================================================================
void CShadow::Init()
{
	//�e�N�X�`���̓o�^�E���蓖��
	int nIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\shadow000.jpg");
	BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(nIdx));
	CObject3D::Init();
}

//==========================================================================================
//�`�揈��
//==========================================================================================
void CShadow::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�A���t�@�e�X�g�ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//Z�A���t�@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CObject3D::Draw();

	//�ʏ�̍����ɖ߂��ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//Z�A���t�@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//==========================================================================================
//��������
//==========================================================================================
CShadow* CShadow::Create(D3DXVECTOR3 pos)
{
	CShadow* shadow = new CShadow;

	shadow->SetPolygonParam(pos, DEF_RADIUS, DEF_RADIUS);
	shadow->Init();

	return shadow;
}

//==========================================================================================
//��������(�T�C�Y�w��p�I�[�o�[���[�h)
//==========================================================================================
CShadow* CShadow::Create(D3DXVECTOR3 pos, float radius)
{
	CShadow* shadow = new CShadow;

	shadow->SetPolygonParam(pos, radius, radius);
	shadow->Init();

	return shadow;
}

//==========================================================================================
//�e��n�`���b�V���ɔ��킹�鏈��
//==========================================================================================
void CShadow::SetShadowGround(D3DXVECTOR3 pos)
{
	// �n�`����
	BOOL  bIsHit = false;
	float fLandDistance;
	DWORD dwHitIndex = 0U;
	float fHitU;
	float fHitV;
	D3DXMATRIX mWorld;
	D3DXVECTOR3 vStartl;
	D3DXVECTOR3 vDirl;
	D3DXVECTOR3 vEnd;
	D3DXVECTOR3 objpos = pos;
	LPD3DXMESH pMesh = nullptr;
	for (int j = 0; j < SET_PRIORITY; ++j) {
		for (int i = 0; i < MAX_OBJECT; i++) {
			CObject* pObj = CObject::GetObjects(j, i);
			if (pObj != nullptr) {
				CObject::TYPE type = pObj->GetType();
				if (type == CObject::TYPE::TYPE_3D_MESHOBJECT) {
					CMeshGround* pTest = dynamic_cast<CMeshGround*>(pObj);
					if (pTest != nullptr) {
						if (pTest != nullptr) {
							// �n�`����

							LPD3DXMESH pMesh = nullptr;
							D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

							pMesh = pTest->GetMesh();
							vEnd = objpos + dir;
							D3DXMATRIX objMtx = pTest->GetMatrix();

							// ���C�𓖂Ă�Ώۂ̃}�g���b�N�X�̋t�s����擾���A�n�_�ƏI�_�̍��W�ɑ΂��č��W�ϊ����s���A�ʒu�E��]�E�傫���̕�Ԃ�����
							D3DXMatrixInverse(&mWorld, NULL, &objMtx);
							D3DXVec3TransformCoord(&vStartl, &objpos, &mWorld);
							D3DXVec3TransformCoord(&vEnd, &vEnd, &mWorld);

							vDirl = vEnd - vStartl;
							D3DXVec3Normalize(&vDirl, &vDirl);
							pMesh = pTest->GetMesh();
							D3DXIntersect(pMesh, &vStartl, &vDirl, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, nullptr, nullptr);

							if (bIsHit)
							{
								// ���������|���S���擾
								VERTEX_3D* pVertex;
								if (fLandDistance < 0.2)
								{
									break;
								}
								float size = 2.0 - (4.0f / fLandDistance);

								CObject3D::SetPos({ objpos.x,objpos.y - fLandDistance,objpos.z });
								CObject3D::SetSize(size);

							}
						}
					}
				}
			}
		}
	}
}