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

	int GetLevel() {return m_level;}
	void SetLevel(int lv){m_level = lv;}
	void LevelUp();



	int GetHp() {return m_hp;}
	void SetHp(int hp){m_hp = hp;}

	int GetMaxHp() {return m_maxhp;}
	void SetMaxHp(int maxhp){m_maxhp = maxhp;}

	int GetMaxMp() {return m_maxmp;}
	void SetMaxMp(int maxmp){m_maxmp = maxmp;}

	int GetMp() {return m_mp;}
	void SetMp(int mp){m_mp = mp;}

	int GetExp() {return m_exp;}
	void SetExp(int exp){m_exp = exp;}
	void AddExp(int exp);

	int GetMaxExp() {return m_maxexp;}
	void SetMaxExp(int maxexp){m_maxexp = maxexp;}
	
protected:
	Position m_position;
	std::string m_name;
	TYPE m_type;

	int m_level;

	int m_maxhp;
	int m_hp;

	int m_maxmp;
	int m_mp;
	
	int m_maxexp;
	int m_exp;

};

