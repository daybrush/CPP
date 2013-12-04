#pragma once
#include "Screen.h"


class CGameManager
{


#ifndef GAME_MANAGER

#define GAME_MANGER

#define IOS

#ifdef IOS
#endif
#ifdef ANDROID
#endif
#ifdef WINDOWS
#endif



public:
	CGameManager(void);
	~CGameManager(void);
	void Init();
	void Run();
	void Release();
	int GetKey();

protected:
	bool inputProc();
	void CreateTempMap();
	void CreateMobs();
	void GameOver();

protected:
	CPC* m_PC;
	CGameMap m_Map;
	CScreen m_Screen;
};
#endif
