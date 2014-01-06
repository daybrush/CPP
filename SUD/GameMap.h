#pragma once

#ifndef GAMEMAP
#define GAMEMAP


#define MAP_SIZE 20

#include "Character.h"
struct MapInfo
{
	CCharacter* pChracter;

};


class CGameMap
{
public:
	CGameMap(void);
	~CGameMap(void);
	void SetNo(int no) {m_no = no;}
	int GetNo() {return m_no;}
	void SetName(std::string name) {m_name = name;}
	void SetSize(int width, int height) {m_width = width; m_height = height;}
	void SetDetail(std::string detail) {m_detail = detail;}
	bool IsShow(int x, int y);//���Ͱ� �׾��°� �Ǵ� �ش���ǥ�� �ƹ��͵� ���� ��ǥ�� ��� �ֳ�..

	int GetWidth() {return m_width;};//���� ���� ũ��
	int GetHeight() {return m_height;};//���� ���� ũ��

	MapInfo* GetMapInfo(int x, int y);//�� ��ǥ�� �ִ� ���� ���� ��. ĳ������ ����
	std::string GetMapInfoName(int x, int y);//ĳ������ �ɺ��� ��Ÿ��.��
	std::string GetDetail() {return m_detail;}//�ʿ� ���� ����

	bool IsNoMonster();//�ʿ� �����ϴ� ���Ͱ� �ִ��� ������,
	void SetCharacterMove(int i, int j, int toI, int toJ);//���� �̵�

protected:
	MapInfo m_mapInfo[MAP_SIZE][MAP_SIZE];

	std::string m_name;
	std::string m_detail;
	int m_no;
	int m_width;
	int m_height;
	
};

#endif