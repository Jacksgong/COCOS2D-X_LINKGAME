#ifndef __OTHER_H__
#define __OTHER_H__

#include <ctime>
#include <cstdlib>



double RanDom(double start, double end)
{
	return start+(end-start)*rand()/(RAND_MAX + 1.0);
}
#endif  // __OTHER_H__