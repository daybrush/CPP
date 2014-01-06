#include "stdafx.h"
#include "PC.h"

CPC::CPC(void)
{
	m_Perspective = DIR_RIGHT;
	m_is_over = false;
	m_nextStage = false;
	m_type = PC;
	m_name = "플레이어";
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
void CPC::AttackStraight(CGameMap *map) {
	if(map->GetNo() < 4) {
		CLog::GetInstance()->Add("4번 맵부터 가능한 스킬입니다.");
		return;
	} 
	if(m_mp < 10) {
		CLog::GetInstance()->Add("MP가 부족합니다.");
		return;
	}
	CLog::GetInstance()->Add("[와다다다] 스킬 발동");
	m_skillType = 1;
	MinusMp(10);
	int x = 0;
	int y = 0;
	switch(m_Perspective) {
	case DIR_UP:
		y = -1;
		break;
	case DIR_DOWN:
		y = 1;
		break;
	case DIR_LEFT:
		x = -1;
		break;
	case DIR_RIGHT:
		x = 1;
		break;
	default:
		return;
	}

	Position pos = m_position;
	bool flag = true;
	int power = (int) (m_power * 1.1);//1.1배
	while(flag) {
		if(pos.x >= map->GetWidth() || pos.x < 0 || pos.y < 0 || pos.y >= map->GetHeight()) {
			flag = false;
			break;
		}
		MapInfo* mapinfo = map->GetMapInfo(pos.x, pos.y);
		
		if(map->IsShow(pos.x, pos.y) && mapinfo && mapinfo->pChracter)
			mapinfo->pChracter->Attacked(this, power, false);

		pos.x += x;
		pos.y += y;
		//자신이 바라보고 있는 방향으로 쭉쭉쭉 공격.
	}
}
void CPC::AttackWide(CGameMap *map) {
	if(map->GetNo() < 9) {
		CLog::GetInstance()->Add("3학기 부터 가능한 스킬입니다.");
		return;
	} 
	if(m_mp < 20) {
		CLog::GetInstance()->Add("MP가 부족합니다.");
		return;
	}
	CLog::GetInstance()->Add("[벼락치기] 스킬 발동");
	m_skillType = 2;
	MinusMp(20);
	Position pos = m_position;
	int power = (int) (m_power * 2);//1.5배 공격
	
	//상하좌우 대각선 포함.
	for(int i = -1; i <= 1; ++i) {
		for(int j = -1; j <= 1; ++j) {
			int x = pos.x + i;
			int y = pos.y + j;
			if(x >= map->GetWidth() || x < 0 || y < 0 || y >= map->GetHeight())
				continue;
			
			MapInfo* mapinfo = map->GetMapInfo(x, y);
			if(map->IsShow(x, y) && mapinfo && mapinfo->pChracter)
				mapinfo->pChracter->Attacked(this, power, false);
		}
	}
}
void CPC::Attack(CGameMap* map) {

	Position pos = m_position;//자기 위치에서 보고 있는 방향 다음의 위치
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
