#pragma once
#include "PC.h"


#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

#define SCREEN_SIZE 12
class CScreen
{
public:
	CScreen(void);
	~CScreen(void);

	void Clean();
	void Show(CGameMap *m_Map,CPC *pc);
	void ShowInventory();

	std::string ShowStatus(int line, CPC *pc);
	void ShowSkill();
	std::string ShowMap(int line, CGameMap *m_Map,CPC *pc);

};

