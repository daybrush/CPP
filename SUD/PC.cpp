#include "stdafx.h"
#include "PC.h"

CPC::CPC(void)
{
	m_Perspective = DIR_RIGHT;
	m_is_over = false;
	m_nextStage = false;
	m_type = PC;
}


CPC::~CPC(void)
{
}

void CPC::ChangeDir(CGameMap *map, DIRECTION dir) {
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
		mapinfo = map->GetMapInfo(x, y);
		if(x >= map->GetWidth()) {//가장 오른쪽으로 가면 넥스트 스테이지로 가는 것을 체크.
			if(!map->IsNoMonster()) {
				CLog::GetInstance()->Add("몬스터를 전부 없애주세요.");
			} else {
				m_nextStage = true;//넥스트 스테이로 가라는 신호.
			}
			return;
		}
		if(!map->IsShow(x,y) || mapinfo->pChracter->GetType() != BLOCK)//블록일 때 또는 맵을 벗어날려고 할 떄 움직이지 못한다.
			Move(dir, map);

	} else {
		m_Perspective = dir;
	}
}

std::string CPC::GetSymbol() {
	switch(m_Perspective) {
	case DIR_UP:
		return "┻";
	case DIR_DOWN:
		return "┳";
	case DIR_LEFT:
		return "┫";
	case DIR_RIGHT:
		return "┣";
	}
	return "　";
}
void CPC::Killed(CCharacter *chr) {
	chr;
	CLog::GetInstance()->Add("YOU DIE");
	m_is_over = true;
}
void CPC::Attack(CGameMap* map) {
	//char buffer[1024];
	//sprintf_s(buffer, "%s님이 휘둘렀습니다.",GetName().c_str());	
	//CLog::GetInstance()->Add(buffer);

	Position pos = m_position;//자기 위치에서 보고 있는 방향의 위치
	Position nowpos = m_position;//자기 위치


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

	CCharacter* monster = nullptr;

	//자기 위치랑 상하좌우 몬스터가 있는지 확인
	if(map->IsShow(nowpos.x, nowpos.y))
		monster = map->GetMapInfo(nowpos.x, nowpos.y)->pChracter;
	else if(map->IsShow(pos.x, pos.y))
		monster = map->GetMapInfo(pos.x, pos.y)->pChracter;

	//몬스터로그를 뽑아준다.
	if(monster != nullptr) {
		monster->Attacked(this, m_power, false);
		char buffer2[1024];
		sprintf_s(buffer2, "%s hp %5d / %5d", monster->GetName().c_str(), monster->GetHp(), monster->GetMaxHp() );	
		CLog::GetInstance()->AddMonsterLog(buffer2);
	}
}
