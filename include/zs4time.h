#ifndef ZS4_TIME
#define ZS4_TIME

#include <time.h>

class zs4time
{
	clock_t start;
public:
	inline zs4time(void){
		start = clock();
	}
	inline virtual ~zs4time(void){
	}

	inline double elapsed(void){
		clock_t diff = clock()-start;
		return (double)(((double)diff) / CLOCKS_PER_SEC);
	}
};

#endif

