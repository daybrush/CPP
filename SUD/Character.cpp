#include "stdafx.h"
#include "Character.h"

#include "GameMap.h"
#include <math.h>

CCharacter::CCharacter(void)
{
	m_position.x = 0;
	m_position.y = 0;

	m_name = "임시요";
	m_exp = 0;
	m_level = 0;
	LevelUp();
}


CCharacter::~CCharacter(void)
{
}

void CCharacter::SetPosition(int x, int y) {
	Position pos;
	pos.x = x;
	pos.y = y;
	SetPosition(pos);
}

void CCharacter::Attacked(CCharacter* chr, int power, bool reflection) {
	power = __max(1, power - m_defense);
	int minmaxpower = -5 + rand() % 11;
	power = power + power * minmaxpower / 20;
	//  파워의 범위   3/4파워 ~ 5/4 파워 

	char buffer[1024];
	switch(rand() % ATTACK_COUNT) {
	case HIT:
		sprintf_s(buffer, "%s님이 [%s]에게 %d데미지를 입혔습니다.",chr->GetName().c_str(), m_name.c_str(), power );
		break;
	case CRITICAL:
		power = (int)(power * 1.5);
		sprintf_s(buffer, "%s님이 [%s]에게 %d 크리티컬 데미지를 입혔습니다.",chr->GetName().c_str(), m_name.c_str(), power);
		break;
	case DEFENSE:
		power = (int)(power / 2);
		sprintf_s(buffer, "%s님이[%s]에게 %d 조금 데미지를 입혔습니다.",chr->GetName().c_str(), m_name.c_str(), power);
		break;
	case MISS:
		sprintf_s(buffer, "%s님이 [%s]에게 미스!!!",chr->GetName().c_str(), m_name.c_str());
		power = 0;
		break;
	}

	
	CLog::GetInstance()->Add(buffer);
	

	//반사....
	if(reflection)
		chr->Attacked(this, 3, false);

	MinusHp(chr, power);

}

void CCharacter::MinusHp(CCharacter* chr, int minus) {
	if(m_hp - minus <= 0) {
		m_hp = 0;
		Killed(chr);
	} else {
		m_hp = m_hp - minus;
	}
}
void CCharacter::Killed(CCharacter* chr) {
	CLog::GetInstance()->Add("몬스터를 죽였습니다.");
	
	
	char buf[100];
	sprintf_s(buf, "%d경험치를 얻었습니다.", GetExp());
	CLog::GetInstance()->Add(buf);

	chr->AddExp(GetExp());
}
void CCharacter::AddExp(int exp) {
	if(m_maxexp == 0)
		printf_s("Error\n");
	if(m_exp + exp > m_maxexp) {
		int extraExp = m_exp + exp - m_maxexp;
		LevelUp();
		AddExp(extraExp);
	} else if(m_exp + exp == m_maxexp) {
		LevelUp();
		CLog::GetInstance()->Add("레벨 업하셨습니다.");
	} else {
		SetExp(m_exp + exp);
	}
}
void CCharacter::LevelUp() {
	m_level = m_level + 1;
	m_exp = 0;
	m_maxexp = m_level * 20;
	m_power = m_level * 7;
	m_defense = m_level * 2;
	m_hp = m_maxhp = m_level * 12;
	m_mp = m_maxmp = m_level * 10;
}

Position CCharacter::Move(DIRECTION dir, void *map) {
	CGameMap* c_map = reinterpret_cast<CGameMap *>(map);
	switch (dir)
	{
	case DIR_UP:
		m_position.y = __max(m_position.y - 1, 0);
		break;
	case DIR_DOWN:
		m_position.y = __min(m_position.y + 1, c_map->GetHeight() - 1);
		break;
	case DIR_LEFT:
		m_position.x = __max(m_position.x - 1, 0);
		break;
	case DIR_RIGHT:
		m_position.x = __min(m_position.x + 1, c_map->GetWidth() - 1);
		break;
	default:
		break;
	}
	return m_position;
}



void CCharacter::PrintPosition() {
	printf_s("Your Position x : %d , y : %d\n", m_position.x, m_position.y);
};