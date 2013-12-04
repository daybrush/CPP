#pragma once
#include "character.h"
#include "GameMap.h"
class CPC :
	public CCharacter
{
public:
	CPC(void);
	~CPC(void);
	DIRECTION GetPerspective() {return m_Perspective;}
	void SetPerspective(DIRECTION dir) {m_Perspective = dir;}
	void ChangeDir(CGameMap &map, DIRECTION dir);
	
	void Attack(CGameMap& map);
	void Killed(CCharacter* chr);
	bool Is_Over(){return m_is_over;}
	std::string GetSymbol();
protected:
	DIRECTION m_Perspective;
	bool m_is_over;
};

