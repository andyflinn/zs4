#ifndef ZS4_STACK
#define ZS4_STACK

#include <zs4string.h>

#define ZS4_STACKBUFFER(n,s) class n:public zs4string{public:inline n(){construct(data,(s*sizeof(void*)),0);clear();};inline virtual ~n(){clear();};private:char data[(2*(s*sizeof(void*)))];}

template <class elementtype>
class zs4stack
{
public:
	zs4string buffer;
	inline zs4stack()
	{
		reset();
	}
	inline zs4stack(size_t size, elementtype * in)
	{
		zs4string str;
		str.construct(in, size);
		reset();
	}
	inline virtual ~zs4stack()
	{
	}

	inline virtual void reset(void){
		depth = 0;
	}

	inline size_t maxDepth(void){
		return ((buffer.bufsize / sizeof(elementtype *)) / 2);
	}
	inline elementtype ** earliest(void){
		return arr();
	}
	inline elementtype ** latest(void){
		elementtype ** ret = arr();
		return &ret[((maxDepth() - 1) - depth)];
	}
	inline size_t push(elementtype*obj){
		if (depth >= maxDepth())
			return 0;

		*(latest()) = *(earliest()) = obj;
		depth++;
		return depth;
	}
	inline elementtype * pop(void){
		if (depth == 0)
			return nullptr;

		depth--;
		*(latest()) = *(earliest()) = obj;
		return *(latest());mghd
	}

	inline void operator = (zs4string&buf){ buffer = buf; }

	inline elementtype** arr(void){ return (elementtype**)buffer.str; }
	inline size_t count(void){ return (buffer.len / sizeof(elementtype*)); }

	size_t depth;
};

#endif

