#include "stdafx.h"
#include "Data.h"
#include <fstream>
CData::CData(void)
{
}


CData::~CData(void)
{
}
//���ڿ��� �� ' '���� ������
std::string getStringFileItem(std::ifstream &istream)
{
	std::string item;
	std::getline(istream, item, ' ');
	return item;
}

//�ַ� ���ڸ� ���� �������ϱ� string���� �������� int�� ��ȯ�Ѵ�.
int getIntFileItem(std::ifstream &istream) {
	std::string item;
	std::getline(istream, item, ' ');
	int	intItem = atoi(item.c_str());

	return intItem;
}
//�׷��� �� ���� �������� ' '�� �������� �ȵȴ�. ���� �ٱ��� ������������...
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
	�� �̸�
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
	�̸�
	�� ����
	���� ����
	BLOCK 1 x y
	MOB mob��ȣ x y
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
				printf_s("�̹� ���Ͱ� �����մϴ�.\n");
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