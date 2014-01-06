#include "stdafx.h"
#include "GameAI.h"
#include <math.h>
#include <time.h>
CGameAI::CGameAI(void)
{
	srand((unsigned int)time(NULL));
}


CGameAI::~CGameAI(void)
{
}
void CGameAI::Attack(CPC *character, CGameMap *gamemap) {

	Position position = character->GetPosition();
	/*
	for(int i = -1; i <= 1; ++i) {
		for(int j = -1; j <= 1; ++j) {
			if(!(i == 0 || j == 0) )
				continue;
			if(!gamemap->IsShow(position.x + i, position.y + j))
				continue;
			int probability = rand() % 4;
			if(probability != 0)
				continue;
			CCharacter* monster = gamemap->GetMapInfo(position.x + i, position.y + j)->pChracter;
			if(monster->GetType() != MOB)
				continue;
			character->Attacked(monster, monster->GetPower(), true);
		}
	}*/
	
	//몬스터가 있는지 확인.
	if(!gamemap->IsShow(position.x, position.y))
		return;

	//확률 1/3로 몬스터가 공격한다.
	int probability = rand() % 3;
	if(probability != 0)
		return;
	CCharacter* monster = gamemap->GetMapInfo(position.x, position.y)->pChracter;
	
	//일단 몹이 아니면 공격을 안한다.
	if(monster->GetType() != MOB)
		return;
	
	character->Attacked(monster, monster->GetPower(), true);
	character->SetUnBeatDelay();
	

}
void CGameAI::Move(CPC *character, CGameMap *gamemap) {
	Position position = character->GetPosition();
	
	for(int i = 0; i < gamemap->GetWidth(); ++i) {
		for(int j = 0 ; j < gamemap->GetHeight(); ++j) {
			if(!gamemap->IsShow(i, j))
				continue;

			CCharacter* character = gamemap->GetMapInfo(i, j)->pChracter;
			if(character->GetType() != MOB)
				continue;
			
			//몬스터와 pc와의 간격.
			int gapX = position.x - i;
			int gapY = position.y - j;
			
			int probability = rand() % 30;
			if((probability <= 3) && gapX != 0)
				gamemap->SetCharacterMove(i, j, i + gapX / abs(gapX), j);
			else if((probability >=4 && probability < 8) && gapY != 0)
				gamemap->SetCharacterMove(i, j, i, j + gapY / abs(gapY));

		}
	}
}
