//===============================================================================
//
//  ゲームシーン(game.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"


constexpr int MAX_TREESET_NUM = 260;

class CField_Manager;
class CFloorNumberUI;

class CGame : public CScene
{
public:
	CGame();
	~CGame()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

private:
	void MakeRandTree();
	std::shared_ptr< CField_Manager> m_FieldManager;
	CFloorNumberUI* m_FloorNumberUI;
};

#endif