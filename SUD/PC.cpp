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
		if(x >= map->GetWidth()) {//���� ���������� ���� �ؽ�Ʈ ���������� ���� ���� üũ.
			if(!map->IsNoMonster()) {
				CLog::GetInstance()->Add("���͸� ���� �����ּ���.");
			} else {
				m_nextStage = true;//�ؽ�Ʈ �����̷� ����� ��ȣ.
			}
			return;
		}
		if(!map->IsShow(x,y) || mapinfo->pChracter->GetType() != BLOCK)//����� �� �Ǵ� ���� ������� �� �� �������� ���Ѵ�.
			Move(dir, map);

	} else {
		m_Perspective = dir;
	}
}

std::string CPC::GetSymbol() {
	switch(m_Perspective) {
	case DIR_UP:
		return "��";
	case DIR_DOWN:
		return "��";
	case DIR_LEFT:
		return "��";
	case DIR_RIGHT:
		return "��";
	}
	return "��";
}
void CPC::Killed(CCharacter *chr) {
	chr;
	CLog::GetInstance()->Add("YOU DIE");
	m_is_over = true;
}
void CPC::Attack(CGameMap* map) {
	//char buffer[1024];
	//sprintf_s(buffer, "%s���� �ֵѷ����ϴ�.",GetName().c_str());	
	//CLog::GetInstance()->Add(buffer);

	Position pos = m_position;//�ڱ� ��ġ���� ���� �ִ� ������ ��ġ
	Position nowpos = m_position;//�ڱ� ��ġ


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

	//�ڱ� ��ġ�� �����¿� ���Ͱ� �ִ��� Ȯ��
	if(map->IsShow(nowpos.x, nowpos.y))
		monster = map->GetMapInfo(nowpos.x, nowpos.y)->pChracter;
	else if(map->IsShow(pos.x, pos.y))
		monster = map->GetMapInfo(pos.x, pos.y)->pChracter;

	//���ͷα׸� �̾��ش�.
	if(monster != nullptr) {
		monster->Attacked(this, m_power, false);
		char buffer2[1024];
		sprintf_s(buffer2, "%s hp %5d / %5d", monster->GetName().c_str(), monster->GetHp(), monster->GetMaxHp() );	
		CLog::GetInstance()->AddMonsterLog(buffer2);
	}
}
