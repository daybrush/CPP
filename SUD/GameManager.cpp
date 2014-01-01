#include "stdafx.h"
#include "GameManager.h"
#include "Mob.h"
#include "Block.h"
#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>


CGameManager::CGameManager(void)
{
	m_PC = new CPC();
	CLog::GetInstance()->reset();
	m_stage = 1;
	m_flag = true;
}


CGameManager::~CGameManager(void)
{
	delete m_PC;
	if(m_Map != nullptr)
		delete m_Map;
}

void CGameManager::Init() {
	srand((unsigned int)time(NULL));


	printf_s("[Game Start!!]\n");
	m_PC->SetPosition(5, 5);
	m_PC->PrintPosition();
	printf_s("�ȳ��ϼ��� 1�б�����Դϴ�.\n");
	printf_s("���״�� 1�б��� ��Ȱ�� �ϴ� ��������.\n");
	printf_s("1�б⸦ �����鼭 �� ��� ������ �����Ͻñ� �ٶ��ϴ�.\n");
	printf_s("����(��)���� ����ġ�� �ʽ��ϴ�.\n");
	printf_s("�� w �Ʒ� s �� a ���� d  ���� e \n");
	printf_s("������ �� �����ϸ� ���� ���������� ���ø� ���� �ܰ�� �Ѿ�ϴ�. \n");
	printf_s("GOOD LUCK \n");
	//CreateTempMap();
	//CreateMobs();
	GetKey();
	GetStage(1);
	GetKey();
}
void CGameManager::GetStage(int stage) {
	delete m_Map;
	CGameMap* map = m_data.LoadMap(stage);
	if(map == nullptr)
		m_flag = false;

	m_Map = map;
	m_stage = stage;
	m_PC->SetIsNextStage(false);
	m_PC->SetPosition(0, 6);
}
void CGameManager::Run() {
	bool is_ReadyAttack = false;

	if(m_Map == nullptr) {
		printf_s("���� �ε���� �ʾҽ��ϴ�.\n");
		GetKey();
		return;
	}

	//m_flag ���������� ������ ������ Ȯ��
	while(inputProc() && m_flag) {
		Sleep(100);//0.1�ʸ��� ����
		is_ReadyAttack = !is_ReadyAttack;

		m_ai.Move(m_PC, m_Map);//���Ͱ� ���ΰ����� ��..����

		//0.2�ʸ��� ���� �� �ִ� �Ǹ��� ����.������
		//���� �� ���� ����.... �ٴٴٴ�...
		if(is_ReadyAttack)
			m_ai.Attack(m_PC, m_Map);

		m_Screen.Clean();//ȭ�� Ŭ����
		m_Screen.Show(m_Map, m_PC);//ȭ�� �׷��ְ�.

		if(m_PC->Is_Over() )
			break;
	}
	if(!m_flag)
		GameEnding();

	if(m_PC->Is_Over() )
		GameOver();

}
void CGameManager::GameOver() {
	printf_s("GAME OVER\n");
	GetKey();
}
void CGameManager::GameEnding() {
	printf_s("GAME Ending\n");
	printf_s("������ �� �˾���??\n");
	printf_s("2�б� ���� �̷����� ������\n");
	GetKey();
}
void CGameManager::Release() {

}
int CGameManager::GetKey() {
	int key = _getch();
	

	// ���Ű�� ���� �� 224�� ���� �ް� �ٽ� �ѹ� �� �޴´�. alt, control, shift �� ����
	if(key == 224)
		key = 1000 + _getch();

	//�ҹ��ڸ� �빮�ڷ� �����Ѵ�.
	if(key>=97 && key <= 122)
		key = key - 32;
	return key;
}

bool CGameManager::inputProc()
{
	//Ű���� �Է��� �޾Ƽ�
	// Ŀ�ǵ带 �Ľ��ϰ�, �°� ó���Ѵ�.
	// q�� �Է� ������ ����ȴ�.
	if(!_kbhit())
		return true;

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

	//PC���� ���������� ������ ���� �ؽ�Ʈ���������� ����� �Ѵ�.
	if(m_PC->GetIsNextStage()) {
		GetStage(m_stage + 1);
	}

	return true;
}
