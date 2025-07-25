//===============================================================================
//
//  当たり判定可視化線クラス(debug_line.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _DEBUG_LINE_H_
#define _DEBUG_LINE_H_

#include "main.h"

class CDebugLine
{
public:
	CDebugLine() {};
	virtual ~CDebugLine() ;

	virtual void Init();
	virtual void Draw(D3DXVECTOR3 pos);
	static std::shared_ptr<CDebugLine> Create();
protected:
	std::vector<D3DXVECTOR3> m_DrawPoint;
	struct IdxPair {
		int Start;
		int End;
	};
	std::vector<IdxPair>m_IdxPair;
	LPD3DXLINE m_pLine;
	static bool m_bDraw;
private:
	
};

class CDebugLineSphire : public CDebugLine
{
public:
	CDebugLineSphire() :m_fRadius(0U) {};
	~CDebugLineSphire()override {};

	void Init()override;
	void Draw(D3DXVECTOR3 pos)override;
	void SetColor(D3DXCOLOR col) { m_col = col; }
	static std::shared_ptr<CDebugLineSphire> Create(float Radius);				//生成処理
	static std::shared_ptr<CDebugLineSphire> Create(float Radius,D3DXCOLOR col);//色変更オーバーロード
private:
	float m_fRadius;
	D3DXCOLOR m_col;
};

class CDebugLineCylinder : public CDebugLine
{
public:
	CDebugLineCylinder() :m_fRadius(0U) {};
	~CDebugLineCylinder() override{};

	void Init()override;
	void Draw(D3DXVECTOR3 pos)override;
	static std::shared_ptr<CDebugLineCylinder> Create(float Radius);				//生成処理
	static std::shared_ptr<CDebugLineCylinder> Create(float Radius, D3DXCOLOR col); //色変更オーバーロード
private:
	float m_fRadius;
	D3DXCOLOR m_col;
};

#endif 
