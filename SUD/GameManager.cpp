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
	
	if(key == 224)
		key = 1000 + _getch();

	if(key>=97 && key <= 122)
		key = key - 32;
	return key;
}

bool CGameManager::inputProc()
{
	//Ű���� �Է��� �޾Ƽ�
	// Ŀ�ǵ带 �Ľ��ϰ�, �°� ó���Ѵ�.
	// q�� �Է� ������ ����ȴ�.

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
		printf_s("������ �����Ͻðڽ��ϱ�? (Y/N)\n");
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
	mob->SetName("���� ��");
	m_Map.GetMapInfo(2, 3)->pChr = mob;
}