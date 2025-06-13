//===============================================================================
//
//  敵管理クラス(enemy_manager.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include "main.h"

class CEnemy_Manager
{
public:
	std::shared_ptr<CEnemy_Manager>GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = std::make_shared<CEnemy_Manager>();
		}
		return m_instance;
	}
private:
	CEnemy_Manager() {};
	~CEnemy_Manager() = default;
	std::shared_ptr<CEnemy_Manager>m_instance;
};

#endif