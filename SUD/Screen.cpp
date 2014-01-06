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

void CScreen::Show(CGameMap *maap, CPC *pc) {
	/*
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
	*/
	
	//가로로 펼쳐주기.
	for(int i = 0; i < SCREEN_SIZE + 2; i++ ) {
		std::string str = ShowMap(i, maap, pc);
		char buf[100];
		if(i >= 1 && i <= 2)//몬스터 로그
			sprintf_s(buf, "%-30.30s %.60s", str.c_str(), CLog::GetInstance()->GetMonsterLog(i + 2).c_str() );
		else if(i>3 && i <= 7)//내 상태창.
			sprintf_s(buf, "%-30.30s %.60s", str.c_str(), ShowStatus(i - 4, pc).c_str()); 
		else
			sprintf_s(buf, "%-30.30s", str.c_str());

		printf_s("%s\n", buf);
	}
	//일반적인 로그
	printf_s("%s\n", maap->GetDetail().c_str());
	for(int i = 0 ; i < 5; ++i) {
		printf_s("%s\n", CLog::GetInstance()->Get(i).c_str());
	}

	pc->SetSkillNotShow();
	
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
std::string CScreen::ShowMap(int line, CGameMap *mmap, CPC *pc) {
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
		DIRECTION dir = pc->GetPerspective();//캐릭터가 처다보고 있는 방향
		Position pcPosition = pc->GetPosition();//캐릭터의 위치
		//
		Position screen_position;

		//맵사이즈는 스크린사이즈보다 크거나 같은 걸로 가정한다.
		//스크린 위치가 움직이면서 스크린 사이즈에 해당하는 맵을 보여준다.


		//일단 스크린의 위치는 pc를 기준으로 가운데로 간다.
		screen_position.x = pcPosition.x - SCREEN_SIZE / 2;
		screen_position.y = pcPosition.y - SCREEN_SIZE / 2;

		//x,y가 0 미만이면 안된다.
		screen_position.x = __max(0, screen_position.x);
		screen_position.y = __max(0, screen_position.y);

		//스크린이 맵에서 벗어나면 안된다.
		screen_position.x = __min(screen_position.x, mmap->GetWidth() - SCREEN_SIZE);
		screen_position.y = __min(screen_position.y, mmap->GetHeight() - SCREEN_SIZE);


		int y = line - 1 + screen_position.y;//스크린의 y에 해당하는 map y좌표.
		map = map + "┃";



		int skillType = pc->GetSkillType();
		std::string skillSymbol = "━";
		if(dir == DIR_UP || dir == DIR_DOWN) {
			skillSymbol = "┃";
		}

		for(int j = 0; j < SCREEN_SIZE; ++j) {
			int x = screen_position.x + j;//스크린의 x에 해당하는 map x좌표.
			if(pcPosition.x == x && pcPosition.y == y) {
				map = map + pc->GetSymbol();
			} else if(mmap->IsShow(x, y)) {
				map = map + mmap->GetMapInfoName(x, y);
			} else {
				if(skillType == 1) {
					if(dir == DIR_UP && y < pcPosition.y && x == pcPosition.x)
						map = map + skillSymbol;
					else if(dir == DIR_DOWN && y > pcPosition.y && x == pcPosition.x)
						map = map + skillSymbol;
					else if(dir == DIR_LEFT && x < pcPosition.x && y == pcPosition.y)
						map = map + skillSymbol;
					else if(dir == DIR_RIGHT && x > pcPosition.x && y == pcPosition.y)
						map = map + skillSymbol;
					else map = map + "　";
				} else if(skillType == 2) {
					if(x >= pcPosition.x - 1 && x <= pcPosition.x + 1) {
						if(y >= pcPosition.y - 1 && y<= pcPosition.y + 1) {
							map = map + skillSymbol;
						} else {
							map = map + "　";
						}
					} else {
						map = map + "　";
					}
				}
				else {
					map = map + "　";
				}
			}
		}
		map = map + "┃";
		return map;
	}	
	//return "";
}