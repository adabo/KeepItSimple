#include "Timer.h"

using namespace std::chrono;

Timer::Timer()
{
	Start();
}


Timer::~Timer()
{}

void Timer::Start()
{
	m_start = steady_clock::now();
	m_started = true;
}

void Timer::Stop()
{
	m_end = steady_clock::now();
	m_started = false;
}

float Timer::GetMilliseconds() const
{
	if( m_started )
		return duration<float>( steady_clock::now() - m_start ).count();
	else
		return duration<float>( m_end - m_start ).count();	
}

float Timer::Reset()
{
	Stop();
	const float dt = GetMilliseconds();
	Start();

	return dt;
}
