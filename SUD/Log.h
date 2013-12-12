#pragma once
class CLog
{
public:
	CLog(void);
	~CLog(void);
	static void reset() {
		for(int i = 0; i < 5;++i) {
			m_logs[i] = "";
		}
	}
	static void Add(std::string log) {
		for(int i = 1; i < 5;++i) {
			m_logs[i - 1] = m_logs[i];
		}
		m_logs[4] = log;
	}
	static void AddMonsterLog(std::string log) {
		for(int i = 1; i < 5;++i) {
			m_monsterLog[i - 1] = m_monsterLog[i];
		}
		m_monsterLog[4] = log;
	}
	static std::string Get(int index) {return m_logs[index];}
	static std::string GetMonsterLog(int index) {return m_monsterLog[index];}


protected:
	static std::string m_logs[5];
	static std::string m_monsterLog[5];
};