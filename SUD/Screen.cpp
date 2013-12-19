#include "stdafx.h"
#include "Screen.h"
#include <cstdlib>

CScreen::CScreen(void)
{
}


CScreen::~CScreen(void)
{
}

void CScreen::Clean() {
	std::system(CLEAR);
}

void CScreen::Show(CGameMap &maap, CPC *pc) {
	for(int i = 0; i < SCREEN_SIZE + 2; ++i ) {
		printf_s("%s\n", ShowMap(i, maap, pc).c_str()); 
	}
	
	printf_s("\n");
	
	for(int i = 0; i < 4;++i)
		printf_s("%s\n",ShowStatus(i , pc).c_str());
	
	printf_s("\n");

	printf_s("%s\n", CLog::GetInstance()->GetMonsterLog(4).c_str());
	
	printf_s("\n");
	
	for(int i = 0; i < 5; ++i)
		printf_s("%s\n",CLog::GetInstance()->Get(i).c_str());

	
	/*
	for(int i = 0; i < MAP_SIZE + 2; i++ ) {
		std::string str = ShowMap(i, maap, pc);
		char buf[100];
		
		if(i <=5 && i > 0)
			sprintf_s(buf, "%-30.30s %.60s", str.c_str(), CLog::Get(i - 1).c_str() );
		else if(i>7 && i <= 11)
			sprintf_s(buf, "%-30.30s %.60s", str.c_str(), ShowStatus(i - 8, pc).c_str()); 
		else
			sprintf_s(buf, "%-30.30s", str.c_str());

		printf_s("%s\n", buf);
	}
	printf_s("%s\n", CLog::GetMonsterLog(4).c_str());
	*/
}
std::string CScreen::ShowStatus(int line, CPC *pc) {
	char buf[100];
	switch(line) {
	case 0:
		sprintf_s(buf, "이름 : %s  레벨 : %d pos : (%d, %d)", pc->GetName().c_str(), pc->GetLevel(),pc->GetPosition().x,pc->GetPosition().y);
		break;
	case 1:
		sprintf_s(buf, "HP  : %5d / %5d", pc->GetHp(), pc->GetMaxHp());
		break;
	case 2:
		sprintf_s(buf, "MP  : %5d / %5d", pc->GetMp(), pc->GetMaxMp());
		break;
	case 3:
		sprintf_s(buf, "EXP : %5d / %5d", pc->GetExp(), pc->GetMaxExp());
		break;
	}
	
	return buf;
}
std::string CScreen::ShowMap(int line, CGameMap &mmap, CPC *pc) {
	std::string map;
	if(line == 0) {
		map = "┏";
		for(int i = 0; i < SCREEN_SIZE; ++i) {
			map = map + "━";
		}
		map = map + "┓";
		return map;
	}
	else if(line == SCREEN_SIZE + 1) {
		map = "┗";
		for(int i = 0; i < SCREEN_SIZE; ++i) {
			map = map + "━";
		}
		map = map + "┛\n";
		return map;
	}
	else {

		//
		Position screen_position;
		screen_position.x = pc->GetPosition().x - SCREEN_SIZE / 2;
		screen_position.y = pc->GetPosition().y - SCREEN_SIZE / 2;

		screen_position.x = __max(0, screen_position.x);
		screen_position.y = __max(0, screen_position.y);

		screen_position.x = __min(screen_position.x, MAP_SIZE - SCREEN_SIZE);
		screen_position.y = __min(screen_position.y, MAP_SIZE - SCREEN_SIZE);

		int y = line - 1 + screen_position.y;
		map = map + "┃";
		for(int j = 0; j < SCREEN_SIZE; ++j) {
			int x = screen_position.x + j;
			if(pc->GetPosition().x == x && pc->GetPosition().y == y) {
				map = map + pc->GetSymbol();
			} else if(mmap.IsShow(x, y)) {
				map = map + mmap.GetMapInfoName(x, y);
			} else {
				map = map + "　";
			}
		}
		map = map + "┃";
		return map;
	}	
	//return "";
}