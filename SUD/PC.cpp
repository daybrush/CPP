#include "stdafx.h"
#include "PC.h"

CPC::CPC(void)
{
	m_Perspective = DIR_RIGHT;
	m_is_over = false;
	m_nextStage = false;
	m_type = PC;
	m_name = "�÷��̾�";
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
void CPC::AttackStraight(CGameMap *map) {
	if(map->GetNo() < 4) {
		CLog::GetInstance()->Add("4�� �ʺ��� ������ ��ų�Դϴ�.");
		return;
	} 
	if(m_mp < 10) {
		CLog::GetInstance()->Add("MP�� �����մϴ�.");
		return;
	}
	CLog::GetInstance()->Add("[�ʹٴٴ�] ��ų �ߵ�");
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
	int power = (int) (m_power * 1.1);//1.1��
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
		//�ڽ��� �ٶ󺸰� �ִ� �������� ������ ����.
	}
}
void CPC::AttackWide(CGameMap *map) {
	if(map->GetNo() < 9) {
		CLog::GetInstance()->Add("3�б� ���� ������ ��ų�Դϴ�.");
		return;
	} 
	if(m_mp < 20) {
		CLog::GetInstance()->Add("MP�� �����մϴ�.");
		return;
	}
	CLog::GetInstance()->Add("[����ġ��] ��ų �ߵ�");
	m_skillType = 2;
	MinusMp(20);
	Position pos = m_position;
	int power = (int) (m_power * 2);//1.5�� ����
	
	//�����¿� �밢�� ����.
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

	Position pos = m_position;//�ڱ� ��ġ���� ���� �ִ� ���� ������ ��ġ
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
