#include "stdafx.h"
#include "GameMap.h"

//0으로 초기화
#define ZERO_MEMORY(mem, size) memset(mem, 0, size)

CGameMap::CGameMap(void)
{
	ZERO_MEMORY(m_mapInfo, sizeof(m_mapInfo));
	printf("CREATE MAP");
}

CGameMap::~CGameMap(void)
{
	for(int i = 0; i < MAP_SIZE; ++i) {
		for(int j = 0; j < MAP_SIZE; ++j) {
			
			delete m_mapInfo[i][j].pChracter;
			m_mapInfo[i][j].pChracter = nullptr;

		}
	}
}

void CGameMap::SetCharacterMove(int i, int j, int toI, int toJ) {
	if(toI >= m_width || toI < 0 || toJ < 0 || toJ >= m_height)
		return;
	//몬스터의 이동

	MapInfo* mapinfo = GetMapInfo(i, j);
	if(!mapinfo)
		return;

	CCharacter* character = mapinfo->pChracter;
	
	//MapInfo* tomapinfo = GetMapInfo(toI, toJ);
	
	//갈려고 하는 곳에 장애물 또는 몬스터가 있나 확인
	if(!IsShow(toI, toJ)) {
		delete m_mapInfo[toI][toJ].pChracter;
		//혹시 죽은 몬스터가 있다면 그 자리는 제거.

		m_mapInfo[toI][toJ].pChracter = character;
		m_mapInfo[i][j].pChracter = nullptr;
		//원래 자리는 nullptr로 초기화 

	}
}
MapInfo* CGameMap::GetMapInfo(int x, int y) {
	if(x < 0 || y < 0 || x >= m_width || y >= m_height)
		return nullptr;

	return &m_mapInfo[x][y];
}
bool CGameMap::IsShow(int x, int y) {
	if(x < 0 || y < 0 || x >= m_width || y >= m_height)
		return false;

	if(m_mapInfo[x][y].pChracter == nullptr)
		return false;

	//일단hp가 0이 되면 죽은 상태로 판단.
	if(m_mapInfo[x][y].pChracter->GetHp() == 0)
		return false;

	return true;
}
bool CGameMap::IsNoMonster() {//몬스터가 전부 없는지 확인
	for(int i = 0; i < MAP_SIZE; ++i) {
		for(int j = 0; j < MAP_SIZE; ++j) {		
			if(IsShow(i, j) && m_mapInfo[i][j].pChracter->GetType() != BLOCK)
				 return false;
		}
	}
	return true;
}
std::string CGameMap::GetMapInfoName(int x, int y) {
	//화면에 나타낼 심볼 또는 이름을 나타냄.
	if(x < 0 || y < 0 || x >= m_width || y >= m_height)
		return "";

	MapInfo* mapinfo = GetMapInfo(x, y);
	switch(mapinfo->pChracter->GetType()) {
	case MOB:
		return "Ｍ";
	case NPC:
		return "Ｎ";
	case PC:
		return "Ｐ";
	case BLOCK:
		return "Ｂ";
	}
	return "　";
}