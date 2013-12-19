#include "stdafx.h"
#include "Data.h"


CData::CData(void)
{
}


CData::~CData(void)
{
}


void CData::LoadMap() {
	CMapData* mapdata = new CMapData("Çï·Î¿ì ¿ùµå", 12, 12);
	mapdata->addTile(1, NPC, 2, 4);
	mapdata->addTile(1, MOB, 5, 4);
	mapdata->addTile(2, POTAL, 12, 4);//Go To 2
}