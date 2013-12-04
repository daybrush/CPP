#include "stdafx.h"
#include "GameMap.h"

#define ZERO_MEMORY(mem, size) memset(mem, 0, size)
//0���� �ʱ�ȭ


CGameMap::CGameMap(void)
{
	ZERO_MEMORY(m_mapInfo, sizeof(m_mapInfo));
	printf("CREATE MAP");
}

CGameMap::~CGameMap(void)
{
	for(int i = 0; i < MAP_SIZE; ++i) {
		for(int j = 0; j < MAP_SIZE; ++j) {
			delete m_mapInfo[i][j].pChr;
			m_mapInfo[i][j].pChr = nullptr;
		}
	}
}


MapInfo* CGameMap::GetMapInfo(int x, int y) {
	if(x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE)
		return nullptr;

	return &m_mapInfo[x][y];
}
bool CGameMap::IsShow(int x, int y) {
	if(x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE)
		return false;

	if(m_mapInfo[x][y].pChr == nullptr)
		return false;

	//�ϴ�hp�� 0�� �Ǹ� ���� ���·� �Ǵ�.
	if(m_mapInfo[x][y].pChr->GetHp() == 0)
		return false;

	return true;
}
std::string CGameMap::GetMapInfoName(int x, int y) {
	if(x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE)
		return "";

	MapInfo* mapinfo = GetMapInfo(x, y);
	switch(mapinfo->pChr->GetType()) {
	case MOB:
		return "��";
	case NPC:
		return "��";
	case PC:
		return "��";
	case BLOCK:
		return "��";
	}
	return "��";
}