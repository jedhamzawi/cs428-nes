#include "Clock.h"

Clock::advance(int num_ticks) 
{
	clock = (clock + num_ticks) % clock_max;
};