#include "stdafx.h"
#include "Character.h"
#include "GameMap.h"

CCharacter::CCharacter(void)
{
	m_position.x = 0;
	m_position.y = 0;

	m_name = "임시요";
	m_exp = 0;

	m_lv = 1;
	m_mhp = m_hp = 20;
	m_mmp = m_mp = 20;
	m_mexp = 100;
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

void CCharacter::Attacked(CCharacter* chr, int damage, bool reflection) {
	char buffer[1024];
/*	
	AttackResult result = ATTACK_COUNT;
	switch (result)
	{
	case ATTACK_HIT:
			printf_s("-- %s는 공격에 (%d)의 피해를 입었다.\n", GetName().c_str(), damage);
			break;
	case ATTACK_MISS:                // 회피시에는 데미지가 없다.
			printf_s("-- %s는 공격을 피했다.\n", GetName().c_str());
			damage = 0;
			break;
	case ATTACK_GUARD:
			printf_s("-- 는 공격을 막았다. (%d)의 피해만 입었다.\n", GetName().c_str(), damage / 2);
			damage = damage / 2;
			break;        
	default:
			break;
	}
*/
	sprintf_s(buffer, "%s님이[%s]한테 %d데미지를 입혔습니다.",chr->GetName().c_str(), m_name.c_str(), damage );	
	CLog::Add(buffer);
	
	if(reflection)
		chr->Attacked(this, 3, false);

	MinusHp(chr, damage);
	
	if(chr->m_type != PC) {
		char buffer2[1024];
		sprintf_s(buffer2, "%s hp %5d / %5d", GetName().c_str(), GetHp(), GetMHp() );	
		CLog::AddMonsterLog(buffer2);
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

// agebreak : 이 구현은 캐릭터가 아닌, Mob에게 있어야 하지 않을까?
void CCharacter::Killed(CCharacter* chr) {
	CLog::Add("몬스터를 죽였습니다.");
	
	
	char buf[100];
	sprintf_s(buf, "%d경험치를 얻었습니다.", GetExp());
	CLog::Add(buf);

	chr->AddExp(GetExp());
}
void CCharacter::AddExp(int exp) {
	if(m_mexp == 0)
		printf_s("Error\n");
	if(m_exp + exp > m_mexp) {
		int extraExp = m_exp + exp - m_mexp;
		LevelUp();
		AddExp(extraExp);
	} else if(m_exp + exp == m_mexp) {
		LevelUp();
	} else {
		SetExp(m_exp + exp);
	}
}
void CCharacter::LevelUp() {
	m_lv = m_lv + 1;
	m_exp = 0;
	m_mexp = m_mexp + 100;
	CLog::Add("레벨 업하셨습니다.");
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