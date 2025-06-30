//===============================================================================
//
//  フィールド管理クラス(field_manager.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _FIELD_MANAGER_H_
#define _FIELD_MANAGER_H_

#include "main.h"
#include "objectX.h"
#include "object2D.h"

//前方宣言
class FieldDissolve;

class CField_Manager
{
private:
	static std::shared_ptr<CField_Manager> _instance;
	FieldDissolve* m_FieldDissolve;

	int m_FieldNum;
	bool m_bActibateManager;
	std::vector<CObjectX*> m_vecFieldObj;
public:
	CField_Manager() :m_bActibateManager(false), m_FieldNum(0), m_FieldDissolve(nullptr){}
	~CField_Manager() { }

	static std::shared_ptr<CField_Manager> GetInstance()	{
		if (_instance == nullptr)
		{
			_instance = std::make_shared<CField_Manager>();
		}
		return _instance;
	}
	void Init();
	void Uninit();
	void Update();
	void ChangeField(int Num) { m_vecFieldObj.clear(); m_FieldNum = Num; };
	void RegistObj(CObjectX* objX) {m_vecFieldObj.push_back(objX); }
	void SetField();
};

class FieldDissolve : public CObject2D
{
public:
	FieldDissolve(int nPriority = 5) :CObject2D(nPriority),m_bDraw(false), m_bReachHalf(false), m_bUse(false){}
	~FieldDissolve() {}
	
	void Init()override;
	void Update()override;
	void Draw()override;

	void StartDissolve();
	void RestartDissolve();

	bool GetReach() { return m_bReachHalf; }
	void DrawEnable() { m_bDraw = true; }
	void DrawDisable() { m_bDraw = false; }

	static FieldDissolve* Create();
private:
	bool m_bDraw,m_bReachHalf,m_bUse;
};

#endif