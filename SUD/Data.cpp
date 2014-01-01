#include "stdafx.h"
#include "Data.h"
#include <fstream>
CData::CData(void)
{
}


CData::~CData(void)
{
}

std::string getStringFileItem(std::ifstream &istream)
{
	std::string item;
	std::getline(istream, item, ' ');
	return item;
}
int getIntFileItem(std::ifstream &istream) {
	std::string item;
	std::getline(istream, item, ' ');
	int	intItem = atoi(item.c_str());

	return intItem;
}
int getIntFileLastItem(std::ifstream &istream) {
	std::string item;
	std::getline(istream, item, ' ');
	int	intItem = atoi(item.c_str());

	return intItem;
}
CMob* CData::LoadMob(int mobNo) {
	char buf[100];
	sprintf_s(buf, "mob/mob%d.txt",mobNo);
	/*
	몹 이름
	hp mp exp
	attackType reflection 0.4
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
	char buf[100];
	sprintf_s(buf, "map/map%d.txt",mapNo);
	/*
	이름
	가로 세로
	NPC npc번호 x y
	MOB mob번호 x y
	*/

	
	std::ifstream mapFile(buf);
	if(!mapFile)
		return nullptr;

	std::string mapName;
	std::getline(mapFile, mapName);
	
	std::string mapDetail;
	std::getline(mapFile, mapDetail);

	

	std::string stringMapWidth;
	std::getline(mapFile, stringMapWidth, ' ');
	int	mapWidth = atoi(stringMapWidth.c_str());
	
	std::string stringMapHeight;
	std::getline(mapFile, stringMapHeight);
	int	mapHeight = atoi(stringMapHeight.c_str());
	
	printf_s("size : %d %d\n", mapWidth, mapHeight);

	CGameMap* map = new CGameMap();
	map->SetName(mapName);
	map->SetSize(mapWidth, mapHeight);
	map->SetDetail(mapDetail);

	while(!mapFile.eof())
	{
		std::string type;
		std::string no;
		std::string x;
		std::string y;
		std::getline(mapFile, type, ' ');
		std::getline(mapFile, no, ' ');
		std::getline(mapFile, x, ' ');
		std::getline(mapFile, y);

		int intNo = atoi(no.c_str());
		int intX = atoi(x.c_str());
		int intY = atoi(y.c_str());

		printf_s("-> %s %s %s %s\n", type.c_str(), no.c_str(), x.c_str(), y.c_str());

		if(type == "MOB")
			map->GetMapInfo(intX, intY)->pChracter = LoadMob(intNo);
		else if(type == "BLOCK")
			map->GetMapInfo(intX, intY)->pChracter = new CBlock();

	}
	mapFile.close();

	//int width = atoi("asd");

	//delete map;

	return map;
}