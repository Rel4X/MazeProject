#include "RandomMachine.h"

bool		RandomMachine::p_initialized = false;

RandomMachine::RandomMachine(void)
{
}

RandomMachine::~RandomMachine(void)
{
}

int			RandomMachine::Randomize(int min, int max)
{
	int			tmin;
	int			tmax;
	int			res;

	if (RandomMachine::p_initialized == false)
	{
		srand(time(0));
		RandomMachine::p_initialized = true;
	}
	if (min > max)
	{
		tmax = min + 1;
		tmin = max;
	}
	else
	{
		tmax = max + 1;
		tmin = min;
	}
	res = (int)((tmax - tmin) * (rand() / (double)RAND_MAX) + tmin);
	return (res);
}
