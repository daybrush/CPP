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
	void ChangeDir(CGameMap *map, DIRECTION dir);
	
	void Attack(CGameMap* map);
	void AttackStraight(CGameMap* map);
	void AttackWide(CGameMap* map);

	void Killed(CCharacter* chr);
	bool Is_Over(){return m_is_over;}
	std::string GetSymbol();

	void SetIsNextStage(bool is_next){m_nextStage = is_next;};
	bool GetIsNextStage(){return m_nextStage;};

	void SetUnBeatDelay() {m_UnBeatDelay = 7;};
	void MinusUnBeatDelay() {
		--m_UnBeatDelay;
		if(m_UnBeatDelay < 0)
			m_UnBeatDelay = 0;
	};
	int GetUnBeatDelay() {return m_UnBeatDelay;}
	int GetSkillType() {return m_skillType;}
	void SetSkillNotShow() {m_skillType = 0;}
protected:
	DIRECTION m_Perspective;
	int m_skillType;
	bool m_is_over;
	bool m_nextStage;
	int m_UnBeatDelay;
};

