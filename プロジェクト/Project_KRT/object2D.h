//===============================================================================
//
//  2D�I�u�W�F�N�g���N���X(object2D.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "main.h"
#include "object.h"

class CObject2D:public CObject
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,
		TYPE_GAUGE,
		TYPE_MAX,
	}TYPE_2D;

	CObject2D(int nPriority = 3);		//�R���X�g���N�^
	~CObject2D()override;				//�f�X�g���N�^
	void Init()override;		//������
	void Uninit()override;		//�I��
	void Update()override;		//�X�V
	void Draw()override;		//�`��
	inline D3DXVECTOR3 GetPos() { return m_pos; }				//���W�擾
	inline void AddPos(D3DXVECTOR3 pos) { m_pos += pos; }		//���W�ړ�
	inline void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }		//���W�ύX
	inline D3DXVECTOR3 GetRot() { return m_rot; }				//�p�x�擾
	inline void AddRot(D3DXVECTOR3 rot) { m_rot += rot; }		//�p�x�ړ�
	inline D3DXVECTOR2 GetAnim() { return { (float)m_AnimU,(float)m_AnimV }; }					//�A�j���[�V�����擾
	inline void SetAnim(D3DXVECTOR2 Anim) {m_AnimU = (int)Anim.x; m_AnimV = (int)Anim.y;}		//�A�j���[�V�����ړ�
	inline float GetSize() {return m_fLength * m_fZoom;}					//�傫���擾
	inline void SetZoom(float Zoom) { m_fZoom = Zoom; }						//�傫���ύX
	inline D3DXCOLOR GetColor() { return m_col; }							//�J���[���擾
	inline void SetColor(D3DXCOLOR col) { m_col = col; }					//�J���[��ݒ�
	inline void SetGauge(int value) { m_nCharge = value; }					//�Q�[�W�̃T�C�Y�ύX
	inline void SetGaugeAnim(D3DXVECTOR2 value) { m_GaugeAnim += value; }	//�Q�[�W�̃e�N�X�`���A�j���[�V����
	static CObject2D* Create(D3DXVECTOR3 pos);
	void SetPolygonParam(D3DXVECTOR3 pos, float fHeight, float fWidth);					//�����ݒ�
	void SetPolygonParam(D3DXVECTOR3 pos, float fHeight, float fWidth,D3DXCOLOR col);	//�����ݒ�(�I�[�o�[���[�h)
	void SetPolygonParam(D3DXVECTOR3 pos, float fHeight, float fWidth, int nMaxGauge,bool Reverse);	//�����ݒ�(�Q�[�W�p�I�[�o�[���[�h)
	void BindTexture(LPDIRECT3DTEXTURE9 pTex, int AnimU, int AnimV);	//������e�N�X�`�� /�c���� /������
private:
	float CalcWidth();
	void UpdateNormal();
	void UpdateGaugeLeft();
	void UpdateGaugeRight();

	LPDIRECT3DTEXTURE9 m_pTextureObject2D;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffObject2D;
	D3DXVECTOR2 m_GaugeAnim;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXCOLOR m_col;
	static const int MAX_VERTEX;
	static const int MAX_POLYGON;
	float m_fAngle;
	float m_fLength;
	float m_fHeight;
	float m_fWidth;
	float m_fZoom;
	int m_AnimU, m_AnimV;
	int m_TexSliceU, m_TexSliceV;
	int m_nCharge,m_nMaxGauge;
	bool m_bGaugeReverse;
	TYPE_2D m_type;
};

#endif