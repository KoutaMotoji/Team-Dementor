//===============================================================================
//
//  リザルトオブジェクト(result_obj.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _TITLEOBJ_H_
#define _TITLEOBJ_H_

#include "main.h"
#include "character.h"
#include "object2D.h"
#include "objectX.h"
#include "billboard.h"

#include "manager.h"

//前方宣言

class CR_Graound :public CObjectX
{
public:
	CR_Graound(int nPriority = 2);				//コンストラクタ
	~CR_Graound()override;		//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//描画
	static CR_Graound* Create();

protected:

private:
};
class CResultBG :public CObject2D
{
public:
	CResultBG(int nPriority = 3):CObject2D(nPriority)  {};		//コンストラクタ
	~CResultBG()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//初期化

	static CResultBG* Create();
private:
};
class CResultBGBack :public CObject2D
{
public:
	CResultBGBack(int nPriority = 2) :CObject2D(nPriority) {};		//コンストラクタ
	~CResultBGBack()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//初期化

	static CResultBGBack* Create();
private:
};
class CResultReview :public CObject2D
{
public:
	CResultReview(int nPriority = 2) :CObject2D(nPriority) {};		//コンストラクタ
	~CResultReview()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//初期化

	static CResultReview* Create(bool bResult);
private:
};
class CResultRank :public CObject2D
{
public:
	CResultRank(int nPriority = 2) :CObject2D(nPriority) {};		//コンストラクタ
	~CResultRank()override = default;				//デストラクタ
	void Init()override;		//初期化
	void Draw()override;		//初期化

	static CResultRank* Create(int nResult);
private:
};
#endif