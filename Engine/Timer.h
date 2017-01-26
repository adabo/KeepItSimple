#pragma once

#include <chrono>

class Timer
{
public:
	Timer();
	~Timer();

	void Start();
	void Stop();
	float GetMilliseconds()const;
	float Reset();

private:
	std::chrono::time_point<std::chrono::steady_clock> m_start, m_end;
	bool m_started = false;
};

