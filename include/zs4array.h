#ifndef ZS4_ARRAY
#define ZS4_ARRAY

#include <zs4string.h>

#define ZS4_ARRAYBUFFER(n,s) class n:public zs4string{public:inline n(){construct(data,(s*sizeof(void*)),0);clear();};inline virtual ~n(){clear();};private:char data[(s*sizeof(void*))];}

template <class elementtype>
class zs4array
{
public:
	zs4string buffer;
	inline zs4array()
	{
	}
	inline zs4array(size_t size, elementtype * in)
	{
		zs4string str;
		str.construct(in, size);
	}
	inline virtual ~zs4array()
	{
	}

	inline elementtype** add(elementtype*obj){
		if (elementtype ** ret = (elementtype **)buffer.zs4alloc(sizeof(elementtype*)))
		{
			*ret = obj;
			return ret;
		}
		return nullptr;
	}

	inline void operator = (zs4string&buf){ buffer = buf; }

	inline elementtype** arr(void){ return (elementtype**)buffer.str; }
	inline size_t count(void){ return (buffer.len / sizeof(elementtype*)); }
};

#endif

