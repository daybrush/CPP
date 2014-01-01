#include "stdafx.h"
#include "Block.h"


CBlock::CBlock(void)
{
	m_type = BLOCK;
	m_name = "ºí·Ï";
	m_power = 0;
	m_hp = m_maxhp = 100;
	m_exp = m_maxexp = 10;
}


CBlock::~CBlock(void)
{
}
