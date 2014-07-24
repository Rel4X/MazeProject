#pragma once

/* version 1.0 */

#include	<ctime>
#include	<map>
#include	<string>

#define			DEFAULT_KEY			"IamTheDefaultKeyOfRxString"

class			RxTime
{
private:
	bool							p_initialized;
	clock_t							p_initial_clock;
	std::map<std::string, clock_t>	p_timers;

public:
	RxTime(void);
	~RxTime(void);

public:
	bool		Start(const char* key = 0);
	float		GetEllapsedTime(const char* key = 0);
};
