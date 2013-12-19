#pragma once

#include "MapData.h"

class CData
{
public:
	CData(void);
	~CData(void);

	void LoadMap();

private:
	CMapData* m_mapdatas[30];
};

