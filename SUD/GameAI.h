#pragma once
#include "GameMap.h"
#include "PC.h"
class CGameAI
{
public:
	void Move(CPC *character, CGameMap *gamemap);//몬스터들이 캐릭터 방향으로 움직이지는 함수
	void Attack(CPC *character, CGameMap *gamemap);//몬스터들이 캐릭터에게 공격하는 함수
	CGameAI(void);
	~CGameAI(void);
};

