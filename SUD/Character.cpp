#include "stdafx.h"
#include "Character.h"
#include "GameMap.h"

CCharacter::CCharacter(void)
{
	m_position.x = 0;
	m_position.y = 0;

	m_name = "임시요";
	m_exp = 0;

	m_level = 1;
	m_maxhp = m_hp = 20;
	m_maxmp = m_mp = 20;
	m_maxexp = 100;
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
	char buffer[1024];
	sprintf_s(buffer, "%s님이[%s]한테 %d데미지를 입혔습니다.",chr->GetName().c_str(), m_name.c_str(), power );	
	CLog::GetInstance()->Add(buffer);
	
	if(reflection)
		chr->Attacked(this, 3, false);

	MinusHp(chr, power);
	
	if(chr->m_type != PC) {
		char buffer2[1024];
		sprintf_s(buffer2, "%s hp %5d / %5d", GetName().c_str(), GetHp(), GetMaxHp() );	
		CLog::GetInstance()->AddMonsterLog(buffer2);
	}



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
	} else {
		SetExp(m_exp + exp);
	}
}
void CCharacter::LevelUp() {
	m_level = m_level + 1;
	m_exp = 0;
	m_maxexp = m_maxexp + 100;
	CLog::GetInstance()->Add("레벨 업하셨습니다.");
}

Position CCharacter::Move(DIRECTION dir) {
	switch (dir)
	{
	case DIR_UP:
		m_position.y = __max(m_position.y - 1, 0);
		break;
	case DIR_DOWN:
		m_position.y = __min(m_position.y + 1, MAP_SIZE - 1);
		break;
	case DIR_LEFT:
		m_position.x = __max(m_position.x - 1, 0);
		break;
	case DIR_RIGHT:
		m_position.x = __min(m_position.x + 1, MAP_SIZE - 1);;
		break;
	default:
		break;
	}
	return m_position;
}



void CCharacter::PrintPosition() {
	printf_s("Your Position x : %d , y : %d\n", m_position.x, m_position.y);
};