#include "stdafx.h"
#include "MapData.h"
#define ZERO_MEMORY(mem, size) memset(mem, 0, size)

CMapData::CMapData(void)
{
	m_tileCount = 0;
}
CMapData::CMapData(std::string name, int width, int height) {
	m_name = name;
	
	m_size.width = width;
	m_size.height = height;

	m_tileCount = 0;
	ZERO_MEMORY(m_tile, sizeof(m_tile));
}

CMapData::~CMapData(void)
{
}


void CMapData::addTile(int no, TileType type, int x, int y) {
	m_tile[m_tileCount].no = no;
	m_tile[m_tileCount].type = type;
	m_tile[m_tileCount].pos.x = x;
	m_tile[m_tileCount].pos.y = y;
	++m_tileCount;
}