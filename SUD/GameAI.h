#pragma once
#include "GameMap.h"
#include "Character.h"
class CGameAI
{
public:
	void Move(CCharacter *character, CGameMap *gamemap);//���͵��� ĳ���� �������� ���������� �Լ�
	void Attack(CCharacter *character, CGameMap *gamemap);//���͵��� ĳ���Ϳ��� �����ϴ� �Լ�
	CGameAI(void);
	~CGameAI(void);
};

