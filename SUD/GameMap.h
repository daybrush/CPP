#pragma once
#define MAP_SIZE 12
#include "Character.h"
struct MapInfo
{
	CCharacter* pChr;

};

class CGameMap
{
public:
	CGameMap(void);
	~CGameMap(void);
	bool IsShow(int x, int y);
	MapInfo* GetMapInfo(int x, int y);
	std::string GetMapInfoName(int x, int y);
protected:
	MapInfo m_mapInfo[MAP_SIZE][MAP_SIZE];
};

