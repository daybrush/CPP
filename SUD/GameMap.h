#pragma once

#ifndef GAMEMAP
#define GAMEMAP


#define MAP_SIZE 20

#include "Character.h"
struct MapInfo
{
	CCharacter* pChracter;

};


class CGameMap
{
public:
	CGameMap(void);
	~CGameMap(void);
	void SetNo(int no) {m_no = no;}
	int GetNo() {return m_no;}
	void SetName(std::string name) {m_name = name;}
	void SetSize(int width, int height) {m_width = width; m_height = height;}
	void SetDetail(std::string detail) {m_detail = detail;}
	bool IsShow(int x, int y);//몬스터가 죽었는가 또는 해당좌표에 아무것도 없나 좌표에 벗어나 있나..

	int GetWidth() {return m_width;};//맵의 가로 크기
	int GetHeight() {return m_height;};//맵의 세로 크기

	MapInfo* GetMapInfo(int x, int y);//각 좌표에 있는 맵의 정보 즉. 캐릭터의 정보
	std::string GetMapInfoName(int x, int y);//캐릭터의 심볼을 나타남.숙
	std::string GetDetail() {return m_detail;}//맵에 대한 설명

	bool IsNoMonster();//맵에 존재하는 몬스터가 있는지 없는지,
	void SetCharacterMove(int i, int j, int toI, int toJ);//몬스터 이동

protected:
	MapInfo m_mapInfo[MAP_SIZE][MAP_SIZE];

	std::string m_name;
	std::string m_detail;
	int m_no;
	int m_width;
	int m_height;
	
};

#endif