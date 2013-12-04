// Exam.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Character.h"
void TestValue1() {
	CCharacter player;
	player.SetHP(99);
	player.PrintHP();
}
void TestValue2() {
	CCharacter partyMember[3];

	CCharacter soeun,wonHyo, jinSang;
	partyMember[0] = soeun;//���� ����
	partyMember[1] = wonHyo;//���� ����
	partyMember[2] = jinSang;

	partyMember[0].SetHP(111);
	soeun.PrintHP();
}
void Heal(CCharacter& player) {
	//CCharacter player ���翡 ���� ����
	//���� ������ ȣ��. �Ϲ� ������ ȣ�� X
	player.SetHP(999);
}
void TestValue3() {
	CCharacter gunhee;

	gunhee.SetHP(1);
	Heal(gunhee);
	gunhee.PrintHP();
}
void TestPointer_1() {
	CCharacter* pPlayer = new CCharacter();

	pPlayer->SetHP(999);
	pPlayer->PrintHP();

	delete pPlayer;
}
void TestPointer_2() {
	CCharacter* pParty[3];

	CCharacter* pJinWoo = new CCharacter();
	CCharacter* pJongChan = new CCharacter();
	CCharacter* pYoonSung = new CCharacter();
	pParty[0] = pJinWoo;
	pParty[1] = pJongChan;
	pParty[2] = pYoonSung;
	pParty[0]->SetHP(999);
	pJinWoo->PrintHP();

	for(int i = 0;i < 3;i++) {
		delete pParty[i];
	}
}

void Heal(CCharacter *pPlayer) {
	pPlayer->SetHP(999);
}
void TestPointer_3() {
	CCharacter* pYounKue = new CCharacter();

	pYounKue->SetHP(1);
	pYounKue->PrintHP();

	Heal(pYounKue);
	pYounKue->PrintHP();
	delete pYounKue;
}
void CopyPointer(CCharacter** player1, CCharacter** player2) {
	*player1 = *player2;
}

void TestPointer_4() {
	CCharacter* player1 = new CCharacter();
	CCharacter* player2 = new CCharacter();

	player1->SetHP(10);
	player2->SetHP(20);


	//player1 = player2;
	//CopyPointer(&player1,&player2);

	player1->PrintHP();
	player2->PrintHP();

	delete player1;
	delete player2;

}
void TestReference_1() {
	CCharacter player;
	CCharacter& refPlayer = player;//���۷��� ��
	CCharacter* pPlayer = &player;//���۷��� ������

	refPlayer.SetHP(666);
	player.PrintHP();
}

void TestValuePointer() {
	CCharacter player; //value
	player.SetHP(888);
	CCharacter* pPlayer = &player;//value -> Pointer
	player.PrintHP();
	CCharacter player2 = *pPlayer;//Pointer -> value
	player.PrintHP();
}
int _tmain(int argc, _TCHAR* argv[])
{
// 	TestValue1();
// 	TestValue1();
// 	TestValue1();
//  TestValue2();
/*	TestValue3();*/

	/*TestPointer_2();*/
	/*TestPointer_3();*/
	//TestPointer_4();

	//TestReference_1();
	TestValuePointer();
	getchar();
	
	return 0;
}

