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
	
	//���η� �����ֱ�.
	for(int i = 0; i < SCREEN_SIZE + 2; i++ ) {
		std::string str = ShowMap(i, maap, pc);
		char buf[100];
		if(i >= 1 && i <= 2)//���� �α�
			sprintf_s(buf, "%-30.30s %.60s", str.c_str(), CLog::GetInstance()->GetMonsterLog(i + 2).c_str() );
		else if(i>3 && i <= 7)//�� ����â.
			sprintf_s(buf, "%-30.30s %.60s", str.c_str(), ShowStatus(i - 4, pc).c_str()); 
		else
			sprintf_s(buf, "%-30.30s", str.c_str());

		printf_s("%s\n", buf);
	}
	//�Ϲ����� �α�
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
		sprintf_s(buf, "�̸� : %s  ���� : %d pos : (%d, %d)", pc->GetName().c_str(), pc->GetLevel(),pc->GetPosition().x,pc->GetPosition().y);
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
		map = "��";
		for(int i = 0; i < SCREEN_SIZE; ++i) {
			map = map + "��";
		}
		map = map + "��";
		return map;
	}
	else if(line == SCREEN_SIZE + 1) {
		map = "��";
		for(int i = 0; i < SCREEN_SIZE; ++i) {
			map = map + "��";
		}
		map = map + "��\n";
		return map;
	}
	else {
		DIRECTION dir = pc->GetPerspective();//ĳ���Ͱ� ó�ٺ��� �ִ� ����
		Position pcPosition = pc->GetPosition();//ĳ������ ��ġ
		//
		Position screen_position;

		//�ʻ������ ��ũ��������� ũ�ų� ���� �ɷ� �����Ѵ�.
		//��ũ�� ��ġ�� �����̸鼭 ��ũ�� ����� �ش��ϴ� ���� �����ش�.


		//�ϴ� ��ũ���� ��ġ�� pc�� �������� ����� ����.
		screen_position.x = pcPosition.x - SCREEN_SIZE / 2;
		screen_position.y = pcPosition.y - SCREEN_SIZE / 2;

		//x,y�� 0 �̸��̸� �ȵȴ�.
		screen_position.x = __max(0, screen_position.x);
		screen_position.y = __max(0, screen_position.y);

		//��ũ���� �ʿ��� ����� �ȵȴ�.
		screen_position.x = __min(screen_position.x, mmap->GetWidth() - SCREEN_SIZE);
		screen_position.y = __min(screen_position.y, mmap->GetHeight() - SCREEN_SIZE);


		int y = line - 1 + screen_position.y;//��ũ���� y�� �ش��ϴ� map y��ǥ.
		map = map + "��";



		int skillType = pc->GetSkillType();
		std::string skillSymbol = "��";
		if(dir == DIR_UP || dir == DIR_DOWN) {
			skillSymbol = "��";
		}

		for(int j = 0; j < SCREEN_SIZE; ++j) {
			int x = screen_position.x + j;//��ũ���� x�� �ش��ϴ� map x��ǥ.
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
					else map = map + "��";
				} else if(skillType == 2) {
					if(x >= pcPosition.x - 1 && x <= pcPosition.x + 1) {
						if(y >= pcPosition.y - 1 && y<= pcPosition.y + 1) {
							map = map + skillSymbol;
						} else {
							map = map + "��";
						}
					} else {
						map = map + "��";
					}
				}
				else {
					map = map + "��";
				}
			}
		}
		map = map + "��";
		return map;
	}	
	//return "";
}