#include "stdafx.h"
#include "GameManager.h"
#include "Mob.h"
#include "Block.h"
#include <iostream>
#include <time.h>
#include <conio.h>
CGameManager::CGameManager(void)
{
	m_PC = new CPC();
	CLog::reset();
}


CGameManager::~CGameManager(void)
{
	delete m_PC;
}

void CGameManager::Init() {
	srand((unsigned int)time(NULL));


	printf("[Game Start!!]\n");
	m_PC->SetPosition(5, 5);
	m_PC->PrintPosition();

	

	CreateTempMap();
	CreateMobs();
}
void CGameManager::Run() {
	while(inputProc() ) {
		int a= 0;
		m_Screen.Clean();
		m_Screen.Show(m_Map, m_PC);

		if(m_PC->Is_Over() )
			break;
	}
	if(m_PC->Is_Over() )
		GameOver();

}
void CGameManager::GameOver() {
	printf_s("GAME OVER\n");
	GetKey();
}
void CGameManager::Release() {

}
int CGameManager::GetKey() {
	int key = _getch();
	
	// agebreak : 이 부분 처리에 대한 설명을 주석을 다는것이 좋음. 왜 이렇게 하는건지에 대해서..
	if(key == 224)
		key = 1000 + _getch();

	if(key>=97 && key <= 122)
		key = key - 32;
	return key;
}

bool CGameManager::inputProc()
{
	//키보드 입력을 받아서
	// 커맨드를 파싱하고, 맞게 처리한다.
	// q를 입력 받으면 종료된다.

	std::string strInput;
	//getline(std::cin, strInput);
	int key = GetKey();

	switch(key) {
	case 'W':
		m_PC->ChangeDir(m_Map, DIR_UP);
		break;
	case 'A':
		m_PC->ChangeDir(m_Map, DIR_LEFT);
		break;
	case 'S':
		m_PC->ChangeDir(m_Map, DIR_DOWN);
		break;
	case 'D':
		m_PC->ChangeDir(m_Map, DIR_RIGHT);
		break;
	case 'E':
		m_PC->Attack(m_Map);
		break;
	case 'Q':
		printf_s("게임을 종료하시겠습니까? (Y/N)\n");
		int quitKey = GetKey();
		if(quitKey == 'Y')
			return false;

	}

	return true;
}
void CGameManager::CreateTempMap() { 
	m_Map.GetMapInfo(8, 8)->pChr = new CBlock();
	m_Map.GetMapInfo(8, 9)->pChr = new CBlock();
	m_Map.GetMapInfo(9, 8)->pChr = new CBlock();
	m_Map.GetMapInfo(10, 8)->pChr = new CBlock();
	m_Map.GetMapInfo(11, 8)->pChr = new CBlock();
}
void CGameManager::CreateMobs() {

	CMob* mob = new CMob();
	mob->SetExp(30);
	mob->SetName("멋진 몹");
	m_Map.GetMapInfo(2, 3)->pChr = mob;
}