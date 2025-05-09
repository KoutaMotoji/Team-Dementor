//===============================================================================
//
//  �Q�[���V�[��(game.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"


constexpr int MAX_TREESET_NUM = 260;

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
};

#endif