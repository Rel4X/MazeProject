#pragma once

#include	<ctime>
#include	<cstdlib>

class		RandomMachine
{
private:
	static bool		p_initialized;

public:
	RandomMachine(void);
	~RandomMachine(void);

public:
	static int		Randomize(int, int);
};

