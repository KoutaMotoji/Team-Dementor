//===============================================================================
//
//  �v���C���[�Ď��N���X(player_observer.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "player_observer.h"
#include "manager.h"

std::shared_ptr<CPlayerObserver> CPlayerObserver::_instance = nullptr;
//======================================================================
//�v���C���[����
//======================================================================
void CPlayerObserver::PlayerSearch()
{
	//���ɒ��g�����邩���m�F
	if (pPlayer != nullptr) return;
	
	//�v���C���[�̌���
	for (int j = 0; j < SET_PRIORITY; ++j) {//�v���C�I���e�B
		for (int i = 0; i < MAX_OBJECT; ++i) {//�I�u�W�F�N�g�ԍ�
			//�I�u�W�F�N�g�|�C���^��null�`�F�b�N
			CObject* pObj = CObject::GetObjects(j, i);
			if (pObj == nullptr) continue;

			//�I�u�W�F�N�g�̃^�C�v���m�F
			CObject::TYPE type = pObj->GetType();
			if (type != CObject::TYPE::TYPE_3D_PLAYER) continue;

			//�v���C���[���_�E���L���X�g���Anull�`�F�b�N
			CPlayerX* pP = dynamic_cast<CPlayerX*>(pObj);
			if (pP == nullptr) continue;

			pPlayer = pP;	//���
		}
	}
}

//======================================================================
//�m�ۂ����v���C���[��j��
//======================================================================
void CPlayerObserver::PlayerObsDestroy()
{
	if (pPlayer != nullptr)
	{
		pPlayer = nullptr;
	}
}

//======================================================================
//�v���C���[�̍��W���擾
//======================================================================
D3DXVECTOR3 CPlayerObserver::GetPlayerPos()
{
	if (pPlayer != nullptr)
	{
		return pPlayer->GetPos();
	}
	return { 0.0f,0.0f,0.0f };
}

//======================================================================
// �v���C���[�̈ړ��ʂ��擾
//======================================================================
D3DXVECTOR3 CPlayerObserver::GetPlayerMove()
{
	if (pPlayer != nullptr)
	{
		return pPlayer->GetMove();
	}
	return { 0.0f,0.0f,0.0f };
}

//======================================================================
// �v���C���[�̗̑͂��擾
//======================================================================
int CPlayerObserver::GetPlayerLife()
{
	if (pPlayer != nullptr)
	{
		return 0;
	}
	return 0;
}

//======================================================================
// �v���C���[�̃|�C���^���擾
//======================================================================
CPlayerX* CPlayerObserver::GetPlayer()
{
	if (pPlayer != nullptr)
	{
		return pPlayer;
	}
	return nullptr;
}