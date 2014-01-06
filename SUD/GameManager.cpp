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
	printf_s("�ȳ��ϼ��� 1�г� �����Դϴ�.\n");
	printf_s("���״�� 1�г��� ��Ȱ�� �ϴ� ��������.\n");
	printf_s("1�г��� �����鼭 �� ��� ������ �����Ͻñ� �ٶ��ϴ�.\n");
	printf_s("����(��)���� ����ġ�� �ʽ��ϴ�.\n");
	printf_s("����Ű�� �̵�  a�� ����\n");
	printf_s("1�б� �Ĺ� ��� sŰ(�ʹٴٴ� : �ձ��� ������ �״´�.) \n");
	printf_s("3�б� �ʹ� ��� wŰ(����ġ�� : �����¿� �밢���� ���� �ִ� ������ ����������.) \n");
	printf_s("������ �� �����ϸ� ���� ���������� ���ø� ���� �ܰ�� �Ѿ�ϴ�. \n");
	printf_s("GOOD LUCK \n");
	//CreateTempMap();
	//CreateMobs();
	GetKey();
	GetStage(1);
}
//���� ���������� ��������
void CGameManager::GetStage(int stage) {
	
	delete m_Map;//���� �� �����Ѵ�.

	CGameMap* map = m_data.LoadMap(stage);//���� ���������� ���� �����´�.
	m_Map = map;
	if(map == nullptr) {//����
		m_flag = false;
		return;
	}

	
	m_stage = stage;

	m_PC->SetIsNextStage(false);//���� ���������� �Ѿ��� ��ȣ�� ��ҽ�Ų��.
	m_PC->SetPosition(0, 6);//ó�� ��ġ�� �̵���Ų��.

	m_Screen.Clean();
	printf_s("STAGE :: %d\n", m_Map->GetNo());
	GetKey();
}
void CGameManager::Run() {
	bool is_MonsterReadyToAttack = false;
	int chargeMPDelay = 0;// 10�� ȭ���� ���� �� ������ +1�� ä���.����
	if(m_Map == nullptr) {
		printf_s("���� �ε���� �ʾҽ��ϴ�.\n");
		GetKey();
		return;
	}


	//m_flag ���������� ������ ������ Ȯ��
	while(inputProc() && m_flag) {
		Sleep(100);//0.1���� ����
		is_MonsterReadyToAttack = !is_MonsterReadyToAttack;
		++chargeMPDelay;
		if(chargeMPDelay >=15) {//15�� ���� �� ������ mp 1 ���
			chargeMPDelay = 0;
			m_PC->SetMp(m_PC->GetMp() + 1);
		}
		m_ai.Move(m_PC, m_Map);//���Ͱ� ���ΰ����� ��..����

		//2�� ���� �Ҷ����� ���� �� �ִ� �Ǹ��� ����.������
		//���� ���� 3�� ���ű��� ����.
		if(m_PC->GetUnBeatDelay() <= 0 && is_MonsterReadyToAttack)
			m_ai.Attack(m_PC, m_Map);
		else
			m_PC->MinusUnBeatDelay();

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
	m_Screen.Clean();
	printf_s("GAME OVER\n");
	printf_s("-_- �״ٴ� ���⼭ ������ ���ΰ�... \n");
	GetKey();
}
void CGameManager::GameEnding() {
	m_Screen.Clean();
	printf_s("GAME Ending\n");
	printf_s("������ �� �˾���??\n");
	printf_s("2�г� ���� �̷����� ������\n");
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
	case 1072:// 1000 + 72 UP DIRECTION
		m_PC->ChangeDir(m_Map, DIR_UP);
		break;
	case 1075://1000+ 75 ���� ����Ű
		m_PC->ChangeDir(m_Map, DIR_LEFT);
		break;
	case 1080://1000 + 80 �Ʒ�����Ű
		m_PC->ChangeDir(m_Map, DIR_DOWN);
		break;
	case 1077://1000 + 77 ->
		m_PC->ChangeDir(m_Map, DIR_RIGHT);
		break;
	case 'A':
		m_PC->Attack(m_Map);
		break;
	case 'S'://Straight Skill
		m_PC->AttackStraight(m_Map);
		break;
	case 'W'://Wide Attack Skill
		m_PC->AttackWide(m_Map);
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
