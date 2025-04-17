#include <time.h>
#include <stdio.h>

float	_start_time = 0.0f;
int		_started = 0;

int		start_bench(void)
{
    if (_started == 0)
	{
    	_start_time = (float)clock() / CLOCKS_PER_SEC;
    	_started = 1;
	}
    return 0;
}

float	end_bench(void)
{
    if (_started == 1)
    {
    	float	end_time = (float)clock()/CLOCKS_PER_SEC;
    	float	diff_time = end_time - _start_time;
    	_started = 0;
        return (diff_time);
    }
	return (0.0f);
}