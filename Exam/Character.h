#pragma once
class CCharacter
{
public:
	CCharacter(void);
	CCharacter(const CCharacter& src);
	~CCharacter(void);
	void SetHP(int _hp);
	void PrintHP();
protected:
	int m_hp;
};

