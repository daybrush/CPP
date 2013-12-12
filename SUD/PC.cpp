#include "stdafx.h"
#include "PC.h"

CPC::CPC(void)
{
	m_Perspective = DIR_RIGHT;
	m_is_over = false;
}


CPC::~CPC(void)
{
}

void CPC::ChangeDir(CGameMap &map, DIRECTION dir) {
	if(m_Perspective == dir) {
		MapInfo* mapinfo = nullptr;
		int x = m_position.x;
		int y = m_position.y;
		switch(dir) {
		case DIR_UP:
			--y;
			break;
		case DIR_DOWN:
			++y;
			break;
		case DIR_LEFT:
			--x;
			break;
		case DIR_RIGHT:
			++x;
			break;
		}
		mapinfo = map.GetMapInfo(x, y);

		if(!map.IsShow(x,y) || mapinfo->pChr->GetType() != BLOCK)
			Move(dir);

	} else {
		m_Perspective = dir;
	}
}

std::string CPC::GetSymbol() {
	switch(m_Perspective) {
	case DIR_UP:
		return "¦µ";
	case DIR_DOWN:
		return "¦³";
	case DIR_LEFT:
		return "¦´";
	case DIR_RIGHT:
		return "¦²";
	}
	return "¡¡";
}
void CPC::Killed(CCharacter *chr) {
	CLog::Add("YOU DIE");
	m_is_over = true;
}
void CPC::Attack(CGameMap& map) {
	char buffer[1024];
	sprintf_s(buffer, "%s´ÔÀÌ ÈÖµÑ·¶½À´Ï´Ù.",GetName().c_str());	
	CLog::Add(buffer);

	Position pos = m_position;
	switch(m_Perspective) {
	case DIR_UP:
		pos.y = pos.y - 1;
		break;
	case DIR_DOWN:
		pos.y = pos.y + 1;
		break;
	case DIR_LEFT:
		pos.x = pos.x - 1;
		break;
	case DIR_RIGHT:
		pos.x = pos.x + 1;
		break;
	}
	if(map.IsShow(pos.x, pos.y))
		map.GetMapInfo(pos.x, pos.y)->pChr->Attacked(this, 5, true);
}
