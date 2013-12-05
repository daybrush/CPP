#pragma once
#define MAP_SIZE 12
#include "Character.h"
struct MapInfo
{
	// agebreak : 부득이한 경우를 제외하고는 변수명에 약자를 사용하는것은 좋지 못함
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

