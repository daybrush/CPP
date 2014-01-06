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
	printf_s("안녕하세요 1학년 게임입니다.\n");
	printf_s("말그대로 1학년의 생활을 하는 게임이죠.\n");
	printf_s("1학년을 지내면서 꼭 모든 과목을 수료하시기 바랍니다.\n");
	printf_s("과목(몹)들이 만만치는 않습니다.\n");
	printf_s("방향키는 이동  a는 공격\n");
	printf_s("1학기 후반 기술 s키(와다다다 : 앞길을 막으면 죽는다.) \n");
	printf_s("3학기 초반 기술 w키(벼락치기 : 상하좌우 대각선을 막고 있는 과목을 끝내버린다.) \n");
	printf_s("몹들을 다 제거하면 가장 오른쪽으로 가시면 다음 단계로 넘어갑니다. \n");
	printf_s("GOOD LUCK \n");
	//CreateTempMap();
	//CreateMobs();
	GetKey();
	GetStage(1);
}
//다음 스테이지로 가져오기
void CGameManager::GetStage(int stage) {
	
	delete m_Map;//현재 맵 삭제한다.

	CGameMap* map = m_data.LoadMap(stage);//다음 스테이지의 맵을 가져온다.
	m_Map = map;
	if(map == nullptr) {//엔딩
		m_flag = false;
		return;
	}

	
	m_stage = stage;

	m_PC->SetIsNextStage(false);//다음 스테이지로 넘어가라는 신호를 취소시킨다.
	m_PC->SetPosition(0, 6);//처음 위치로 이동시킨다.

	m_Screen.Clean();
	printf_s("STAGE :: %d\n", m_Map->GetNo());
	GetKey();
}
void CGameManager::Run() {
	bool is_MonsterReadyToAttack = false;
	int chargeMPDelay = 0;// 10번 화면이 갱신 될 때마다 +1씩 채운다.ㅋㅋ
	if(m_Map == nullptr) {
		printf_s("맵이 로드되지 않았습니다.\n");
		GetKey();
		return;
	}


	//m_flag 스테이지가 끝까지 갔는지 확인
	while(inputProc() && m_flag) {
		Sleep(100);//0.1마다 갱신
		is_MonsterReadyToAttack = !is_MonsterReadyToAttack;
		++chargeMPDelay;
		if(chargeMPDelay >=15) {//15번 갱신 할 때마다 mp 1 상승
			chargeMPDelay = 0;
			m_PC->SetMp(m_PC->GetMp() + 1);
		}
		m_ai.Move(m_PC, m_Map);//몬스터가 주인공에게 감..ㅋㅋ

		//2번 갱신 할때마다 때릴 수 있는 권리가 생김.ㅋㅋㅋ
		//무적 상태 3번 갱신까지 무시.
		if(m_PC->GetUnBeatDelay() <= 0 && is_MonsterReadyToAttack)
			m_ai.Attack(m_PC, m_Map);
		else
			m_PC->MinusUnBeatDelay();

		m_Screen.Clean();//화면 클리어
		m_Screen.Show(m_Map, m_PC);//화면 그려주고.

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
	printf_s("-_- 죽다니 여기서 포기할 것인가... \n");
	GetKey();
}
void CGameManager::GameEnding() {
	m_Screen.Clean();
	printf_s("GAME Ending\n");
	printf_s("엔딩일 줄 알았지??\n");
	printf_s("2학년 때도 이럴꺼야 ㅋㅋㅋ\n");
	GetKey();
}
void CGameManager::Release() {

}
int CGameManager::GetKey() {
	int key = _getch();
	

	// 기능키를 누를 시 224를 먼저 받고 다시 한번 더 받는다. alt, control, shift 등 ㅋㅋ
	if(key == 224)
		key = 1000 + _getch();

	//소문자를 대문자로 통일한다.
	if(key>=97 && key <= 122)
		key = key - 32;
	return key;
}

bool CGameManager::inputProc()
{
	//키보드 입력을 받아서
	// 커맨드를 파싱하고, 맞게 처리한다.
	// q를 입력 받으면 종료된다.
	if(!_kbhit())
		return true;

	std::string strInput;
	//getline(std::cin, strInput);
	int key = GetKey();

	switch(key) {
	case 1072:// 1000 + 72 UP DIRECTION
		m_PC->ChangeDir(m_Map, DIR_UP);
		break;
	case 1075://1000+ 75 왼쪽 방향키
		m_PC->ChangeDir(m_Map, DIR_LEFT);
		break;
	case 1080://1000 + 80 아래방향키
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
		printf_s("게임을 종료하시겠습니까? (Y/N)\n");
		int quitKey = GetKey();
		if(quitKey == 'Y')
			return false;

	}

	//PC에서 오른쪽으로 끝까지 가면 넥스트스테이지로 가라고 한다.
	if(m_PC->GetIsNextStage()) {
		GetStage(m_stage + 1);
	}

	return true;
}
