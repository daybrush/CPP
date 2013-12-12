#pragma once
struct Position {
	int x;
	int y;
};
enum DIRECTION {
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
};

enum TYPE {
	NPC,
	BLOCK,
	MOB,
	PC
};
class CCharacter
{
public:
	CCharacter(void);
	virtual ~CCharacter(void);

	void SetPosition(Position pos) {m_position = pos;}
	void SetPosition(int x, int y);

	void PrintPosition();

	Position GetPosition() {return m_position;}
	
	Position Move(DIRECTION dir);
	
	std::string GetName() {return m_name;}
	void SetName(std::string name) {m_name = name;}

	void Attacked(CCharacter* chr, int power, bool reflection);

	void MinusHp(CCharacter* chr, int minus);
	virtual void Killed(CCharacter* chr);

	TYPE GetType() {return m_type;}

	int GetLv() {return m_lv;}
	void SetLv(int lv){m_lv = lv;}
	void LevelUp();



	int GetHp() {return m_hp;}
	void SetHp(int hp){m_hp = hp;}

	int GetMHp() {return m_mhp;}
	void SetMHp(int mhp){m_mhp = mhp;}

	int GetMMp() {return m_mmp;}
	void SetMMp(int mmp){m_mmp = mmp;}

	int GetMp() {return m_mp;}
	void SetMp(int mp){m_mp = mp;}

	int GetExp() {return m_exp;}
	void SetExp(int exp){m_exp = exp;}
	void AddExp(int exp);

	int GetMExp() {return m_mexp;}
	void SetMExp(int mexp){m_mexp = mexp;}
	
protected:
	Position m_position;
	std::string m_name;
	TYPE m_type;

	int m_lv;

	int m_mhp;
	int m_hp;

	int m_mmp;
	int m_mp;
	
	int m_mexp;
	int m_exp;

};

