// SUD.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "GameManager.h"

int _tmain(int argc, _TCHAR* argv[])
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	argc;
	argv;


	std::string helloWorld = "Hello World";
	std::cout<<helloWorld << std::endl;

	CGameManager gameManager;

	gameManager.Init();
	gameManager.Run();
	gameManager.Release();


	//getchar();
	return 0;
}