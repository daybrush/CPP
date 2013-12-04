#include "stdafx.h"
#include "Character.h"


CCharacter::CCharacter(void)
{
		printf_s("Character is Created\n");
}

CCharacter::CCharacter( const CCharacter& src )
{
	m_hp = src.m_hp;
	printf_s("Character is COPY Created\n");
}


CCharacter::~CCharacter(void)
{
	printf_s("Character is Dead\n");
}

void CCharacter::PrintHP()
{
	printf_s("your HP = %d\n", m_hp);
}

void CCharacter::SetHP( int _hp )
{
	m_hp = _hp;
}