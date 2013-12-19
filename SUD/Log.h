#pragma once
class CLog
{
public:
	CLog(void);
	~CLog(void);
	void reset() {
		for(int i = 0; i < 5;++i) {
			m_logs[i] = "";
		}
	}
	void Add(std::string log) {
		for(int i = 1; i < 5;++i) {
			m_logs[i - 1] = m_logs[i];
		}
		m_logs[4] = log;
	}
	void AddMonsterLog(std::string log) {
		for(int i = 1; i < 5;++i) {
			m_monsterLog[i - 1] = m_monsterLog[i];
		}
		m_monsterLog[4] = log;
	}
	std::string Get(int index) {return m_logs[index];}
	std::string GetMonsterLog(int index) {return m_monsterLog[index];}
	static CLog* GetInstance() {

		static CLog log;// = new CLog();

		return &log;
	}

protected:
	std::string m_logs[5];
	std::string m_monsterLog[5];
};