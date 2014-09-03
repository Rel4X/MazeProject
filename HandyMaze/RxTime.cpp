#include	"RxTime.h"

/* version 1.0 */

RxTime::RxTime(void) :
	p_initialized(false), p_initial_clock(0)
{
}

RxTime::~RxTime(void)
{
}

bool		RxTime::Start(const char* key)
{
	if (this->p_initialized == false)
	{
		this->p_initial_clock = clock();
		if (this->p_initial_clock == -1)
			return (false);
		this->p_initialized = true;
	}
	if (key)
	{
		this->p_timers[key] = clock();
		if (this->p_timers[key] == -1)
			return (false);
	}
	else
	{
		this->p_timers[DEFAULT_KEY] = clock();
		if (this->p_timers[DEFAULT_KEY] == -1)
			return (false);
	}
	return (true);
}

float		RxTime::GetEllapsedTime(const char* key)
{
	std::map<std::string, clock_t>::iterator	it;

	if (this->p_initialized = false) return (0.0);
	if (key) it = this->p_timers.find(key); else it = this->p_timers.find(DEFAULT_KEY);
	if (it == this->p_timers.end()) return (0.0);
	return (((float)(clock() - (*it).second)) / CLOCKS_PER_SEC);
}
