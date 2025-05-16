//===============================================================================
//
//  ini�t�@�C���Ǘ��N���X(inimanager.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _INIMANAGER_H_
#define _INIMANAGER_H_

#include "main.h"

//�v���C���[�Ď��N���X
class CiniManager
{
private:
	static std::shared_ptr<CiniManager> _instance;
public:
	//�V���O���g���p�����C���X�^���X
	static const std::shared_ptr<CiniManager> GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = std::make_shared<CiniManager>();
		}
		return _instance;
	}
	std::string GetINIData(std::string Filename, std::string Section, std::string Keyword);//.ini�t�@�C�����������ɓ����֐��A�����珇��ini�t�@�C���� / �Z�N�V������ / �L�[���[�h��
};

#endif 
