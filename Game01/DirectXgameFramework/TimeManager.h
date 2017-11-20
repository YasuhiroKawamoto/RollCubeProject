#pragma once

class TimeManager 
{
public:
	~TimeManager() {}
	void Update();

	void SetTimeScale(float timeScale)
	{
		m_timeScale = timeScale;
	}

	float GetTime()
	{
		return m_time;
	}

public:
	static TimeManager* GetInstance();

private:
	float m_time;
	float m_timeScale;
private:
	TimeManager();

private:
	static TimeManager* s_instance;
	static const float DELTA_TIME;

};

