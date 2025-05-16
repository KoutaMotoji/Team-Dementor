//===============================================================================
//
//  カメラ処理(camera.h)
//								制作：元地弘汰
// 
//===============================================================================
#include "inimanager.h"
#include "manager.h"

#include "inicpp.h"

namespace
{
	
}
using namespace std;

std::shared_ptr<CiniManager> CiniManager::_instance = nullptr;

string CiniManager::GetINIData(string Filename, string Section, string Keyword)
{
	ini::IniFile myIni;

	string filename = Filename;
	string section = Section;
	string keyword = Keyword;

	string Answer;
	//INIファイルを読み込む
	myIni.load(filename);

	string temp3 = myIni[section][keyword].as<string>();
	if (!temp3.empty())
	{
		Answer = temp3;
	}
	else
	{
		assert(temp3.empty());
	}

	return Answer;
}