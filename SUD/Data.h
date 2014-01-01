#pragma once

#include "GameMap.h"
#include "Block.h"
#include "Mob.h"

class CData
{
public:
	CData(void);
	~CData(void);
	CMob* LoadMob(int mobNo);
	CGameMap* LoadMap(int mapNo);

private:
};

