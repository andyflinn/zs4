#ifndef ZS4_MACHINE_H
#define ZS4_MACHINE_H

#include <zs4.h>

typedef int (zs4transform)(const json_value * request, const json_value * state, zs4stream * out);

ZS4_ARRAYBUFFER(zs4machineChildren, 1024);

class zs4machine : public jsonObject
{
public:
	inline zs4machine(){
	}

	inline virtual ~zs4machine(){
	}

	zs4 zs4;
};

#endif
