//===============================================================================
//
//  iniファイル管理クラス(inimanager.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _INIMANAGER_H_
#define _INIMANAGER_H_

#include "main.h"

//プレイヤー監視クラス
class CiniManager
{
private:
	static std::shared_ptr<CiniManager> _instance;
public:
	//シングルトン用内部インスタンス
	static const std::shared_ptr<CiniManager> GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = std::make_shared<CiniManager>();
		}
		return _instance;
	}
	std::string GetINIData(std::string Filename, std::string Section, std::string Keyword);//.iniファイルから情報を手に入れる関数、左から順にiniファイル名 / セクション名 / キーワード名
};

#endif 
