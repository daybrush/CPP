#pragma once
#include "GameMap.h"
#include "PC.h"
class CGameAI
{
public:
	void Move(CPC *character, CGameMap *gamemap);//���͵��� ĳ���� �������� ���������� �Լ�
	void Attack(CPC *character, CGameMap *gamemap);//���͵��� ĳ���Ϳ��� �����ϴ� �Լ�
	CGameAI(void);
	~CGameAI(void);
};

