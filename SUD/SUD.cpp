// SUD.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "GameManager.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::string helloWorld = "Hello World";
	std::cout<<helloWorld << std::endl;

	CGameManager gameManager;

	gameManager.Init();
	gameManager.Run();
	gameManager.Release();


	//getchar();
	return 0;
}