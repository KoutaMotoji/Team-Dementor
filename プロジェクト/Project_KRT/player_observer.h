//===============================================================================
//
//  �v���C���[�Ď��N���X(player_observer.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _PLAYER_OBSERVER_H_
#define _PLAYER_OBSERVER_H_

#include "main.h"
#include "xxx_player.h"

//�v���C���[�Ď��N���X
class CPlayerObserver
{
private:
	CPlayerX* pPlayer;
	static std::shared_ptr<CPlayerObserver> _instance;
public:
	CPlayerObserver() { pPlayer = nullptr; }
	//�V���O���g���p�����C���X�^���X
	static const std::shared_ptr<CPlayerObserver> GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = std::make_shared<CPlayerObserver>();
		}
		return _instance;
	}
	void PlayerSearch();
	void PlayerObsDestroy();
	D3DXVECTOR3 GetPlayerPos();
	CPlayerX* GetPlayer();
	D3DXVECTOR3 GetPlayerMove();
	int GetPlayerLife();
};

#endif 
