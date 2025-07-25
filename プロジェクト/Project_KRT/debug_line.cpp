//===============================================================================
//
//  �����蔻��������N���X(debug_line.cpp)
//								����F���n�O��
// 
//===============================================================================

#include "manager.h"
#include "debug_line.h"

namespace 
{
	float _DEFAULT_LINE = 8;
	std::vector<D3DXVECTOR3> _DEF_VEC3 =
	{
		{-200.0f,-200.0f,-200.0f},
		{200.0f,-200.0f,-200.0f},
		{200.0f,200.0f,-200.0f},
		{200.0f,200.0f,200.0f},
		{-200.0f,200.0f,-200.0f},
		{-200.0f,200.0f,200.0f},
		{200.0f,-200.0f,200.0f},
		{-200.0f,-200.0f,200.0f}
	};
	int _MAX_SPHIRE_SLICE = 8; // �o���̐�
	int _MAX_SPHIRE_STACK = 8; // �ܐ��̐�
	int _MAX_CYLINDER_LINE = 18;
	int _MAX_CORNER = 6;
	int _MAX_STEP = 2;
	float _CYLINDER_HEIGHT = 300.0f;
	int _DRAW_POINTCNT = 2;				//�A�����ĕ`�悷�钸�_��
	float _DRAW_LINEWIDTH = 2.0f;
	D3DXCOLOR _DRAW_COLOR_CYLINDER = { 1.0f,0.1f,1.0f,1.0f };
	D3DXCOLOR _DRAW_COLOR_SPHIRE = { 0.1f,1.0f,1.0f,1.0f };

}
bool CDebugLine::m_bDraw = false;

CDebugLine::~CDebugLine()
{
	m_IdxPair.clear();
	m_DrawPoint.clear();
	if (m_pLine != nullptr)
	{
		m_pLine->Release();
		m_pLine = nullptr;
	}
}

void CDebugLine::Init()
{

}


void CDebugLine::Draw(D3DXVECTOR3 pos)
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F10))
	{
		m_bDraw = !m_bDraw;
	}
}


std::shared_ptr<CDebugLine> CDebugLine::Create()
{
	std::shared_ptr<CDebugLine> instance = std::make_shared<CDebugLine>();

	instance->Init();
	return instance;
}

void CDebugLineSphire::Init()
{
	D3DXVECTOR3 pos{};
	// ���_�̐����i����j
	for (int j = 0; j <= _MAX_SPHIRE_SLICE; ++j)
	{
		float phi = D3DX_PI * j / _MAX_SPHIRE_SLICE; // �ܓx�p
		if (j == 0)
		{
			m_DrawPoint.push_back({ 0.0f,m_fRadius,0.0f });
			continue;
		}
		else if (j == _MAX_SPHIRE_SLICE)
		{
			m_DrawPoint.push_back({ 0.0f,-m_fRadius,0.0f });
			continue;
		}
		for (int i = 0; i <= _MAX_SPHIRE_STACK; ++i)
		{
			float theta = 2.0f * D3DX_PI * i / _MAX_SPHIRE_STACK; // �o�x�p

			D3DXVECTOR3 vec3 = {};

			vec3.x = m_fRadius * sinf(phi) * cosf(theta);
			vec3.y = m_fRadius * cosf(phi);
			vec3.z = m_fRadius * sinf(phi) * sinf(theta);

			m_DrawPoint.push_back({ vec3.x, vec3.y,vec3.z });
		}
	}

	// �������ԃC���f�b�N�X�̐ݒ�i�������F�ܐ��j

	for (int i = 0; i < _MAX_SPHIRE_STACK; ++i)
	{
		m_IdxPair.push_back({0,_MAX_SPHIRE_SLICE + i });
	}
	
	for (int j = 1; j < _MAX_SPHIRE_STACK - 1; ++j)
	{
		for (int i = 0; i < _MAX_SPHIRE_STACK; ++i)
		{
			m_IdxPair.push_back({ (j * _MAX_SPHIRE_SLICE) + i, (j + 1) * _MAX_SPHIRE_SLICE + i });
		}
	}
	// �������ԃC���f�b�N�X�̐ݒ�i�c�����F�o���j
	for (int i = 0; i <= _MAX_SPHIRE_STACK; ++i)
	{
		m_IdxPair.push_back({ _MAX_SPHIRE_SLICE* (_MAX_SPHIRE_SLICE -1)  + i, (_MAX_SPHIRE_SLICE) * (_MAX_SPHIRE_SLICE) -2});
	}

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXCreateLine(pDevice, &m_pLine);
#ifdef _DEBUG
	m_bDraw = true;
	return;
#endif // _DEBUG
	m_bDraw = false;
}

void CDebugLineSphire::Draw(D3DXVECTOR3 pos)
{
#ifdef _DEBUG
	CDebugLine::Draw({ 0.0f,0.0f,0.0f });
	if (!m_bDraw)return;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	// ���C�g�̖�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �J�����E�ˉe�s��Ȃǂ��擾
	D3DXMATRIX matView, matProj, matWorld, matTransform;
	pDevice->GetTransform(D3DTS_VIEW, &matView);
	pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixIdentity(&matWorld);

	matTransform = matWorld * matView * matProj;

	D3DXVECTOR3 BasePos = pos;
	D3DXVECTOR3 BeginPos, EedPos;

	m_pLine->SetAntialias(TRUE);
	m_pLine->SetWidth(_DRAW_LINEWIDTH);
	m_pLine->Begin();

	for (int i = 0; i < m_IdxPair.size(); ++i)
	{
		BeginPos = m_DrawPoint[m_IdxPair[i].Start];
		EedPos = m_DrawPoint[m_IdxPair[i].End];
		BeginPos += BasePos;
		EedPos += BasePos;
		D3DXVECTOR3 DrawPos[2] = {
			BeginPos,
			EedPos
		};
		m_pLine->DrawTransform(DrawPos, _DRAW_POINTCNT, &matTransform, m_col);
	}
	m_pLine->End();
	// ���C�g�̗L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
#endif // !1
}


std::shared_ptr<CDebugLineSphire> CDebugLineSphire::Create(float Radius)
{
	std::shared_ptr<CDebugLineSphire> instance = std::make_shared<CDebugLineSphire>();
	instance->m_fRadius = Radius;
	instance->m_col = _DRAW_COLOR_SPHIRE;
	instance->Init();
	return instance;
}

std::shared_ptr<CDebugLineSphire> CDebugLineSphire::Create(float Radius,D3DXCOLOR col)
{
	std::shared_ptr<CDebugLineSphire> instance = std::make_shared<CDebugLineSphire>();
	instance->m_fRadius = Radius;
	instance->m_col = col;

	instance->Init();
	return instance;
}

void CDebugLineCylinder::Init()
{
	D3DXVECTOR3 pos{};
	//���a�����Ƃɒ��_�𐶐�
	for (int i = 0; i < _MAX_STEP; ++i) {
		for (int j = 0; j < _MAX_CORNER; ++j) {
			float radian = (((float)j) / (float)_MAX_CORNER);
			pos.x = (cosf(radian * 2 * D3DX_PI) * m_fRadius);
			pos.z = (sinf(radian * 2 * D3DX_PI) * m_fRadius);
			pos.y = i * _CYLINDER_HEIGHT;
			m_DrawPoint.push_back(pos);
		}
	}
	//�n�_�ƏI�_�̃C���f�b�N�X�ԍ��̐ݒ�
	int nLoop{};
	IdxPair IdxPair{};
	//��i�̃C���f�b�N�X�ԍ���ݒ�
	for (int X = 0; X < _MAX_CORNER - 1; ++X)
	{
		IdxPair.Start = X;
		IdxPair.End = X + 1;
		m_IdxPair.push_back(IdxPair);
	}
	IdxPair.Start = _MAX_CORNER - 1;
	IdxPair.End = 0;
	m_IdxPair.push_back(IdxPair);
	//���i�̃C���f�b�N�X�ԍ���ݒ�
	for (int X = 0; X < _MAX_CORNER - 1; ++X)
	{
		IdxPair.Start = X + _MAX_CORNER;
		IdxPair.End = X + 1 + _MAX_CORNER;
		m_IdxPair.push_back(IdxPair);
	}
	IdxPair.Start = (_MAX_CORNER *2)- 1;
	IdxPair.End = _MAX_CORNER;
	m_IdxPair.push_back(IdxPair);
	//�㉺�̒��_���q����
	for (int X = 0; X < _MAX_CORNER; ++X)
	{
		IdxPair.Start = X;
		IdxPair.End = X + _MAX_CORNER;
		m_IdxPair.push_back(IdxPair);
	}

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXCreateLine(pDevice, &m_pLine);
#ifdef _DEBUG
	m_bDraw = true;
	return;
#endif // _DEBUG
	m_bDraw = false;
}



void CDebugLineCylinder::Draw(D3DXVECTOR3 pos)
{
#ifdef _DEBUG
	CDebugLine::Draw({ 0.0f,0.0f,0.0f });
	if (!m_bDraw)return;

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	// ���C�g�̖�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �J�����E�ˉe�s��Ȃǂ��擾
	D3DXMATRIX matView, matProj, matWorld, matTransform;
	pDevice->GetTransform(D3DTS_VIEW, &matView);
	pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixIdentity(&matWorld);

	matTransform = matWorld * matView * matProj;

	D3DXVECTOR3 BasePos = pos;
	D3DXVECTOR3 BeginPos, EedPos;

	m_pLine->SetAntialias(TRUE);
	m_pLine->SetWidth(_DRAW_LINEWIDTH);
	m_pLine->Begin();

	for (int i = 0; i < _MAX_CYLINDER_LINE; ++i)
	{
		BeginPos = m_DrawPoint[m_IdxPair[i].Start];
		EedPos = m_DrawPoint[m_IdxPair[i].End];
		BeginPos += BasePos;
		EedPos += BasePos;
		D3DXVECTOR3 DrawPos[2] = {
			BeginPos,
			EedPos
		};
		m_pLine->DrawTransform(DrawPos, _DRAW_POINTCNT, &matTransform, m_col);
	}
	m_pLine->End();
	// ���C�g�̗L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
#endif // !1
}


std::shared_ptr<CDebugLineCylinder> CDebugLineCylinder::Create(float Radius)
{
	std::shared_ptr<CDebugLineCylinder> instance = std::make_shared<CDebugLineCylinder>();
	instance->m_fRadius = Radius;
	instance->m_col = _DRAW_COLOR_CYLINDER;
	instance->Init();
	return instance;
}

std::shared_ptr<CDebugLineCylinder> CDebugLineCylinder::Create(float Radius, D3DXCOLOR col)
{
	std::shared_ptr<CDebugLineCylinder> instance = std::make_shared<CDebugLineCylinder>();
	instance->m_fRadius = Radius;
	instance->m_col = col;
	instance->Init();
	return instance;
}
