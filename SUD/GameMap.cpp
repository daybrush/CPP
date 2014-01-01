#include "stdafx.h"
#include "GameMap.h"

//0���� �ʱ�ȭ
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
	//������ �̵�

	MapInfo* mapinfo = GetMapInfo(i, j);
	if(!mapinfo)
		return;

	CCharacter* character = mapinfo->pChracter;
	
	//MapInfo* tomapinfo = GetMapInfo(toI, toJ);
	
	//������ �ϴ� ���� ��ֹ� �Ǵ� ���Ͱ� �ֳ� Ȯ��
	if(!IsShow(toI, toJ)) {
		delete m_mapInfo[toI][toJ].pChracter;
		//Ȥ�� ���� ���Ͱ� �ִٸ� �� �ڸ��� ����.

		m_mapInfo[toI][toJ].pChracter = character;
		m_mapInfo[i][j].pChracter = nullptr;
		//���� �ڸ��� nullptr�� �ʱ�ȭ 

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

	//�ϴ�hp�� 0�� �Ǹ� ���� ���·� �Ǵ�.
	if(m_mapInfo[x][y].pChracter->GetHp() == 0)
		return false;

	return true;
}
bool CGameMap::IsNoMonster() {//���Ͱ� ���� ������ Ȯ��
	for(int i = 0; i < MAP_SIZE; ++i) {
		for(int j = 0; j < MAP_SIZE; ++j) {		
			if(IsShow(i, j) && m_mapInfo[i][j].pChracter->GetType() != BLOCK)
				 return false;
		}
	}
	return true;
}
std::string CGameMap::GetMapInfoName(int x, int y) {
	//ȭ�鿡 ��Ÿ�� �ɺ� �Ǵ� �̸��� ��Ÿ��.
	if(x < 0 || y < 0 || x >= m_width || y >= m_height)
		return "";

	MapInfo* mapinfo = GetMapInfo(x, y);
	switch(mapinfo->pChracter->GetType()) {
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