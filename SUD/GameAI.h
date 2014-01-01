#pragma once
#include "GameMap.h"
#include "Character.h"
class CGameAI
{
public:
	void Move(CCharacter *character, CGameMap *gamemap);//몬스터들이 캐릭터 방향으로 움직이지는 함수
	void Attack(CCharacter *character, CGameMap *gamemap);//몬스터들이 캐릭터에게 공격하는 함수
	CGameAI(void);
	~CGameAI(void);
};

