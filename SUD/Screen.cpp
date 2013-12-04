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
	for(int i = 0; i < MAP_SIZE + 2; ++i ) {
		printf_s("%s\n", ShowMap(i, maap, pc).c_str()); 
	}
	
	printf_s("\n");
	
	for(int i = 0; i <4;++i)
		printf_s("%s\n",ShowStatus(i , pc).c_str());
	
	printf_s("\n");

	printf_s("%s\n", CLog::GetMonsterLog(4).c_str());
	
	printf_s("\n");
	
	for(int i = 0; i <5;++i)
		printf_s("%s\n",CLog::Get(i).c_str());

	
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
		sprintf_s(buf, "이름 : %s  레벨 : %d pos : (%d, %d)", pc->GetName().c_str(), pc->GetLv(),pc->GetPosition().x,pc->GetPosition().y);
		break;
	case 1:
		sprintf_s(buf, "HP  : %5d / %5d", pc->GetHp(), pc->GetMHp());
		break;
	case 2:
		sprintf_s(buf, "MP  : %5d / %5d", pc->GetMp(), pc->GetMMp());
		break;
	case 3:
		sprintf_s(buf, "EXP : %5d / %5d", pc->GetExp(), pc->GetMExp());
		break;
	}
	
	return buf;
}
std::string CScreen::ShowMap(int line, CGameMap &mmap, CPC *pc) {
	std::string map;
	if(line == 0) {
		map = "┏";
		for(int i = 0; i < MAP_SIZE; ++i) {
			map = map + "━";
		}
		map = map + "┓";
		return map;
	}
	else if(line == MAP_SIZE + 1) {
		map = "┗";
		for(int i = 0; i < MAP_SIZE; ++i) {
			map = map + "━";
		}
		map = map + "┛\n";
		return map;
	}
	else {
		int y = line - 1;
		map = map + "┃";
		for(int j = 0; j < MAP_SIZE; ++j) {
			if(pc->GetPosition().x == j && pc->GetPosition().y == y) {
				map = map + pc->GetSymbol();
			} else if(mmap.IsShow(j, y)) {
				map = map + mmap.GetMapInfoName(j, y);
			} else {
				map = map + "　";
			}
		}
		map = map + "┃";
		return map;
	}	
	return "";
}