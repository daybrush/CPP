#include "stdafx.h"
#include "Data.h"
#include <fstream>
CData::CData(void)
{
}


CData::~CData(void)
{
}
//문자열로 된 ' '으로 나누기
std::string getStringFileItem(std::ifstream &istream)
{
	std::string item;
	std::getline(istream, item, ' ');
	return item;
}

//주로 숫자를 많이 가져오니까 string으로 가져오고 int로 변환한다.
int getIntFileItem(std::ifstream &istream) {
	std::string item;
	std::getline(istream, item, ' ');
	int	intItem = atoi(item.c_str());

	return intItem;
}
//그런데 한 줄의 마지막은 ' '로 가져오면 안된다. 다음 줄까지 가져가버린다...
int getIntFileLastItem(std::ifstream &istream) {
	std::string item;
	std::getline(istream, item);
	int	intItem = atoi(item.c_str());

	return intItem;
}
CMob* CData::LoadMob(int mobNo) {
	char buf[100];
	sprintf_s(buf, "mob/mob%d.txt",mobNo);
	/*
	몹 이름
	hp mp exp
	attack defense
	*/

	std::ifstream mobFile(buf);
	
	std::string mobName;
	std::getline(mobFile, mobName);


	CMob* mob = new CMob();
	mob->SetName(mobName);
	
	int hp = getIntFileItem(mobFile);
	int mp = getIntFileItem(mobFile);
	int exp = getIntFileLastItem(mobFile);

	mob->SetExp(exp);
	mob->SetMaxExp(exp);
	mob->SetHp(hp);
	mob->SetMaxHp(hp);
	mob->SetMp(mp);
	mob->SetMaxMp(mp);
	
	int power = getIntFileItem(mobFile);
	int defense = getIntFileLastItem(mobFile);
	mob->SetPower(power);
	mob->SetDefense(defense);
	mobFile.close();


	printf_s("LoadMob %d HP : %d, MP:%d, POWER : %d\n", mobNo,hp, mp, power);
	return mob;
}

CGameMap* CData::LoadMap(int mapNo) {
	char buf[20];
	sprintf_s(buf, "map/map%d.txt",mapNo);
	/*
	이름
	맵 설명
	가로 세로
	BLOCK 1 x y
	MOB mob번호 x y
	*/

	
	std::ifstream mapFile(buf);
	if(!mapFile)
		return nullptr;

	std::string mapName;
	
	std::getline(mapFile, mapName);
	
	std::string mapDetail;
	std::getline(mapFile, mapDetail);

	

	
	int	mapWidth = getIntFileItem(mapFile);
	int	mapHeight =  getIntFileLastItem(mapFile);
	
	printf_s("size : %d %d\n", mapWidth, mapHeight);

	CGameMap* map = new CGameMap();
	map->SetNo(mapNo);
	map->SetName(mapName);
	map->SetSize(mapWidth, mapHeight);
	map->SetDetail(mapDetail);

	while(!mapFile.eof())
	{
		std::string type;
		std::getline(mapFile, type, ' ');

		int no = getIntFileItem(mapFile);
		int x = getIntFileItem(mapFile);
		int y = getIntFileLastItem(mapFile);

		printf_s("-> %s %d %d %d\n", type.c_str(), no, x, y);

		if(type == "MOB") {
			if(map->GetMapInfo(x, y)->pChracter != nullptr)
				printf_s("이미 몬스터가 존재합니다.\n");
			else
				map->GetMapInfo(x, y)->pChracter = LoadMob(no);
		} else if(type == "BLOCK") {
			map->GetMapInfo(x, y)->pChracter = new CBlock();
		}
	}
	mapFile.close();

	//int width = atoi("asd");

	//delete map;

	return map;
}