//===============================================================================
//
//  当たり判定可視化線クラス(debug_line.cpp)
//								制作：元地弘汰
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
	int _MAX_SPHIRE_SLICE = 8; // 経線の数
	int _MAX_SPHIRE_STACK = 8; // 緯線の数
	int _MAX_CYLINDER_LINE = 18;
	int _MAX_CORNER = 6;
	int _MAX_STEP = 2;
	float _CYLINDER_HEIGHT = 300.0f;
	int _DRAW_POINTCNT = 2;				//連続して描画する頂点数
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
	// 頂点の生成（球状）
	for (int j = 0; j <= _MAX_SPHIRE_SLICE; ++j)
	{
		float phi = D3DX_PI * j / _MAX_SPHIRE_SLICE; // 緯度角
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
			float theta = 2.0f * D3DX_PI * i / _MAX_SPHIRE_STACK; // 経度角

			D3DXVECTOR3 vec3 = {};

			vec3.x = m_fRadius * sinf(phi) * cosf(theta);
			vec3.y = m_fRadius * cosf(phi);
			vec3.z = m_fRadius * sinf(phi) * sinf(theta);

			m_DrawPoint.push_back({ vec3.x, vec3.y,vec3.z });
		}
	}

	// 線を結ぶインデックスの設定（横方向：緯線）

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
	// 線を結ぶインデックスの設定（縦方向：経線）
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
	// ライトの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// カメラ・射影行列などを取得
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
	// ライトの有効化
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
	//半径をもとに頂点を生成
	for (int i = 0; i < _MAX_STEP; ++i) {
		for (int j = 0; j < _MAX_CORNER; ++j) {
			float radian = (((float)j) / (float)_MAX_CORNER);
			pos.x = (cosf(radian * 2 * D3DX_PI) * m_fRadius);
			pos.z = (sinf(radian * 2 * D3DX_PI) * m_fRadius);
			pos.y = i * _CYLINDER_HEIGHT;
			m_DrawPoint.push_back(pos);
		}
	}
	//始点と終点のインデックス番号の設定
	int nLoop{};
	IdxPair IdxPair{};
	//上段のインデックス番号を設定
	for (int X = 0; X < _MAX_CORNER - 1; ++X)
	{
		IdxPair.Start = X;
		IdxPair.End = X + 1;
		m_IdxPair.push_back(IdxPair);
	}
	IdxPair.Start = _MAX_CORNER - 1;
	IdxPair.End = 0;
	m_IdxPair.push_back(IdxPair);
	//下段のインデックス番号を設定
	for (int X = 0; X < _MAX_CORNER - 1; ++X)
	{
		IdxPair.Start = X + _MAX_CORNER;
		IdxPair.End = X + 1 + _MAX_CORNER;
		m_IdxPair.push_back(IdxPair);
	}
	IdxPair.Start = (_MAX_CORNER *2)- 1;
	IdxPair.End = _MAX_CORNER;
	m_IdxPair.push_back(IdxPair);
	//上下の頂点を繋ぐよ
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
	// ライトの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// カメラ・射影行列などを取得
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
	// ライトの有効化
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
