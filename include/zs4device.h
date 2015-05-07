
#include <zs4config.h>

#ifndef device
#define device char 
#define devicename "p8" 
#define bussclass p8
#define readfunction(t,f) t f ## _ ## p8(void)
#define writefunction(t,f,a) t f ## _ ## p8(p8 a)
#define mustundefdevice 1 
#endif

typedef class bussclass : public storage
{
public:
	unsigned device data = 0;

	static const char * NAME(){ return (const char *)devicename; }

	static const ZS4LARGE PRECISION = (ZS4LARGE)(unsigned device)(sizeof(device) << 3);
	static const ZS4LARGE MASK = (ZS4LARGE)(unsigned device)(~0);
	static const ZS4LARGE MAX = MASK;
	static const ZS4LARGE MIN = (ZS4LARGE)((device)0);
	static const ZS4LARGE SIGBIT = (ZS4LARGE)(bussclass::PRECISION - 1);
	static const ZS4LARGE PROBABILITY = (ZS4LARGE)(1 << PRECISION);

	// storage support
	INLINE_BITS_FUNCTION(){
		return PRECISION; 
	}
	inline virtual readfunction(ZS4LARGE, size){ return 1; }

	inline static unsigned device bitSet(unsigned device d, unsigned device i){ i %= bussclass::PRECISION; d |= (unsigned device)((unsigned device)1 << (unsigned device)i); return d; }
	inline static unsigned device bitClear(unsigned device d, unsigned device i){ i %= bussclass::PRECISION; d &= (unsigned device)((unsigned device)~((unsigned device)1 << (unsigned device)i)); return d; }
	inline static bool bitGet(unsigned device d, unsigned device i){ i %= bussclass::PRECISION; if (d & (unsigned device)((unsigned device)1 << (unsigned device)i))return true; return false; }
	inline static bool bitGetMS(unsigned device d){ return bitGet(d, (bussclass::PRECISION - 1)); }
	inline static bool bitGetLS(unsigned device d){ return bitGet(d, 0); }

	inline static unsigned device cmp(unsigned device c1, unsigned device c2){
		return c1 - c2;
	}
	inline static unsigned device cmp(const unsigned device * str1, const unsigned device * str2, const unsigned device * terminator = nullptr){
		if (terminator == nullptr){
			for (;;)
			{
				if (*str1 == 0 && *str2 == 0)
					return 0;

				if (*str1 != *str2)
					return *str1 - *str2;

				str1++; str2++;
			}

		}
		else{
			for (;;)
			{
				if (count(str1, terminator) && count(str2, terminator))
					return 0;

				if (*str1 != *str2)
					return *str1 - *str2;

				str1++; str2++;
			}
		}
	}
	inline static unsigned device ncmp(const unsigned device * str1, const unsigned device * str2, unsigned device n){
		for (unsigned device i = 0; i < n; i++)
		{
			unsigned device c1 = *str1++;
			unsigned device c2 = *str2++;
			if (c1 == 0 && c2 == 0) return 0;
			if (c1 != c2) return c1 - c2;
		}

		return 0;
	}

	inline static unsigned device len(const unsigned device * str, unsigned device * terminator = nullptr){
		unsigned device ret = 0;
		if (terminator == nullptr){
			while (*str){ str++; ret++; }
		}
		else{
			while (0 != (*str) && (0 == count(terminator, *str))){ str++; ret++; }
		}
		return ret;
	}
	inline static unsigned device count(const unsigned device * str, unsigned device c){
		if (str == 0)
			return 0;

		unsigned device ret = 0;

		while (*str != 0)
		{
			if (c == *str)
				ret++;
			str++;
		}

		return ret;
	}
	inline static unsigned device count(const unsigned device * s, const unsigned device * chrs){
		unsigned device ret = 0;
		for (const unsigned device * cp = s; cp && *cp; cp++)
		{
			for (const unsigned device * p = chrs; p && *p; p++)
			{
				if (*cp == *p)
					ret++;
			}
		}

		return ret;
	}
	inline static unsigned device swap(unsigned device org, unsigned device * str, unsigned device nu){
		unsigned device ret = 0;
		while (*str != 0) { if (*str == org) { *str = nu; ret++; } str++; }
		return ret;
	}
	inline static unsigned device ecmp(const unsigned device * str, const unsigned device * end){
		unsigned device len_str = len(str);
		unsigned device len_end = len(end);

		if (len_end > len_str)
			return 1;


		return cmp(&str[len_str - len_end], end);
	}

	INLINE_RESET_FUNCTION(){ data = 0; }
	inline signed cmp(device c)const{return data - c;}

	inline e io(stream * in, stream * out){
		device o = 0;
		device v = 0;

		return SUCCESS;
	}
	inline unsigned device from(const char * s, ZS4CHAR base = 10){
		zs4::event::numeric numeric;
		device data = 0;
		for (ZS4CHAR i = 0; s[i] != 0 && s[i] != '\n'; i++){
			ZS4LARGE lu = numeric.lookup((ZS4CHAR)s[i], base);
			if (lu >= (ZS4LARGE)MAX){
				data = 0;
				return data;
			}

			ZS4LARGE nu = (ZS4LARGE)((ZS4LARGE)((ZS4LARGE)data*(ZS4LARGE)base) + (ZS4LARGE)lu);
			if ((ZS4LARGE)nu > (ZS4LARGE)MAX){
				data = (device)MAX;
				return (device)MAX;
			}
			data = (device)nu;
		}
		//data = len(s);

		return data; //len(s);
	}
	inline unsigned device to(char * s, ZS4LARGE size, ZS4CHAR base = 10)const{

		if (size < 2)
			return (device)MAX;

		ZS4CHAR remainder = data;
		bool NOT_ZERO = false;

		ZS4LARGE count = 0;
		ZS4LARGE large = 1; while (large < MAX){ large *= base; count++; }

		zs4::event::numeric numeric;
		while (count)
		{
			ZS4LARGE accumulator = 0;
			while (remainder > large){
				accumulator++;
				NOT_ZERO = true;
			}

			if (NOT_ZERO){

				if (size > 1){
					*s++ = numeric.data()[accumulator];
					*s = 0;
					size--;
				}
				else {
					return (device)MAX;
				}

			}
			large /= base;
			count--;
		}

		return (device)MIN;
	}

	// C OPERATORS
	inline operator device()const{ return data; }
	inline operator unsigned device()const{ return data; }

	inline unsigned device & operator =(device d){ data = (unsigned device) d; return data; }
	inline unsigned device & operator &(device d){ return (data &= d); }

	inline unsigned device & operator =(size_t d){ data = (unsigned device) d; return data; }

	inline operator bool()const{ if (data != 0) { return true; } return false; }
	inline unsigned device & operator =(bool b){ if (b) data = (~0); else data = 0;  return data; }

	inline operator ZS4ANALOG()const{
		ZS4ANALOG r = 0.0;
		ZS4ANALOG h = 0.5;
		ZS4CHAR tru = 0;
		for (ZS4CHAR i = bussclass::PRECISION; i > 0; i--){
			if ((ZS4LARGE)data | (ZS4LARGE)(1 << (i - 1))) r += h;
			h /= 2.0;
		}
		return r;
	}
	inline unsigned device & operator =(ZS4ANALOG a){
		if (a < 0.0) a = 0.0;
		if (a > 1.0) a = 1.0;

		data = (ZS4CHAR)((ZS4ANALOG)((ZS4ANALOG)bussclass::MAX * (ZS4ANALOG)a));
		return data;
	}

	inline unsigned device & operator = (const char * s){

		if ((*s) == 0 || (*s) == '\n'){
			return data;
		}

		return (data=from(s));
	}
	// END OF C OPERATORS


}bussclass;
	
#ifdef mustundefdevice
#undef device
#undef devicename 
#undef bussclass
#undef readfunction
#undef writefunction
#undef mustundefdevice
#endif


