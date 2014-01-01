#pragma once
#include "Screen.h"
#include "Data.h"
#include "GameAI.h"
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
	void GetStage(int stage);
	void GameEnding();
protected:
	CPC* m_PC;
	CGameMap* m_Map;
	CScreen m_Screen;
	CData m_data;
	CGameAI m_ai;
	int m_stage;
	bool m_flag;
};
#endif
